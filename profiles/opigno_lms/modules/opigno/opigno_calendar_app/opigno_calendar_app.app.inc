<?php

/**
 * @file
 * App configuration.
 */

/**
 * Implements hook_apps_app_info().
 */
function opigno_calendar_app_apps_app_info() {
  return array(
    'post install callback' => 'opigno_calendar_app_post_install'
  );
}

/** 
 * Post install callback when the module is installed through apps.
 */
function opigno_calendar_app_post_install() {
  $item = array(
    'link_title' => st('Calendar'),
    'link_path' => 'opigno-calendar',
    'menu_name' => 'main-menu',
    'options' => array(
      'attributes' => array(
        'class' => array('icon', 'icon-calendar'),
      ),
    ),
  );
  menu_link_save($item);
  menu_rebuild();
}
