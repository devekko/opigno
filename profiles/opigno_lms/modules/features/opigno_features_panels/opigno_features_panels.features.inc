<?php
/**
 * @file
 * opigno_features_panels.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opigno_features_panels_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
}
