<?php

/**
 * Menu function callback for getting the forlder content via AJAX.
 * Returns a JSON object with a 'data' key for the HTML table and a 'parent' key for the parent
 * taxonomy term tid. A 'ops_links' key stores the folder menu.
 */
function tft_ajax_get_folder() {
  $tid = $_GET['tid'];

  $og_nid = tft_get_og_nid($tid);
  
  if (!$tid && $tid != 0) {
    return drupal_json_output(array('error' => 1, 'data' => t("No valid identifier received")));
  }
  elseif (!tft_term_access($tid)) {
    return drupal_json_output(array('error' => 1, 'data' => t("You do not have access to this folder.")));
  }
  
  $content = tft_content_table($tid, $og_nid);

  $parent = tft_get_parent_tid($tid, $og_nid);
  
  $ops_links = tft_get_folder_operation_links($tid, $og_nid);
  
  drupal_json_output(array('data' => $content, 'parent' => $parent, 'ops_links' => $ops_links));
}
