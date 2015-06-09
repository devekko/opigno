<?php

/**
 * @file
 * App configuration.
 */

/**
 * Implements hook_apps_app_info().
 */
function opigno_messaging_app_apps_app_info() {
  return array(
    'post install callback' => 'opigno_messaging_app_post_install'
  );
}

/** 
 * Post install callback when the module is installed through apps.
 */
function opigno_messaging_app_post_install() {
  $item = array(
    'link_title' => st('Messages'),
    'link_path' => 'messages',
    'menu_name' => 'main-menu',
    'options' => array(
      'attributes' => array(
        'class' => array('icon', 'icon-messages'),
      ),
    ),
  );
  menu_link_save($item);
  menu_rebuild();
}
