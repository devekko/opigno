<?php

/**
 * @file
 * Default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function opigno_notifications_app_default_rules_configuration() {
  $items = array();
  $items['rules_notifications_add'] = entity_import('rules_config', '{ "rules_notifications_add" : {
    "LABEL" : "Notifications Add",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "notifications", "og", "opigno" ],
    "REQUIRES" : [ "rules", "rules_conditional", "og", "rules_i18n" ],
    "ON" : [ "node_insert" ],
    "IF" : [
      { "node_is_of_type" : {
          "node" : [ "node" ],
          "type" : { "value" : { "notification" : "notification" } }
        }
      }
    ],
    "DO" : [
      { "variable_add" : {
          "USING" : { "type" : "list\u003Centity\u003E", "value" : [ "" ] },
          "PROVIDE" : { "variable_added" : { "users_to_send_mail_to" : "users_to_send_mail_to" } }
        }
      },
      { "CONDITIONAL" : [
          {
            "IF" : { "data_is" : { "data" : [ "node:notification_send_email" ], "value" : 1 } },
            "DO" : [
              { "og_get_members" : {
                  "USING" : { "group_content" : [ "node" ] },
                  "PROVIDE" : { "group_members" : { "group_members" : "List of group members" } }
                }
              },
              { "LOOP" : {
                  "USING" : { "list" : [ "group-members" ] },
                  "ITEM" : { "members" : "members" },
                  "DO" : [
                    { "list_add" : {
                        "list" : [ "users-to-send-mail-to" ],
                        "item" : [ "members" ],
                        "unique" : 1
                      }
                    }
                  ]
                }
              },
              { "LOOP" : {
                  "USING" : { "list" : [ "users-to-send-mail-to" ] },
                  "ITEM" : { "send_mail" : "send_mail" },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "entity_is_of_type" : { "entity" : [ "send-mail" ], "type" : "user" } },
                          "DO" : [
                            { "mail" : {
                                "to" : [ "send-mail:mail" ],
                                "subject" : "Notification regarding [node:title]",
                                "message" : "Dear [send-mail:name],\r\n\r\nA new notification has been added by a teacher. Here is its content:\r\n[node:field-notification-message]\r\n\r\nPlease login at [site:url] to discover more.\r\n\r\n[site:name]",
                                "language" : [ "site:current-page:language" ]
                              }
                            }
                          ]
                        }
                      ]
                    }
                  ]
                }
              }
            ]
          }
        ]
      }
    ]
  }
}');
  return $items;
}