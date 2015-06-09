<?php

/**
 * @file
 * App configuration.
 */

/**
 * Implements hook_apps_app_info().
 */
function opigno_quiz_app_apps_app_info() {
  return array(
    'post install callback' => 'opigno_quiz_app_post_install'
  );
}

/** 
 * Post install callback when the module is installed through apps.
 */
function opigno_quiz_app_post_install() {
  $item = array(
    'link_title' => st('My achievments'),
    'link_path' => 'my-achievements',
    'menu_name' => 'main-menu',
    'options' => array(
      'attributes' => array(
        'class' => array('icon', 'icon-certificates'),
      ),
    ),
  );
  menu_link_save($item);
  menu_rebuild();
}
