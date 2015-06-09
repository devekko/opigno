<?php

/**
 * @file
 * Defines all page callbacks.
 */

/**
 * Page callback: take quiz. See if fullscreen is available.
 */
function opigno_quiz_app_quiz_take($node) {
  _opigno_quiz_app_enable_fullscreen($node);
  return quiz_take($node);
}

/** 
 * Page callback: view quiz results for the current user.
 * @see 
 */
function opigno_quiz_app_current_user_results() {
  global $user;
  module_load_include('inc', 'quiz', 'quiz.pages');
  return quiz_get_user_results($user->uid);
}

/**
 * Page callback: view user results.
 *
 * @param  int $uid
 *
 * @return string
 */
function opigno_quiz_app_user_results($uid = NULL) {
  if (!isset($uid)) {
    global $user;
    $uid = $user->uid;
    $account = clone $user;
  }
  else {
    $account = user_load($uid);
  }

  if (empty($uid)) {
    drupal_set_message(t("Could not find any user to display results for."), 'error');
    drupal_not_found();
  }

  $scores = array();
  foreach (og_get_groups_by_user($account, 'node') as $gid => $nid) {
    $node = node_load($nid);
    if ($node->type == OPIGNO_COURSE_BUNDLE) {
      if ($score_data = opigno_quiz_app_get_course_data_result($uid, $nid)) {
        $scores[$node->title] = $score_data;
        $scores[$node->title]['node'] = $node;
      }
    }
  }

  $path = drupal_get_path('module', 'opigno_quiz_app');
  drupal_add_js($path . '/js/opigno_quiz_app.js');
  drupal_add_css($path . '/css/opigno_quiz_app.css');

  return theme('opigno_quiz_app_user_results', array('user' => $account, 'results' => $scores));
}

/**
 * Page callback: view all user results for a specific course.
 *
 * @param  stdClass $node
 *
 * @return string
 */
function opigno_quiz_app_course_results($node) {
  if (empty($node->nid)) {
    drupal_set_message(t("Could not find the course."), 'error');
    drupal_not_found();
  }

  $state = isset($_SESSION['opigno_quiz_app']['state_filter'][request_path()]) ? $_SESSION['opigno_quiz_app']['state_filter'][request_path()] : OG_STATE_ACTIVE;
  $scores = array();
  foreach (opigno_get_users_in_group($node->nid, $state) as $uid => $account) {
    if (!og_user_access('node', $node->nid, 'skip display of results', $account,FALSE,TRUE) && $data = opigno_quiz_app_get_course_data_result($uid, $node->nid, TRUE)) {
      $scores[$uid] = $data;
      $scores[$uid]['user'] = $account;
    }
  }

  $path = drupal_get_path('module', 'opigno_quiz_app');
  drupal_add_js($path . '/js/opigno_quiz_app.js');
  drupal_add_css($path . '/css/opigno_quiz_app.css');

  $form = render(drupal_get_form('opigno_quiz_app_filter_by_status_form'));
  return $form . theme('opigno_quiz_app_course_results', array('course' => $node, 'results' => $scores));
}

/**
 * Page callback: view all user results for all courses (where allowed).
 *
 * @return string
 */
function opigno_quiz_app_courses_results() {
  global $user;
  $html = '';
  $state = isset($_SESSION['opigno_quiz_app']['state_filter'][request_path()]) ? $_SESSION['opigno_quiz_app']['state_filter'][request_path()] : OG_STATE_ACTIVE;

  foreach (og_get_groups_by_user($user, 'node') as $gid => $nid) {
    $node = node_load($nid);
    if ($node->type == OPIGNO_COURSE_BUNDLE) {
      $scores = array();
      foreach (opigno_get_users_in_group($node->nid, $state) as $uid => $account) {
        // Only display results for roles that don't have the 'skip display of results' permission.
        if (!og_user_access('node', $nid, 'skip display of results', $account,FALSE,TRUE) && $data = opigno_quiz_app_get_course_data_result($uid, $node->nid, TRUE)) {
          $scores[$uid] = $data;
          $scores[$uid]['user'] = $account;
        }
      }

      // Are there any results to show ?
      if (!empty($scores)) {
        $header = array(
          'data' => check_plain($node->title),
        );
        $rows = array(
          array(theme('opigno_quiz_app_course_results', array('course' => $node, 'results' => $scores)))
        );
        $html .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('opigno-quiz-app-results-table', 'opigno-quiz-app-results-collapsible-table', 'opigno-quiz-app-all-courses-user-results-table'))));
      }
    }
  }

  $path = drupal_get_path('module', 'opigno_quiz_app');
  drupal_add_js($path . '/js/opigno_quiz_app.js');
  drupal_add_css($path . '/css/opigno_quiz_app.css');

  $form = render(drupal_get_form('opigno_quiz_app_filter_by_status_form'));
  return $form . $html;
}

/**
 * Page callback: sort course quizzes.
 *
 * @param  array $form
 * @param  array $form_state
 * @param  stdClass $node
 *
 * @return array
 */
function opigno_quiz_app_sort_course_quizzes_form($form, $form_state, $node) {
  $form['table'] = array(
    '#tree' => TRUE,
  );

  $form['gid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );

  foreach (opigno_quiz_app_get_course_quizzes($node) as $quiz_nid) {
    $quiz = node_load($quiz_nid);
    $form['table']["quiz_{$quiz_nid}"]['nid'] = array(
      '#type' => 'hidden',
      '#value' => $quiz_nid,
    );
    $form['table']["quiz_{$quiz_nid}"]['title'] = array(
      '#markup' => check_plain($quiz->title),
    );
    $form['table']["quiz_{$quiz_nid}"]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 50,
      '#default_value' => opigno_quiz_app_get_course_quiz_weight($node->nid, $quiz_nid),
      '#attributes' => array('class' => array('opigno-quiz-app-sort-course-quizzes-weight')),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save order"),
  );

  return $form;
}

/**
 * Submit callback for opigno_quiz_app_sort_course_quizzes_form().
 */
function opigno_quiz_app_sort_course_quizzes_form_submit($form, $form_state) {
  foreach ($form_state['values']['table'] as $values) {
    opigno_quiz_app_set_course_quiz_weight($form_state['values']['gid'], $values['nid'], $values['weight']);
  }
}

/**
 * Helper form for filtering student lists by student membership state.
 */
function opigno_quiz_app_filter_by_status_form($form, $form_state) {
  $form['state'] = array(
    '#type' => 'select',
    '#title' => t("User state"),
    '#options' => array(
      OG_STATE_ACTIVE => t("Active"),
      OG_STATE_PENDING => t("Pending"),
      OG_STATE_BLOCKED => t("Blocked"),
    ),
    '#default_value' => isset($_SESSION['opigno_quiz_app']['state_filter'][request_path()]) ? $_SESSION['opigno_quiz_app']['state_filter'][request_path()] : OG_STATE_ACTIVE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Filter"),
  );

  return $form;
}

/**
 * Submit callback for opigno_quiz_app_filter_by_status_form().
 */
function opigno_quiz_app_filter_by_status_form_submit($form, $form_state) {
  $_SESSION['opigno_quiz_app']['state_filter'][request_path()] = $form_state['values']['state'];
}
