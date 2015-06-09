<?php
/**
 * @file
 * opigno_features_content_type_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opigno_features_content_type_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
