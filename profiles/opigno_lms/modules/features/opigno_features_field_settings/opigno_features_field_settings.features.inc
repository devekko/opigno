<?php
/**
 * @file
 * opigno_features_field_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opigno_features_field_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
