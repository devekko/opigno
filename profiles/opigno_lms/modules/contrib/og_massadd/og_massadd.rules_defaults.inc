<?php

/**
 * @file
 * Rules integration for the Organic groups Mass Add.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_default_rules_configuration().
 */
function og_massadd_default_rules_configuration() {
  $items['rules_og_massadd'] = entity_import('rules_config', '{ "rules_og_massadd" : {
    "LABEL" : "add_og_membership",
    "PLUGIN" : "action set",
    "REQUIRES" : [ "og", "rules" ],
    "ACCESS_EXPOSED" : "1",
    "USES VARIABLES" : { "user" : { "label" : "user", "type" : "user" } },
    "ACTION SET" : [
      { "og_group_content_add" : { "entity" : [ "user" ], "group" : [ "site:og-context--node" ] } },
      { "drupal_message" : { "message" : "User [user:name] added to group" } }
    ]
  }
}');

  return $items;
}
