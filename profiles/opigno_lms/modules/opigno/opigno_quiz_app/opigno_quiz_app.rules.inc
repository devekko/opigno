<?php

/**
 * @file
 * Rules hook definitions.
 * Many of these should be moved back to the Quiz Rules module once it's ported.
 */

/**
 * Implements hook_rules_event_info().
 */
function opigno_quiz_app_rules_event_info() {
  return array(
    'opigno_quiz_app_rules_quiz_passed' => array(
      'label' => t('User has passed a quiz'),
      'group' => 'Quiz',
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'admin' => array('type' => 'user', 'label' => t('Quiz Administrator')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
    'opigno_quiz_app_rules_quiz_failed' => array(
      'label' => t('User has failed a quiz'),
      'group' => 'Quiz',
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'admin' => array('type' => 'user', 'label' => t('Quiz Administrator')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
    'opigno_quiz_app_rules_quiz_taken' => array(
      'label' => t('User has taken a quiz'),
      'group' => 'Quiz',
      'variables' => array(
        'user' => array('type' => 'user', 'label' => t('Quiz Taker')),
        'admin' => array('type' => 'user', 'label' => t('Quiz Administrator')),
        'node' => array('type' => 'node', 'label' => t('Quiz')),
      ),
    ),
  );
}

/**
 * Implements hook_rules_condition_info().
 */
function opigno_quiz_app_rules_condition_info() {
  return array(
    'opigno_quiz_app_rules_quiz_property_is' => array(
      'group' => 'Quiz',
      'label' => t('Quiz property is'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'property' => array(
          'type' => 'text',
          'label' => t('Quiz property'),
        ),
        'value' => array(
          'type' => 'text',
          'label' => t('Value'),
        ),
      ),
    ),
    'opigno_quiz_app_rules_has_answered_quiz' => array(
      'group' => 'Quiz',
      'label' => t('User has answered quiz'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
    ),
    'opigno_quiz_app_rules_has_passed_quiz' => array(
      'group' => 'Quiz',
      'label' => t('User has passed quiz'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
    ),
    'opigno_quiz_app_rules_has_failed_quiz' => array(
      'group' => 'Quiz',
      'label' => t('User has failed quiz'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
        ),
      ),
    ),
  );
}

/**
 * Condition: Data comparison for a quiz property.
 */
function opigno_quiz_app_rules_quiz_property_is($node, $property, $value, $settings) {
  $property_value = db_select('quiz_node_properties', 'q')
    ->fields('q', array($property))
    ->condition('q.nid', $node->nid)
    ->execute()
    ->fetchField();

  return $property_value == $value;
}

/**
 * Condition: User has answered quiz.
 */
function opigno_quiz_app_rules_has_answered_quiz($node, $user) {
  $score = @current(quiz_get_score_data(array($node->nid), $user->uid));
  return (isset($score->percent_score));
}

/**
 * Condition: User has passed quiz.
 */
function opigno_quiz_app_rules_has_passed_quiz($node, $user) {
  switch ($node->type) {
    case "quiz":
      $score = @current(quiz_get_score_data(array($node->nid), $user->uid));
      return (isset($score->percent_score)) && $score->percent_score >= $score->percent_pass;
    case "in_house_training":
      $value = opigno_in_house_training_score_form_get_default_value($node->nid,$user->uid);
      if ($value['status'] != 1) {
        return false;
      }
      return true;
    case "webex_video_conference":
      $value = opigno_webex_attendance_form_get_default_value($node->nid,$user->uid);
      if ($value['status'] != 1) {
        return false;
      }
      return true;
  }
}

/**
 * Condition: User has failed quiz.
 */
function opigno_quiz_app_rules_has_failed_quiz($node, $user) {
  $score = @current(quiz_get_score_data(array($node->nid), $user->uid));
  return (isset($score->percent_score)) && $score->percent_score < $score->percent_pass;
}

/**
 * Implements hook_rules_action_info().
 */
function opigno_quiz_app_rules_action_info() {
  return array(
    'opigno_quiz_app_rules_quiz_get_property' => array(
      'group' => 'Quiz',
      'label' => t('Quiz get property'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'property' => array(
          'type' => 'text',
          'label' => t('Quiz property'),
        ),
      ),
      'provides' => array(
        'quiz_property' => array(
          'type' => 'unknown',
          'label' => t('Quiz property'),
        ),
      ),
    ),
    'opigno_quiz_app_rules_quiz_get_highest_score' => array(
      'group' => 'Quiz',
      'label' => t('Quiz get best score'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Quiz node'),
        ),
        'property' => array(
          'type' => 'user',
          'label' => t('Quiz taker'),
        ),
      ),
      'provides' => array(
        'quiz_score' => array(
          'type' => 'decimal',
          'label' => t('Quiz score'),
        ),
      ),
    ),
  );
}

/**
 * Action: Get a property from a quiz.
 */
function opigno_quiz_app_rules_quiz_get_property($node, $property, $settings) {
  $value = db_select('quiz_node_properties', 'q')
    ->fields('q', array($property))
    ->condition('q.nid', $node->nid)
    ->execute()
    ->fetchField();

  return array('quiz_property' => $value);
}

/**
 * Action: Get the best score for the quiz and user.
 */
function opigno_quiz_app_rules_quiz_get_highest_score($node, $user, $settings) {
  $score = current(quiz_get_score_data(array($node->nid), $user->uid));
  return array('quiz_score' => !empty($score) ? $score : 0);
}
