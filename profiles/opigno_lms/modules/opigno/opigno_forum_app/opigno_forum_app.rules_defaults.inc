<?php

/**
 * @file
 * Rules hook definitions.
 */
 
 function opigno_forum_app_default_rules_configuration() {
  $items = array();
  $item = '{ "rules_forum_add" : {
    "LABEL" : "Forum Add",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "course", "Forum", "og" ],
    "REQUIRES" : [ "rules", "og" ],
    "ON" : [ "node_insert" ],
    "IF" : [
      { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "course" : "course" } } } }
    ],
    "DO" : [
      { "get_system_text_variable" : {
          "USING" : { "variable" : "forum_nav_vocabulary" },
          "PROVIDE" : { "variable_added" : { "forum_vid" : "Forum vocabulary id" } }
        }
      },
      { "data_convert" : {
          "USING" : { "type" : "integer", "value" : [ "forum-vid" ] },
          "PROVIDE" : { "conversion_result" : { "forum_vid_int" : "forum_vid" } }
        }
      },
      { "entity_fetch" : {
          "USING" : { "type" : "taxonomy_vocabulary", "id" : [ "forum-vid-int" ] },
          "PROVIDE" : { "entity_fetched" : { "forum_vid_voc" : "forum_vid_voc" } }
        }
      },
      { "entity_create" : {
          "USING" : {
            "type" : "taxonomy_term",
            "param_name" : "[node:title]",
            "param_vocabulary" : [ "forum-vid-voc" ]
          },
          "PROVIDE" : { "entity_created" : { "forum_term" : "Forum" } }
        }
      },
      { "entity_save" : { "data" : [ "forum-term" ], "immediate" : 1 } },
      { "og_group_content_add" : { "entity" : [ "forum-term" ], "group" : [ "node" ] } }
    ]
  }
}';
  $items['rules_forum_add']=rules_import($item);
  return $items;
}