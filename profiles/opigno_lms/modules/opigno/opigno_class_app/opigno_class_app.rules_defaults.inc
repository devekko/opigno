<?php

/**
 * @file
 * Contains default rules for opigno class app
 */

function opigno_class_app_default_rules_configuration() {
  $items = array();
  $items['rules_og_member_subscribe_class_active_'] = entity_import('rules_config', '{ "rules_og_member_subscribe_class_active_" : {
    "LABEL" : "Class OG member subscribe (Active)",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [ "rules", "rules_conditional", "og" ],
    "ON" : [ "og_user_insert" ],
    "IF" : [
      { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
      { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
    ],
    "DO" : [
      { "variable_add" : {
          "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
          "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
        }
      },
      { "CONDITIONAL" : [
          {
            "IF" : { "node_is_of_type" : { "node" : [ "group" ], "type" : { "value" : { "class" : "class" } } } },
            "DO" : [
              { "LOOP" : {
                  "USING" : { "list" : [ "group:opigno-class-courses" ] },
                  "ITEM" : { "a_class_course" : "A class course" },
                  "DO" : [
                    { "og_subcribe_user" : { "user" : [ "account" ], "group" : [ "a-class-course" ] } }
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

  $items['rules_class_is_unpublished'] = entity_import('rules_config', '{ "rules_class_is_unpublished" : {
    "LABEL" : "Class is unpublished",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [ "rules", "rules_conditional" ],
    "ON" : [ "node_update" ],
    "IF" : [
      { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "class" : "class" } } } },
      { "data_is" : { "data" : [ "node-unchanged:status" ], "value" : "1" } },
      { "data_is" : { "data" : [ "node:status" ], "value" : "0" } }
    ],
    "DO" : [
      { "entity_query" : {
          "USING" : { "type" : "node", "property" : "type", "value" : [ "node:type" ] },
          "PROVIDE" : { "entity_fetched" : { "evaluate_all_classes" : "evaluate_all_classes" } }
        }
      },
      { "LOOP" : {
          "USING" : { "list" : [ "node:members" ] },
          "ITEM" : { "members_in_my_class" : "members_in_my_class" },
          "DO" : [
            { "LOOP" : {
                "USING" : { "list" : [ "members-in-my-class:og-membership--1" ] },
                "ITEM" : { "all_my_users_active_memberships" : "all_my_users_active_memberships" },
                "DO" : [
                  { "variable_add" : {
                      "USING" : { "type" : "integer", "value" : "0" },
                      "PROVIDE" : { "variable_added" : { "found" : "found" } }
                    }
                  },
                  { "entity_query" : {
                      "USING" : { "type" : "node", "property" : "type", "value" : [ "node:type" ] },
                      "PROVIDE" : { "entity_fetched" : { "all_classes_" : "all_classes_" } }
                    }
                  },
                  { "LOOP" : {
                      "USING" : { "list" : [ "all-classes-" ] },
                      "ITEM" : { "all_class" : "all_class" },
                      "DO" : []
                    }
                  },
                  { "CONDITIONAL" : [
                      {
                        "IF" : { "NOT component_rules_is_user_inside_another_active_class_with_the_same_course" : {
                            "user_membership" : [ "all-my-users-active-memberships" ],
                            "class" : [ "node" ]
                          }
                        },
                        "DO" : [
                          { "LOOP" : {
                              "USING" : { "list" : [ "node:opigno-class-courses" ] },
                              "ITEM" : { "my_courses" : "my_courses" },
                              "DO" : [
                                { "CONDITIONAL" : [
                                    {
                                      "IF" : { "entity_is_of_type" : {
                                          "entity" : [ "all-my-users-active-memberships:group" ],
                                          "type" : "node"
                                        }
                                      },
                                      "DO" : [
                                        { "CONDITIONAL" : [
                                            {
                                              "IF" : { "data_is" : {
                                                  "data" : [ "all-my-users-active-memberships:group:nid" ],
                                                  "value" : [ "my-courses:nid" ]
                                                }
                                              },
                                              "DO" : [
                                                { "data_set" : { "data" : [ "all-my-users-active-memberships:state" ], "value" : "3" } }
                                              ]
                                            }
                                          ]
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
            }
          ]
        }
      }
    ]
  }
}');

  $items['rules_unpublish_classes_overdue'] = entity_import('rules_config', '{ "rules_unpublish_classes_overdue" : {
    "LABEL" : "Class unpublish overdue",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "class", "cron", "og", "opigno" ],
    "REQUIRES" : [ "rules", "rules_conditional" ],
    "ON" : [ "cron" ],
    "DO" : [
      { "variable_add" : {
          "USING" : { "type" : "token", "value" : "class" },
          "PROVIDE" : { "variable_added" : { "class_text" : "class_text" } }
        }
      },
      { "entity_query" : {
          "USING" : { "type" : "node", "property" : "type", "value" : [ "class-text" ] },
          "PROVIDE" : { "entity_fetched" : { "all_classes" : "all_classes" } }
        }
      },
      { "LOOP" : {
          "USING" : { "list" : [ "all-classes" ] },
          "ITEM" : { "a_class" : "a_class" },
          "DO" : [
            { "CONDITIONAL" : [
                {
                  "IF" : { "node_is_of_type" : { "node" : [ "a-class" ], "type" : { "value" : { "class" : "class" } } } },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "NOT data_is_empty" : { "data" : [ "a-class:opigno-class-expiration" ] } },
                          "DO" : [
                            { "CONDITIONAL" : [
                                {
                                  "IF" : { "data_is" : {
                                      "data" : [ "a-class:opigno-class-expiration" ],
                                      "op" : "\u003C",
                                      "value" : "now"
                                    }
                                  },
                                  "DO" : [
                                    { "CONDITIONAL" : [
                                        {
                                          "IF" : { "data_is" : { "data" : [ "a-class:status" ], "value" : "1" } },
                                          "DO" : [ { "node_unpublish" : { "node" : [ "a-class" ] } } ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        }
                      ]
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
}');

  $items['rules_og_member_unsubscribe_class'] = entity_import('rules_config', '{ "rules_og_member_unsubscribe_class" : {
    "LABEL" : "Class OG member unsubscribe",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [ "rules", "rules_conditional", "og" ],
    "ON" : [ "og_user_delete" ],
    "IF" : [
      { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
      { "node_is_of_type" : {
          "node" : [ "og-membership:group" ],
          "type" : { "value" : { "class" : "class" } }
        }
      }
    ],
    "DO" : [
      { "LOOP" : {
          "USING" : { "list" : [ "og-membership:group:opigno-class-courses" ] },
          "ITEM" : { "course" : "course" },
          "DO" : [
            { "CONDITIONAL" : [
                {
                  "IF" : { "node_is_of_type" : { "node" : [ "course" ], "type" : { "value" : { "course" : "course" } } } },
                  "DO" : [
                    { "LOOP" : {
                        "USING" : { "list" : [ "course:members" ] },
                        "ITEM" : { "course_member" : "course_members" },
                        "DO" : [
                          { "CONDITIONAL" : [
                              {
                                "IF" : { "data_is" : { "data" : [ "course-member:uid" ], "value" : [ "account:uid" ] } },
                                "DO" : [
                                  { "LOOP" : {
                                      "USING" : { "list" : [ "course-member:og-membership" ] },
                                      "ITEM" : { "course_member_membership" : "course_member_membership" },
                                      "DO" : [
                                        { "CONDITIONAL" : [
                                            {
                                              "IF" : { "entity_is_of_type" : { "entity" : [ "course-member-membership:group" ], "type" : "node" } },
                                              "DO" : [
                                                { "CONDITIONAL" : [
                                                    {
                                                      "IF" : { "node_is_of_type" : {
                                                          "node" : [ "course-member-membership:group" ],
                                                          "type" : { "value" : { "course" : "course" } }
                                                        }
                                                      },
                                                      "DO" : [
                                                        { "CONDITIONAL" : [
                                                            {
                                                              "IF" : { "data_is" : {
                                                                  "data" : [ "course-member-membership:group:nid" ],
                                                                  "value" : [ "course:nid" ]
                                                                }
                                                              },
                                                              "DO" : [
                                                                { "CONDITIONAL" : [
                                                                    {
                                                                      "IF" : { "NOT component_rules_is_user_inside_another_active_class_with_the_same_course" : {
                                                                          "user_membership" : [ "course-member-membership" ],
                                                                          "class" : [ "og-membership:group" ]
                                                                        }
                                                                      },
                                                                      "DO" : [
                                                                        { "og_unsubscribe_user" : { "user" : [ "account" ], "group" : [ "course" ] } }
                                                                      ]
                                                                    }
                                                                  ]
                                                                }
                                                              ]
                                                            }
                                                          ]
                                                        }
                                                      ]
                                                    }
                                                  ]
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
}');

  $items['rules_class_user_was_granted_a_role'] = entity_import('rules_config', '{ "rules_class_user_was_granted_a_role" : {
    "LABEL" : "Class user was granted a role",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "TAGS" : [ "class", "og", "opigno", "role" ],
    "REQUIRES" : [ "rules", "rules_conditional", "opigno_class_app", "opigno" ],
    "ON" : { "og_user_was_granted_role" : [] },
    "DO" : [
      { "entity_fetch" : {
          "USING" : { "type" : "user", "id" : [ "user-id" ] },
          "PROVIDE" : { "entity_fetched" : { "user" : "user" } }
        }
      },
      { "entity_fetch" : {
          "USING" : { "type" : "node", "id" : [ "node-id" ] },
          "PROVIDE" : { "entity_fetched" : { "node" : "node" } }
        }
      },
      { "CONDITIONAL" : [
          {
            "IF" : { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "class" : "class" } } } },
            "DO" : [
              { "LOOP" : {
                  "USING" : { "list" : [ "node:opigno-class-courses" ] },
                  "ITEM" : { "course" : "course" },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "node_is_of_type" : { "node" : [ "course" ], "type" : { "value" : { "course" : "course" } } } },
                          "DO" : [
                            { "LOOP" : {
                                "USING" : { "list" : [ "course:members" ] },
                                "ITEM" : { "course_member" : "course_member" },
                                "DO" : [
                                  { "CONDITIONAL" : [
                                      {
                                        "IF" : { "data_is" : { "data" : [ "course-member:uid" ], "value" : [ "user:uid" ] } },
                                        "DO" : [
                                          { "class_map_role_to_course" : {
                                              "USING" : {
                                                "class_role_id" : [ "role-id" ],
                                                "clgroup_id" : [ "node-id" ],
                                                "cogroup_id" : [ "course:nid" ]
                                              },
                                              "PROVIDE" : { "course_role_id" : { "course_role_id" : "Course role id" } }
                                            }
                                          },
                                          { "og_give_og_role_to_user" : {
                                              "role" : [ "course-role-id" ],
                                              "user" : [ "user" ],
                                              "group" : [ "course" ]
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
              }
            ]
          }
        ]
      }
    ]
  }
}');

  $items['rules_class_user_was_revoked_a_role'] = entity_import('rules_config', '{ "rules_class_user_was_revoked_a_role" : {
    "LABEL" : "Class user was revoked a role",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "TAGS" : [ "class", "og", "opigno", "role" ],
    "REQUIRES" : [ "rules", "rules_conditional", "opigno_class_app", "opigno" ],
    "ON" : { "og_user_was_revoked_role" : [] },
    "DO" : [
      { "entity_fetch" : {
          "USING" : { "type" : "node", "id" : [ "node-id" ] },
          "PROVIDE" : { "entity_fetched" : { "node" : "node" } }
        }
      },
      { "entity_fetch" : {
          "USING" : { "type" : "user", "id" : [ "user-id" ] },
          "PROVIDE" : { "entity_fetched" : { "user" : "user" } }
        }
      },
      { "CONDITIONAL" : [
          {
            "IF" : { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "class" : "class" } } } },
            "DO" : [
              { "LOOP" : {
                  "USING" : { "list" : [ "node:opigno-class-courses" ] },
                  "ITEM" : { "course" : "course" },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "node_is_of_type" : { "node" : [ "course" ], "type" : { "value" : { "course" : "course" } } } },
                          "DO" : [
                            { "LOOP" : {
                                "USING" : { "list" : [ "course:members" ] },
                                "ITEM" : { "member" : "member" },
                                "DO" : [
                                  { "CONDITIONAL" : [
                                      {
                                        "IF" : { "data_is" : { "data" : [ "member:uid" ], "value" : [ "user:uid" ] } },
                                        "DO" : [
                                          { "LOOP" : {
                                              "USING" : { "list" : [ "member:og-membership" ] },
                                              "ITEM" : { "member_membership" : "member_membership" },
                                              "DO" : [
                                                { "CONDITIONAL" : [
                                                    {
                                                      "IF" : { "entity_is_of_type" : { "entity" : [ "member-membership:group" ], "type" : "node" } },
                                                      "DO" : [
                                                        { "CONDITIONAL" : [
                                                            {
                                                              "IF" : { "data_is" : { "data" : [ "member-membership:group:nid" ], "value" : [ "course:nid" ] } },
                                                              "DO" : [
                                                                { "CONDITIONAL" : [
                                                                    {
                                                                      "IF" : { "NOT component_rules_is_user_inside_another_active_class_with_the_same_course" : { "user_membership" : [ "member-membership" ], "class" : [ "node" ] } },
                                                                      "DO" : [
                                                                        { "class_map_role_to_course" : {
                                                                            "USING" : {
                                                                              "class_role_id" : [ "role-id" ],
                                                                              "clgroup_id" : [ "node-id" ],
                                                                              "cogroup_id" : [ "course:nid" ]
                                                                            },
                                                                            "PROVIDE" : { "course_role_id" : { "course_role_id" : "Course role id" } }
                                                                          }
                                                                        },
                                                                        { "og_revoke_og_role_to_user" : {
                                                                            "role" : [ "course-role-id" ],
                                                                            "user" : [ "user" ],
                                                                            "group" : [ "course" ]
                                                                          }
                                                                        }
                                                                      ]
                                                                    }
                                                                  ]
                                                                }
                                                              ]
                                                            }
                                                          ]
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


  $items['rules_class_courses_changed'] = entity_import('rules_config', '{ "rules_class_courses_changed" : {
    "LABEL" : "Class Courses changed",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [
      "rules",
      "rules_conditional",
      "og",
      "rules_i18n",
      "opigno_class_app",
      "opigno"
    ],
    "ON" : { "node_update" : [] },
    "IF" : [
      { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "class" : "class" } } } },
      { "NOT data_is" : {
          "data" : [ "node:opigno-class-courses" ],
          "value" : [ "node-unchanged:opigno-class-courses" ]
        }
      }
    ],
    "DO" : [
      { "LOOP" : {
          "USING" : { "list" : [ "node-unchanged:opigno-class-courses" ] },
          "ITEM" : { "old_courses" : "old_courses" },
          "DO" : [
            { "CONDITIONAL" : [
                {
                  "IF" : { "NOT list_contains" : { "list" : [ "node:opigno-class-courses" ], "item" : [ "old-courses" ] } },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "node_is_of_type" : {
                              "node" : [ "old-courses" ],
                              "type" : { "value" : { "course" : "course" } }
                            }
                          },
                          "DO" : [
                            { "CONDITIONAL" : [
                                {
                                  "IF" : { "og_entity_is_group" : { "entity" : [ "old-courses" ] } },
                                  "DO" : [
                                    { "LOOP" : {
                                        "USING" : { "list" : [ "node:members" ] },
                                        "ITEM" : { "member_in_removed_course" : "member_in_removed_course" },
                                        "DO" : [
                                          { "LOOP" : {
                                              "USING" : { "list" : [ "member-in-removed-course:og-membership" ] },
                                              "ITEM" : { "members_membership" : "members membership" },
                                              "DO" : [
                                                { "CONDITIONAL" : [
                                                    {
                                                      "IF" : { "entity_is_of_type" : { "entity" : [ "members-membership:group" ], "type" : "node" } },
                                                      "DO" : [
                                                        { "CONDITIONAL" : [
                                                            {
                                                              "IF" : { "node_is_of_type" : {
                                                                  "node" : [ "members-membership:group" ],
                                                                  "type" : { "value" : { "course" : "course" } }
                                                                }
                                                              },
                                                              "DO" : [
                                                                { "CONDITIONAL" : [
                                                                    {
                                                                      "IF" : { "data_is" : {
                                                                          "data" : [ "old-courses:nid" ],
                                                                          "value" : [ "members-membership:group:nid" ]
                                                                        }
                                                                      },
                                                                      "DO" : [
                                                                        { "CONDITIONAL" : [
                                                                            {
                                                                              "IF" : { "NOT component_rules_is_user_inside_another_active_class_with_the_same_course" : { "user_membership" : [ "members-membership" ], "class" : [ "node" ] } },
                                                                              "DO" : [
                                                                                { "og_unsubscribe_user" : { "user" : [ "member-in-removed-course" ], "group" : [ "old-courses" ] } },
                                                                                { "drupal_message" : { "message" : "User [member-in-removed-course:name] was removed from [old-courses:title]" } }
                                                                              ]
                                                                            }
                                                                          ]
                                                                        }
                                                                      ]
                                                                    }
                                                                  ]
                                                                }
                                                              ]
                                                            }
                                                          ]
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
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      },
      { "LOOP" : {
          "USING" : { "list" : [ "node:opigno-class-courses" ] },
          "ITEM" : { "new_courses" : "new_courses" },
          "DO" : [
            { "CONDITIONAL" : [
                {
                  "IF" : { "NOT list_contains" : {
                      "list" : [ "node-unchanged:opigno-class-courses" ],
                      "item" : [ "new-courses" ]
                    }
                  },
                  "DO" : [
                    { "CONDITIONAL" : [
                        {
                          "IF" : { "node_is_of_type" : {
                              "node" : [ "new-courses" ],
                              "type" : { "value" : { "course" : "course" } }
                            }
                          },
                          "DO" : [
                            { "CONDITIONAL" : [
                                {
                                  "IF" : { "og_entity_is_group" : { "entity" : [ "new-courses" ] } },
                                  "DO" : [
                                    { "LOOP" : {
                                        "USING" : { "list" : [ "node:members" ] },
                                        "ITEM" : { "members_in_class" : "members in class" },
                                        "DO" : [
                                          { "og_subcribe_user" : { "user" : [ "members-in-class" ], "group" : [ "new-courses" ] } },
                                          { "drupal_message" : { "message" : "[members-in-class:name] added to [new-courses:title]" } },
                                          { "LOOP" : {
                                              "USING" : { "list" : [ "members-in-class:roles" ] },
                                              "ITEM" : { "member_role" : "member_role" },
                                              "DO" : [
                                                { "class_map_role_to_course" : {
                                                    "USING" : {
                                                      "class_role_id" : [ "member-role" ],
                                                      "clgroup_id" : [ "node:nid" ],
                                                      "cogroup_id" : [ "new-courses:nid" ]
                                                    },
                                                    "PROVIDE" : { "course_role_id" : { "course_role_id" : "Course role id" } }
                                                  }
                                                },
                                                { "CONDITIONAL" : [
                                                    {
                                                      "IF" : { "NOT data_is" : { "data" : [ "course-role-id" ], "value" : "0" } },
                                                      "DO" : [
                                                        { "og_give_og_role_to_user" : {
                                                            "role" : [ "course-role-id" ],
                                                            "user" : [ "members-in-class" ],
                                                            "group" : [ "new-courses" ]
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
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        }
                      ]
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
}');


  $items['rules_class_user_status_changed_'] = entity_import('rules_config', '{ "rules_class_user_status_changed_" : {
    "LABEL" : "Class User Status changed ",
    "PLUGIN" : "reaction rule",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [ "rules_conditional", "rules", "og" ],
    "ON" : [ "og_membership_update" ],
    "DO" : [
      { "CONDITIONAL" : [
          {
            "IF" : { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
            "DO" : [
              { "CONDITIONAL" : [
                  {
                    "IF" : { "node_is_of_type" : {
                        "node" : [ "og-membership:group" ],
                        "type" : { "value" : { "class" : "class" } }
                      }
                    },
                    "DO" : [
                      { "CONDITIONAL" : [
                          {
                            "IF" : { "entity_is_of_type" : { "entity" : [ "og-membership:entity" ], "type" : "user" } },
                            "DO" : [
                              { "LOOP" : {
                                  "USING" : { "list" : [ "og-membership:entity:og-membership" ] },
                                  "ITEM" : { "user_memberships" : "user_memberships" },
                                  "DO" : [
                                    { "LOOP" : {
                                        "USING" : { "list" : [ "og-membership:group:opigno-class-courses" ] },
                                        "ITEM" : { "class_course" : "class course" },
                                        "DO" : [
                                          { "CONDITIONAL" : [
                                              {
                                                "IF" : { "entity_is_of_type" : { "entity" : [ "user-memberships:group" ], "type" : "node" } },
                                                "DO" : [
                                                  { "CONDITIONAL" : [
                                                      {
                                                        "IF" : { "data_is" : {
                                                            "data" : [ "class-course:nid" ],
                                                            "value" : [ "user-memberships:group:nid" ]
                                                          }
                                                        },
                                                        "DO" : [
                                                          { "CONDITIONAL" : [
                                                              {
                                                                "IF" : { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
                                                                "DO" : [
                                                                  { "data_set" : { "data" : [ "user-memberships:state" ], "value" : "1" } }
                                                                ]
                                                              },
                                                              {
                                                                "ELSE IF" : { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
                                                                "DO" : [
                                                                  { "CONDITIONAL" : [
                                                                      {
                                                                        "IF" : { "NOT data_is" : { "data" : [ "user-memberships:state" ], "value" : "1" } },
                                                                        "DO" : [
                                                                          { "CONDITIONAL" : [
                                                                              {
                                                                                "IF" : { "NOT data_is" : { "data" : [ "og-membership-unchanged:state" ], "value" : "1" } },
                                                                                "DO" : [
                                                                                  { "data_set" : {
                                                                                      "data" : [ "user-memberships:state" ],
                                                                                      "value" : [ "og-membership:state" ]
                                                                                    }
                                                                                  }
                                                                                ]
                                                                              }
                                                                            ]
                                                                          }
                                                                        ]
                                                                      }
                                                                    ]
                                                                  }
                                                                ]
                                                              }
                                                            ]
                                                          }
                                                        ]
                                                      }
                                                    ]
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
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  }
                ]
              }
            ]
          }
        ]
      }
    ]
  }
}');

  $items['rules_is_user_inside_another_active_class_with_the_same_course'] = entity_import('rules_config', '{ "rules_is_user_inside_another_active_class_with_the_same_course" : {
    "LABEL" : "Is user inside another active class with the same course",
    "PLUGIN" : "rule condition set",
    "TAGS" : [ "class", "og", "opigno" ],
    "REQUIRES" : [ "rules_conditional", "rules" ],
    "USES VARIABLES" : {
      "user_membership" : { "label" : "User membership", "type" : "og_membership" },
      "class" : { "label" : "Class", "type" : "node" }
    },
    "DO" : [
      { "variable_add" : {
          "USING" : { "type" : "integer", "value" : "0" },
          "PROVIDE" : { "variable_added" : { "found" : "found" } }
        }
      },
      { "variable_add" : {
          "USING" : { "type" : "token", "value" : "class" },
          "PROVIDE" : { "variable_added" : { "class_text" : "class_text" } }
        }
      },
      { "entity_query" : {
          "USING" : { "type" : "node", "property" : "type", "value" : [ "class-text" ] },
          "PROVIDE" : { "entity_fetched" : { "all_classes" : "all_classes" } }
        }
      },
      { "LOOP" : {
          "USING" : { "list" : [ "all-classes" ] },
          "ITEM" : { "a_class" : "a_class" },
          "DO" : [
            { "CONDITIONAL" : [
                {
                  "IF" : { "node_is_of_type" : { "node" : [ "a-class" ], "type" : { "value" : { "class" : "class" } } } },
                  "DO" : [
                    { "LOOP" : {
                        "USING" : { "list" : [ "a-class:members" ] },
                        "ITEM" : { "a_class_member" : "a_class_member" },
                        "DO" : [
                          { "CONDITIONAL" : [
                              {
                                "IF" : { "entity_is_of_type" : { "entity" : [ "user-membership:entity" ], "type" : "user" } },
                                "DO" : [
                                  { "CONDITIONAL" : [
                                      {
                                        "IF" : { "data_is" : {
                                            "data" : [ "user-membership:entity:uid" ],
                                            "value" : [ "a-class-member:uid" ]
                                          }
                                        },
                                        "DO" : [
                                          { "CONDITIONAL" : [
                                              {
                                                "IF" : { "NOT data_is" : { "data" : [ "a-class:nid" ], "value" : [ "class:nid" ] } },
                                                "DO" : [
                                                  { "CONDITIONAL" : [
                                                      {
                                                        "IF" : { "node_is_of_type" : { "node" : [ "class" ], "type" : { "value" : { "class" : "class" } } } },
                                                        "DO" : [
                                                          { "LOOP" : {
                                                              "USING" : { "list" : [ "a-class:opigno-class-courses" ] },
                                                              "ITEM" : { "a_course" : "a_course" },
                                                              "DO" : [
                                                                { "CONDITIONAL" : [
                                                                    {
                                                                      "IF" : { "entity_is_of_type" : { "entity" : [ "user-membership:group" ], "type" : "node" } },
                                                                      "DO" : [
                                                                        { "CONDITIONAL" : [
                                                                            {
                                                                              "IF" : { "node_is_of_type" : {
                                                                                  "node" : [ "user-membership:group" ],
                                                                                  "type" : { "value" : { "course" : "course" } }
                                                                                }
                                                                              },
                                                                              "DO" : [
                                                                                { "CONDITIONAL" : [
                                                                                    {
                                                                                      "IF" : { "data_is" : { "data" : [ "user-membership:group:nid" ], "value" : [ "a-course:nid" ] } },
                                                                                      "DO" : [
                                                                                        { "CONDITIONAL" : [
                                                                                            {
                                                                                              "IF" : { "data_is" : { "data" : [ "a-class:status" ], "value" : "1" } },
                                                                                              "DO" : [ { "data_set" : { "data" : [ "found" ], "value" : "1" } } ]
                                                                                            }
                                                                                          ]
                                                                                        }
                                                                                      ]
                                                                                    }
                                                                                  ]
                                                                                }
                                                                              ]
                                                                            }
                                                                          ]
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
                                            ]
                                          }
                                        ]
                                      }
                                    ]
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
      }
    ],
    "RESULT" : [ { "data_is" : { "data" : [ "found" ], "value" : "1" } } ]
  }
}');

  return $items;
}