<?php

/**
 * @file
 * Define default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function tft_default_rules_configuration() {
  $items = array();

  $items['rules_create_folder_for_course'] = entity_import('rules_config', '{ "rules_create_folder_for_course" : {
      "LABEL" : "Create folder for Course",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "OG", "Opigno", "Taxonomy File Tree" ],
      "REQUIRES" : [ "rules", "tft" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "course" : "course" } } } }
      ],
      "DO" : [ { "tft_rules_create_og_root_folder" : { "group" : [ "node" ] } } ]
    }
  }');

  return $items;
}
