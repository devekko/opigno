<?php

/**
 * Menu callback function the file explorer
 *
 * @param int|string $tid = 'all'
 *        The term tid or 'all' for all terms.
 *
 * @return string
 *        The HTML
 */
function tft($tid = 'all', $gid = NULL) {
  // Check that all the settings are set.
  tft_check_vocabulary_setting();

  if ($tid == 'all' || !(int) $tid) {
    if (user_access(TFT_ACCESS_FULL_TREE)) {
      $tid = 0;
    }
    else {
      drupal_access_denied();
      return;
    }
  }

  // Check if the user has access to this tree
  if (!tft_term_access($tid)) {
    drupal_access_denied();
    return;
  }

  if ($tid) {
    $name = db_query("SELECT name FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $tid))->fetchField();
  }
  else {
    $name = t("Root");
  }

  // Store the URL query. Need the current path for some AJAX callbacks
  $_SESSION['tft']['q'] = $_GET['q'];

  // Store the current term tid
  $_SESSION['tft']['root_tid'] = $tid;

  // Add CSS and Javascript files
  $path = drupal_get_path('module', 'tft');
  drupal_add_js(array('tftDirectory' => drupal_get_path('module', 'tft'), 'cleanUrl' => variable_get('clean_url', 0)), 'setting');
  drupal_add_js($path . '/js/jquery.tablesorter.min.js');
  drupal_add_js($path . '/js/tft.js');
  drupal_add_css($path . '/css/tft.css');

  // Start the html
  $html = '';

  // Get the themed file explorer
  //$html .= theme('tft_folder_explorer', tft_output_tree(tft_folder_tree($tid)), variable_get('tft_vocabulary_vid', 0));

  // Get the themed title bar
  $html .= theme('tft_folder_menu', array('name' => $name, 'path' => $path, 'ops_links' => tft_get_folder_operation_links($tid)));

  // Prepare the folder content area
  $html .= '<div id="folder-content-container">' . tft_content_table($tid, $gid) . '</div>';

  return $html;
}

/**
 * Menu callback function the OG file explorer
 *
 * @param int $nid
 *        The OG nid
 *
 * @return string
 *        The HTML
 */
function tft_og($nid) {
  // Check that all the settings are set.
  tft_check_vocabulary_setting();

  // Check if the user can access content of this group
  if (!node_access('view', node_load($nid))) {
    drupal_access_denied();
    return;
  }

  // Get the term tid
  $tid = db_query("SELECT tid FROM {tft_tid_og_nid} WHERE og_nid = :nid", array(':nid' => $nid))->fetchField();

  // Set the breadcrumb
  $breadcrumb = drupal_get_breadcrumb();

  $title = db_query("SELECT {node_revision}.title FROM {node_revision}
                                      LEFT JOIN {node} ON {node}.vid = {node_revision}.vid
                                    WHERE {node}.nid = :nid", array(':nid' => $nid))->fetchField();

  $breadcrumb[] = l($title, "node/$nid");

  drupal_set_breadcrumb($breadcrumb);

  // Check if we have a valid term tid
  if (!$tid) {
    return t("No term was found for this group ! Please contact your system administrator.");
  }
  else {
    return tft($tid, $nid);
  }
}
