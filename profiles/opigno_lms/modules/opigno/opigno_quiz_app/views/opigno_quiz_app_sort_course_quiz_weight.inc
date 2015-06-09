<?php

/**
 * @file
 * View sort handler to sort quizzes by weight inside a group.
 */

class opigno_quiz_app_sort_course_quiz_weight extends views_handler_sort {

  /**
   * Called to add the sort to a query.
   */
  function query() {
    $this->ensure_my_table();

    if (isset($this->view->argument['og_group_ref_target_id']->value[0])) {
      $gid = $this->view->argument['og_group_ref_target_id']->value[0];
      $this->query->add_where(
        isset($this->options['group']) ? $this->options['group'] : 0,
        db_or()->condition($this->table_alias . '.gid', $gid)
      );
    }
    // Add the field.
    $this->query->add_orderby($this->table_alias, $this->real_field, $this->options['order']);
  }

}
