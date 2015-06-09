<?php

/**
 * @file
 * Hook examples for documentation purposes.
 */

/**
 * Implements hook_guideme_path().
 *
 * Allows developers to register several guided paths.
 * Return an array ,
 */
function hook_guideme_path() {
  return array(
    'path 1' => array(
      'weight' => 100,
      'steps' => array(
        '<front>' => array(
          'title' => 'Title',
          'description' => 'Description here',
          'target' => '.submit',
        ),
        'node/add' => array(
          'title' => 'Title',
          'description' => 'Description here',
        ),
      ),
    ),
    'path 3' => array(
      'weight' => -10,
      'steps' => array(
        '<front>' => array(
          'title' => 'Title',
          'description' => 'Description here',
          'target' => '.submit',
        ),
      ),
    ),
  );
}