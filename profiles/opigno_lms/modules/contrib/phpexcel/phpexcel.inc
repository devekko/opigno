<?php

/**
 * @file
 * Defines the phpexcel api functions that other modules can use.
 */

define('PHPEXCEL_ERROR_NO_HEADERS', 0);
define('PHPEXCEL_ERROR_NO_DATA', 1);
define('PHPEXCEL_ERROR_PATH_NOT_WRITABLE', 2);
define('PHPEXCEL_ERROR_LIBRARY_NOT_FOUND', 3);
define('PHPEXCEL_ERROR_FILE_NOT_WRITTEN', 4);
define('PHPEXCEL_ERROR_FILE_NOT_READABLE', 5);
define('PHPEXCEL_CACHING_METHOD_UNAVAILABLE', 6);
define('PHPEXCEL_SUCCESS', 10);

/**
 * Simple API function which will generate an XLS file and
 * save it in $path.
 *
 * @param array $headers
 *            An array containing all headers. If given a two-dimensional array,
 *            each first dimension entry will be on a separate worksheet
 *            ($headers[sheet][header]).
 * @param array $data
 *            A two-dimensional array containing all data ($data[row][column]).
 *            If given a three-dimensional array, each first dimension
 *            entry will be on a separate worksheet ($data[sheet][row][column]).
 * @param string $path
 *            The path where the file must be saved. Must be writable.
 * @param array $options
 *            An array which allows to set some specific options.
 *            Used keys:
 *                [format] = The EXCEL format. Can be either 'xls' or 'xlsx'
 *                [creator] = The name of the creator
 *                [title] = The title
 *                [subject] = The subject
 *                [description] = The description
 *            The options array will always be passed to all the hooks. If
 *            developers need specific information for their own hooks, they
 *            can add any data to this array.
 * @return PHPEXCEL_SUCCESS|PHPEXCEL_ERROR_NO_HEADERS|PHPEXCEL_ERROR_NO_DATA|PHPEXCEL_ERROR_PATH_NOT_WRITABLE|PHPEXCEL_ERROR_LIBRARY_NOT_FOUND
 *            PHPEXCEL_SUCCESS on success, PHPEXCEL_ERROR_NO_HEADERS, PHPEXCEL_ERROR_NO_DATA, PHPEXCEL_ERROR_PATH_NOT_WRITABLE or
 *            PHPEXCEL_ERROR_LIBRARY_NOT_FOUND on error. Look in watchdog logs for information
 *            about errors.
 */
function phpexcel_export($headers = array(), $data = array(), $path = '', $options = NULL) {
  if (!count(
      $headers
    ) && (!isset($options['ignore_headers']) || (isset($options['ignore_headers']) && !$options['ignore_headers']))
  ) {
    watchdog(
      'phpexcel',
      "No header was provided, and the 'ignore_headers' option was not set to TRUE. Excel export aborted.",
      array(),
      WATCHDOG_ERROR
    );

    return PHPEXCEL_ERROR_NO_HEADERS;
  }

  if (!count($data)) {
    watchdog('phpexcel', "No data was provided. Excel export aborted.", array(), WATCHDOG_ERROR);

    return PHPEXCEL_ERROR_NO_DATA;
  }

  if (!(is_writable($path) || (!file_exists($path) && is_writable(dirname($path))))) {
    watchdog(
      'phpexcel',
      "Path '@path' is not writable. Excel export aborted.",
      array('@path' => $path),
      WATCHDOG_ERROR
    );

    return PHPEXCEL_ERROR_PATH_NOT_WRITABLE;
  }

  $library = libraries_load('PHPExcel');

  if (empty($library['loaded'])) {
    watchdog('phpexcel', "Couldn't find the PHPExcel library. Excel export aborted.", array(), WATCHDOG_ERROR);

    return PHPEXCEL_ERROR_LIBRARY_NOT_FOUND;
  }

  $path = phpexcel_munge_filename($path);

  // Determine caching method.
  $cache_settings = array();
  switch (variable_get('phpexcel_cache_mechanism')) {
    case 'cache_in_memory_serialized':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_in_memory_serialized;
      break;

    case 'cache_in_memory_gzip':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_in_memory_gzip;
      break;

    case 'cache_to_phpTemp':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_to_phpTemp;
      $cache_settings = array(
        'memoryCacheSize' => variable_get('phpexcel_phptemp_limit', 1) . 'MB'
      );
      break;

    case 'cache_to_apc':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_to_apc;
      $cache_settings = array(
        'cacheTime' => variable_get('phpexcel_apc_cachetime', '600')
      );
      break;

    case 'cache_to_memcache':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_to_memcache;
      $cache_settings = array(
        'memcacheServer' => variable_get('phpexcel_memcache_host', 'localhost'),
        'memcachePort' => variable_get('phpexcel_memcache_port', '11211'),
        'cacheTime' => variable_get('phpexcel_memcache_cachetime', '600')
      );
      break;

    case 'cache_to_sqlite3':
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_to_memcache;
      break;

    default:
      $cache_method = PHPExcel_CachedObjectStorageFactory::cache_in_memory;
      break;
  }

  // Is it available ? If not, return an error.
  if (empty($cache_method)) {
    return PHPEXCEL_CACHING_METHOD_UNAVAILABLE;
  }

  PHPExcel_Settings::setCacheStorageMethod($cache_method, $cache_settings);

  // Must we render from a template file ?
  if (!empty($options['template'])) {
    $xls_reader = PHPExcel_IOFactory::createReaderForFile($options['template']);

    $xls = $xls_reader->load($options['template']);
  }
  else {
    $xls = new PHPExcel();
  }

  _phpexcel_set_properties($xls->getProperties(), $options);

  // Must we ignore the headers ?
  if (empty($options['ignore_headers'])) {
    _phpexcel_set_headers($xls, $headers, $options);
  }

  _phpexcel_set_columns($xls, $data, empty($options['ignore_headers']) ? $headers : NULL, $options);

  if (!isset($options['format']) || $options['format'] == 'xls') {
    $writer = new PHPExcel_Writer_Excel5($xls);
  }
  else {
    $writer = new PHPExcel_Writer_Excel2007($xls);
  }

  $writer->save($path);

  return file_exists($path) ? PHPEXCEL_SUCCESS : PHPEXCEL_ERROR_FILE_NOT_WRITTEN;
}

/**
 * Simple API function which allows to export a db_query() result to an Excel file.
 * The headers will be set to the names of the exported columns.
 *
 * @see phpexcel_export()
 *
 * @param result $result
 *              The MySQL result object.
 * @param string $path
 *              The path where the file should be saved. Must be writable.
 * @param array $options
 *              An array which allows to set some specific options.
 *
 * @return bool
 *              TRUE on success, FALSE on error. Look into watchdog logs for information
 *              about errors.
 */
function phpexcel_export_db_result($result, $path, $options = array()) {
  $data = array();

  while ($row = $result->fetchAssoc()) {
    if (!isset($headers)) {
      $headers = array_keys($row);
    }
    $data[] = array_values($row);
  }

  return phpexcel_export($headers, $data, $path, $options);
}

/**
 * Sets the Excel file properties, like creator, title, etc.
 *
 * @see phpexcel_export()
 */
function _phpexcel_set_properties($properties, $options) {
  if (isset($options['creator'])) {
    $properties->setCreator($options['creator']);
  }
  else {
    $properties->setCreator("PHPExcel");
  }

  if (isset($options['title'])) {
    $properties->setTitle($options['title']);
  }

  if (isset($options['subject'])) {
    $properties->setSubject($options['subject']);
  }

  if (isset($options['description'])) {
    $properties->setDescription($options['description']);
  }
}

/**
 * Sets the Excel file headers.
 *
 * @see phpexcel_export()
 */
function _phpexcel_set_headers($xls, &$headers, $options) {
  if (!is_array(current(array_values($headers)))) { // Prior to PHP 5.3, calling current() on an associative array would not work. Get only array values, just in case.
    $headers = array($headers);
  }

  phpexcel_invoke('export', 'headers', $headers, $xls, $options);

  $sheet_id = 0;
  foreach ($headers as $sheet_name => $sheet_headers) {
    if ($sheet_id) {
      $xls->createSheet($sheet_id);
      $sheet = $xls->setActiveSheetIndex($sheet_id);
    }
    else {
      // PHPExcel always creates one sheet.
      $sheet = $xls->getSheet();
    }

    if (!is_numeric($sheet_name)) {
      $sheet->setTitle($sheet_name);
    }
    else {
      $sheet->setTitle(t("Worksheet !id", array('!id' => ($sheet_id + 1))));
    }

    phpexcel_invoke('export', 'new sheet', $sheet_id, $xls, $options);

    for ($i = 0, $len = count($sheet_headers); $i < $len; $i++) {
      $value = trim($sheet_headers[$i]);

      phpexcel_invoke('export', 'pre cell', $value, $sheet, $options, $i, 1);

      $sheet->setCellValueByColumnAndRow($i, 1, $value);

      phpexcel_invoke('export', 'post cell', $value, $sheet, $options, $i, 1);
    }

    $sheet_id++;
  }
}

/**
 * Adds the data to the Excel file.
 *
 * @see phpexcel_export()
 */
function _phpexcel_set_columns($xls, &$data, $headers = NULL, $options = array()) {
  if (!is_array(current(current(array_values($data))))) { // Prior to PHP 5.3, calling current() on an associative array would not work. Get only array values, just in case.
    $data = array($data);
  }

  phpexcel_invoke('export', 'data', $data, $xls, $options);

  $sheet_id = 0;
  foreach ($data as $sheet_name => $sheet_data) {
    // If the headers are not set, we haven't created any sheets yet.
    // Create them now.
    if (!isset($headers)) {
      $offset = 1;
      if ($sheet_id) {
        $xls->createSheet($sheet_id);
        $sheet = $xls->setActiveSheetIndex($sheet_id);
      }
      else {
        // PHPExcel always creates one sheet.
        $sheet = $xls->getSheet();
      }

      if (!is_numeric($sheet_name)) {
        $sheet->setTitle($sheet_name);
      }
      else {
        $sheet->setTitle(t("Worksheet !id", array('!id' => ($sheet_id + 1))));
      }

      phpexcel_invoke('export', 'new sheet', $sheet_id, $xls, $options);
    }
    else {
      $offset = 2;
      $sheet = $xls->setActiveSheetIndex($sheet_id);
    }

    for ($i = 0, $len = count($sheet_data); $i < $len; $i++) {
      for ($j = 0; $j < count($sheet_data[$i]); $j++) {
        $value = isset($sheet_data[$i][$j]) ? $sheet_data[$i][$j] : '';

        // We must offset the row count (by 2, because PHPExcel starts the count at 1), because the first row is used by the headers
        phpexcel_invoke('export', 'pre cell', $value, $sheet, $options, $j, $i + $offset);

        $sheet->setCellValueByColumnAndRow($j, $i + $offset, $value);

        phpexcel_invoke('export', 'post cell', $value, $sheet, $options, $j, $i + $offset);
      }
    }

    $sheet_id++;
  }
}

/**
 * Simple API function that will load an Excel file from $path and parse it
 * as a multidimensional array.
 *
 * @todo API Cleanup. This is getting out of hand as multiple feature requests come in. Only one,
 * optional, parameter array ? Similar to core theme functions ?
 *
 * @param string $path
 *            The path to the Excel file. Must be readable.
 * @param boolean $keyed_by_headers = TRUE
 *            If TRUE, will key the row array with the header values and will
 *            skip the header row. If FALSE, will contain the headers in the first
 *            row and the rows will be keyed numerically.
 * @param boolean $keyed_by_worksheet = FALSE
 *            If TRUE, will key the data array with the worksheet names. Otherwise, it will use a numerical key.
 * @param array $custom_calls = NULL
 *            An associative array of methods and arguments to call on the PHPExcel Reader object.
 * @return array|PHPEXCEL_ERROR_LIBRARY_NOT_FOUND|PHPEXCEL_ERROR_FILE_NOT_READABLE
 *            The parsed data as an array on success, PHPEXCEL_ERROR_LIBRARY_NOT_FOUND or PHPEXCEL_ERROR_FILE_NOT_READABLE on error.
 */
function phpexcel_import($path, $keyed_by_headers = TRUE, $keyed_by_worksheet = FALSE, $custom_calls = NULL) {
  if (is_readable($path)) {
    $library = libraries_load('PHPExcel');

    if (!empty($library['loaded'])) {
      $xls_reader = PHPExcel_IOFactory::createReaderForFile($path);

      $xls_reader->setReadDataOnly(TRUE);

      if (!empty($custom_calls)) {
        foreach ($custom_calls as $method => $args) {
          if (method_exists($xls_reader, $method)) {
            call_user_func_array(array($xls_reader, $method), $args);
          }
        }
      }

      $xls_data = $xls_reader->load($path);

      $data = array();
      $headers = array();
      $i = 0;

      phpexcel_invoke('import', 'full', $xls_data, $xls_reader, array('keyed_by_headers' => $keyed_by_headers));

      foreach ($xls_data->getWorksheetIterator() as $worksheet) {
        $j = 0;

        phpexcel_invoke('import', 'sheet', $worksheet, $xls_reader, array('keyed_by_headers' => $keyed_by_headers));

        foreach ($worksheet->getRowIterator() as $row) {
          if ($keyed_by_worksheet) {
            $i = $worksheet->getTitle();
          }
          $k = 0;

          phpexcel_invoke('import', 'row', $row, $xls_reader, array('keyed_by_headers' => $keyed_by_headers));

          $cells = $row->getCellIterator();

          $cells->setIterateOnlyExistingCells(FALSE);

          foreach ($cells as $cell) {
            $value = $cell->getValue();
            $value = drupal_strlen($value) ? trim($value) : '';

            if (!$j && $keyed_by_headers) {
              $value = drupal_strlen($value) ? $value : $k;

              phpexcel_invoke(
                'import',
                'pre cell',
                $value,
                $cell,
                array('keyed_by_headers' => $keyed_by_headers),
                $k,
                $j
              );

              $headers[$i][] = $value;
            }
            elseif ($keyed_by_headers) {
              phpexcel_invoke(
                'import',
                'pre cell',
                $value,
                $cell,
                array('keyed_by_headers' => $keyed_by_headers),
                $k,
                $j
              );

              $data[$i][$j - 1][$headers[$i][$k]] = $value;

              phpexcel_invoke(
                'import',
                'post cell',
                $data[$i][$j - 1][$headers[$i][$k]],
                $cell,
                array('keyed_by_headers' => $keyed_by_headers),
                $k,
                $j
              );
            }
            else {
              phpexcel_invoke(
                'import',
                'pre cell',
                $value,
                $cell,
                array('keyed_by_headers' => $keyed_by_headers),
                $k,
                $j
              );

              $data[$i][$j][] = $value;

              phpexcel_invoke(
                'import',
                'post cell',
                $data[$i][$j][$k],
                $cell,
                array('keyed_by_headers' => $keyed_by_headers),
                $k,
                $j
              );
            }

            $k++;
          }

          $j++;
        }

        if (!$keyed_by_worksheet) {
          $i++;
        }
      }

      return $data;
    }
    else {
      watchdog('phpexcel', "Couldn't find the PHPExcel library. Excel import aborted.", array(), WATCHDOG_ERROR);

      return PHPEXCEL_ERROR_LIBRARY_NOT_FOUND;
    }
  }
  else {
    watchdog('phpexcel', "The path '@path' is not readable. Excel import aborted.", array('@path' => $path));

    return PHPEXCEL_ERROR_FILE_NOT_READABLE;
  }
}

/**
 * Invokes phpexcel hooks
 * We need a custom hook-invoke method, because we need to pass parameters by
 * reference.
 */
function phpexcel_invoke($hook, $op, &$data, $phpexcel, $options, $column = NULL, $row = NULL) {
  foreach (module_implements('phpexcel_' . $hook) as $module) {
    $function = $module . '_phpexcel_' . $hook;

    $function($op, $data, $phpexcel, $options, $column, $row);
  }
}

/**
 * Munges the filename in the path.
 * We can't use drupals file_munge_filename() directly because the $path variable
 * contains the path as well.
 * Separate the filename from the directory structure, munge it and return.
 *
 * @param string $path
 *
 * @return string
 */
function phpexcel_munge_filename($path) {
  $parts = explode('/', $path);

  $filename = array_pop($parts);

  return implode('/', $parts) . '/' . file_munge_filename($filename, 'xls xlsx');
}
