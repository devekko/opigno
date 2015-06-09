<?php

/**
 * @file
 * Provide documentation to phpexcel hooks.
 *
 * phpexcel provides several hooks which can allow a developer to have more
 * control over the export or import.
 */

/**
 * Export
 *
 * @param string $op
 *        The current operation
 * @param array|string &$data
 *        The data. Depends on the operation. See documentation below for more
 *        information
 * @param PHPExcel|PHPExcel_Worksheet $phpexcel
 *        The current object used. Can either be a PHPExcel object when working
 *        with the excel file in general or a PHPExcel_Worksheet object when
 *        iterating through the worksheets.
 * @param array $options
 *        The options for the phpexcel module
 * @param int $column
 *        (optional) the column number
 * @param int $row
 *        (optional) the row number
 */
function hook_phpexcel_export($op, &$data, $phpexcel, $options, $column = NULL, $row = NULL) {
  switch ($op) {
    case 'headers':
      /**
       * The $data parameter will contain the headers in array form. The headers
       * have not been added to the document yet and can be altered at this
       * point.
       *
       * The $phpexcel parameter will contain the PHPExcel object.
       */
      break;

    case 'new sheet':
      /**
       * The $data parameter will contain the sheet ID. This is a new sheet and
       * can be altered.
       *
       * The $phpexcel parameter will contain the PHPExcel_Worksheet object.
       */
      break;

    case 'data':
      /**
       * The $data parameter contains all the data to be exported as a
       * 3-dimensional array. The data has not been exported yet and can be
       * altered at this point.
       *
       * The $phpexcel parameter contains the PHPExcel object
       */
      break;

    case 'pre cell':
      /**
       * The $data parameter contains the call value to be rendered. The value
       * has not been added yet and can still be altered.
       *
       * The $phpexcel parameter contains the PHPExcel_Worksheet object.
       *
       * The $column and $row parameters are set.
       */
      break;

    case 'post cell':
      /**
       * The $data parameter contains the call value that was rendered. This
       * value can not be altered anymore.
       *
       * The $phpexcel parameter contains the PHPExcel_Worksheet object.
       *
       * The $column and $row parameters are set.
       */
      break;
  }
}

/**
 * Import
 *
 * @param string $op
 *        The current operation
 * @param * &$data
 *        The data. Depends on the operation. See documentation below for more
 *        information
 * @param PHPExcel_Reader|PHPExcel_Worksheet|PHPExcel_Cell $phpexcel
 *        The current object used. Can either be a PHPExcel_Reader object when
 *        loading the Excel file, a PHPExcel_Worksheet object when iterating
 *        through the worksheets or a PHPExcel_Cell object when reading data
 *        from a cell
 * @param array $options
 *        The options for the phpexcel import
 * @param int $column
 *        (optional) the column number
 * @param int $row
 *        (optional) the row number
 */
function hook_phpexcel_import($op, &$data, $phpexcel, $options, $column = NULL, $row = NULL) {
  switch ($op) {
    case 'full':
      /**
       * The $data parameter will contain the fully loaded Excel file, returned
       * by the PHPExcel_Reader object.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'sheet':
      /**
       * The $data parameter will contain the current PHPExcel_Worksheet.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'row':
      /**
       * The $data parameter will contain the current PHPExcel_Row.
       *
       * The $phpexcel parameter will contain the PHPExcel_Reader object.
       */
      break;

    case 'pre cell':
      /**
       * The $data parameter will contain the current cell value. The value has
       * not been added to the data array and can still be altered.
       *
       * The $phpexcel parameter will contain the PHPExcel_Cell object.
       *
       * The $column and $row parameters are set.
       */
      break;

    case 'post cell':
      /**
       * The $data parameter will contain the current cell value inside the data
       * array. The value can be altered.
       *
       * The $phpexcel parameter will contain the PHPExcel_Cell object.
       *
       * The $column and $row parameters are set.
       */
      break;
  }
}