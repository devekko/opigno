<?php

/**
 * @file
 * Default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function opigno_quiz_app_default_rules_configuration() {
  $items = array();
  $items['rules_get_course_required_quizzes'] = entity_import('rules_config', '{ "rules_get_course_required_quizzes" : {
      "LABEL" : "Get course required Quizzes",
      "PLUGIN" : "rule",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "course" : { "label" : "Course node", "type" : "node" },
        "quizzes" : {
          "label" : "Quizzes",
          "type" : "list\u003Cnode\u003E",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "course" ], "field" : "course_required_quiz_ref" } }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "course:course-required-quiz-ref" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "entity_fetch" : {
                  "USING" : { "type" : "node", "id" : [ "list-item:nid" ] },
                  "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
                }
              },
              { "list_add" : { "list" : [ "quizzes" ], "item" : [ "entity-fetched" ], "unique" : 1 } }
            ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "quizzes" ]
    }
  }');
  $items['rules_calculate_course_score'] = entity_import('rules_config', '{ "rules_calculate_course_score" : {
      "LABEL" : "Calculate course score",
      "PLUGIN" : "rule",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "course" : { "label" : "Course", "type" : "node" },
        "user" : { "label" : "Student", "type" : "user" },
        "final_score" : { "label" : "Final score", "type" : "decimal", "parameter" : false }
      },
      "DO" : [
        { "data_set" : { "data" : [ "final-score" ], "value" : "0" } },
        { "component_rules_get_course_required_quizzes" : {
            "USING" : { "course" : [ "course" ] },
            "PROVIDE" : { "quizzes" : { "quizzes" : "Quizzes" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "quizzes" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "component_rules_calculate_quiz_weighted_score" : {
                  "USING" : { "quiz" : [ "list-item" ], "user" : [ "user" ] },
                  "PROVIDE" : { "weighted_score" : { "weighted_score" : "Weighted score" } }
                }
              },
              { "data_calc" : {
                  "USING" : {
                    "input_1" : [ "weighted-score" ],
                    "op" : "+",
                    "input_2" : [ "final-score" ]
                  },
                  "PROVIDE" : { "result" : { "result" : "Calculation result" } }
                }
              },
              { "data_set" : { "data" : [ "final-score" ], "value" : [ "result" ] } }
            ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "final_score" ]
    }
  }');
  $items['rules_calculate_quiz_weighted_score'] = entity_import('rules_config', '{ "rules_calculate_quiz_weighted_score" : {
      "LABEL" : "Calculate quiz weighted score",
      "PLUGIN" : "rule",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules", "opigno_quiz_app" ],
      "USES VARIABLES" : {
        "quiz" : { "label" : "Quiz", "type" : "node" },
        "user" : { "label" : "Quiz taker", "type" : "user" },
        "weighted_score" : { "label" : "Weighted score", "type" : "decimal", "parameter" : false }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "quiz" ], "field" : "quiz_weight" } }
      ],
      "DO" : [
        { "opigno_quiz_app_rules_quiz_get_highest_score" : {
            "USING" : { "node" : [ "quiz" ], "property" : [ "user" ] },
            "PROVIDE" : { "quiz_score" : { "quiz_score" : "Quiz score" } }
          }
        },
        { "data_calc" : {
            "USING" : {
              "input_1" : [ "quiz-score" ],
              "op" : "*",
              "input_2" : [ "quiz:quiz-weight" ]
            },
            "PROVIDE" : { "result" : { "result" : "Calculation result" } }
          }
        },
        { "data_set" : { "data" : [ "weighted-score" ], "value" : [ "result" ] } }
      ],
      "PROVIDES VARIABLES" : [ "weighted_score" ]
    }
  }');
  $items['rules_user_has_answered_all_required_quizzes'] = entity_import('rules_config', '{ "rules_user_has_answered_all_required_quizzes" : {
      "LABEL" : "User has answered all required quizzes",
      "PLUGIN" : "rule condition set",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules_conditional", "rules", "opigno_quiz_app" ],
      "USES VARIABLES" : {
        "course" : { "label" : "Course", "type" : "node" },
        "user" : { "label" : "User", "type" : "user" },
        "answered_all_required_quizzes" : {
          "label" : "Has answered all required quizzes",
          "type" : "boolean",
          "parameter" : false
        }
      },
      "DO" : [
        { "data_set" : { "data" : [ "answered-all-required-quizzes" ], "value" : 1 } },
        { "component_rules_get_course_required_quizzes" : {
            "USING" : { "course" : [ "course" ] },
            "PROVIDE" : { "quizzes" : { "quizzes" : "Quizzes" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "quizzes" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "CONDITIONAL" : [
                  {
                    "IF" : { "NOT opigno_quiz_app_rules_has_passed_quiz" : { "node" : [ "list-item" ], "user" : [ "user" ] } },
                    "DO" : [
                      { "data_set" : { "data" : [ "answered-all-required-quizzes" ], "value" : 0 } }
                    ]
                  }
                ]
              }
            ]
          }
        }
      ],
      "RESULT" : [
        { "data_is" : { "data" : [ "answered-all-required-quizzes" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_user_has_passed_all_required_quizzes'] = entity_import('rules_config', '{ "rules_user_has_passed_all_required_quizzes" : {
      "LABEL" : "User has passed all required quizzes",
      "PLUGIN" : "rule condition set",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules_conditional", "rules", "opigno_quiz_app" ],
      "USES VARIABLES" : {
        "course" : { "label" : "Course", "type" : "node" },
        "user" : { "label" : "User", "type" : "user" },
        "passed_all_required_quizzes" : {
          "label" : "Has passed all required quizzes",
          "type" : "boolean",
          "parameter" : false
        }
      },
      "DO" : [
        { "data_set" : { "data" : [ "passed-all-required-quizzes" ], "value" : 1 } },
        { "component_rules_get_course_required_quizzes" : {
            "USING" : { "course" : [ "course" ] },
            "PROVIDE" : { "quizzes" : { "quizzes" : "Quizzes" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "quizzes" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "CONDITIONAL" : [
                  {
                    "IF" : { "NOT opigno_quiz_app_rules_has_passed_quiz" : { "node" : [ "list-item" ], "user" : [ "user" ] } },
                    "DO" : [
                      { "data_set" : { "data" : [ "passed-all-required-quizzes" ], "value" : 0 } }
                    ]
                  }
                ]
              }
            ]
          }
        }
      ],
      "RESULT" : [
        { "data_is" : { "data" : [ "passed-all-required-quizzes" ], "value" : 1 } }
      ]
    }
  }');
  $items['rules_check_user_completed_course'] = entity_import('rules_config', '{ "rules_check_user_completed_course" : {
      "LABEL" : "Check user completed course",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules", "og", "opigno_quiz_app" ],
      "ON" : [ "opigno_quiz_app_rules_quiz_passed" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "og_group_ref" } },
        { "og_entity_is_group_content" : { "entity" : [ "node" ] } },
        { "component_rules_user_has_passed_all_required_quizzes" : { "course" : [ "node:og-group-ref:0" ], "user" : [ "user" ] } }
      ],
      "DO" : [ { "drupal_message" : { "message" : "You finished this course." } } ]
    }
  }');
  $items['rules_get_course_from_quiz'] = entity_import('rules_config', '{ "rules_get_course_from_quiz" : {
      "LABEL" : "Get course from quiz",
      "PLUGIN" : "rule",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "quiz" : { "label" : "Quiz", "type" : "node" },
        "course" : { "label" : "Course", "type" : "node", "parameter" : false }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "quiz" ], "field" : "og_group_ref" } },
        { "NOT data_is_empty" : { "data" : [ "quiz:og-group-ref" ] } }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "quiz:og-group-ref:0:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        },
        { "data_set" : { "data" : [ "course" ], "value" : [ "entity-fetched" ] } }
      ],
      "PROVIDES VARIABLES" : [ "course" ]
    }
  }');
  $items['rules_quiz_is_part_of_a_course'] = entity_import('rules_config', '{ "rules_quiz_is_part_of_a_course" : {
      "LABEL" : "Quiz is part of a course",
      "PLUGIN" : "rule condition set",
      "TAGS" : [ "og", "opigno", "quiz", "opigno_quiz_app" ],
      "REQUIRES" : [ "rules_conditional", "rules" ],
      "USES VARIABLES" : { "quiz" : { "label" : "Quiz", "type" : "node" } },
      "DO" : [
        { "component_rules_get_course_from_quiz" : {
            "USING" : { "quiz" : [ "quiz" ] },
            "PROVIDE" : { "course" : { "course" : "Course" } }
          }
        }
      ],
      "RESULT" : [ { "NOT data_is_empty" : { "data" : [ "course" ] } } ]
    }
  }');
  return $items;
}
