<?php

/**
 * @file
 * Theming functions for the quiz_drag_drop question type.
 * 
 * The theme file for quiz_drag_drop.
 */

/**
 * Theme function for the quiz_drag_drop report.
 *
 * @param array $variables
 *   Array of data to be presented in the report.
 */
function theme_quiz_drag_drop_response($variables) {
  $output = '';
  if ($variables['data']['is_skipped'] == 1) {
    $output = t('Question skipped.');
  }
  else {
    if ($variables['data']['score'] > 0) {
      $output = t('Nice, all matches are correct.');
    }
    else {
      $output = t('Some of the matches are not correct.');
    }
  }
  return $output;
}

/**
 * Theme function for the quiz_drag_drop report.
 *
 * @param array $variables
 *   Array of data to be presented in the report
 */
function theme_quiz_drag_drop_answer_form($variables) {
  static $css_added;
  global $base_path;
  if (!$css_added) {
    drupal_add_css(drupal_get_path('module', 'quiz_drag_drop') . '/quiz_drag_drop.css');
    $css_added = TRUE;

    drupal_add_library('system', 'ui.draggable');
    drupal_add_library('system', 'ui.droppable');
    drupal_add_js(drupal_get_path('module', 'quiz_drag_drop') . '/quiz_drag_drop.js');
  }

  $placeholders = $images = '';

  if (isset($variables['data']['placeholder']) && !empty($variables['data']['placeholder'])) {
    foreach ($variables['data']['placeholder'] as $key => $val) {
      $placeholder_id = "placeholder_" . $val['fid'];

      $placeholders[$val['title']] = array(
        'data' => (strlen($val['title']) > 18) ?
        substr($val['title'], 0, 18) . '..' : $val['title'],
        'class' => array('droppable'), 'id' => array($placeholder_id));
    }
  }

  if (isset($variables['data']['images']) && !empty($variables['data']['images'])) {
    foreach ($variables['data']['images'] as $key => $val) {
      $image_id = "dragged_from_" . $val['fid'];
      $images[$val['uri']] = array('data' => $val['uri'], 'id' => array($image_id));
    }
  }

  $output = '<div class="questions"><div class="ques-mid">';

  $title = '';
  $placeholder_data = array(
    'items' => $placeholders,
    'title' => $title,
    'type' => 'ul',
    'attributes' => array('class' => 'matches clearfix'),
  );
  $output .= theme('item_list', $placeholder_data);

  $top_image_path = $base_path . drupal_get_path('module', 'quiz_drag_drop') . "/images/top-arrow.gif";
  $output .= '<div class="clearfix seperator">
                <img src="' . $top_image_path . '" alt="" align="absmiddle"/>'
                 . t('Drag the items into the box that matches its label.') .
               '</div>';

  $images_data = array(
    'items' => $images,
    'title' => $title,
    'type' => 'ul',
    'attributes' => array('class' => 'matches clearfix'),
  );
  $output .= theme('item_list', $images_data);
  $output .= '<div></div></div></div>';

  return $output;
}
