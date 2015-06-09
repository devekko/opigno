<?php
/**
 * @file
 * Default views definitions.
 */

/**
 * Implements hook_views_default_views().
 */
function opigno_notifications_app_views_default_views() {
  $export = array();
  $view = new view();
  $view->name = 'Notifications';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Notifications';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Notifications';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '›';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'notification' => 'notification',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Notification validity -  start date (notification_validity) */
  $handler->display->display_options['filters']['notification_validity_value']['id'] = 'notification_validity_value';
  $handler->display->display_options['filters']['notification_validity_value']['table'] = 'field_data_notification_validity';
  $handler->display->display_options['filters']['notification_validity_value']['field'] = 'notification_validity_value';
  $handler->display->display_options['filters']['notification_validity_value']['operator'] = '<=';
  $handler->display->display_options['filters']['notification_validity_value']['granularity'] = 'minute';
  $handler->display->display_options['filters']['notification_validity_value']['default_date'] = 'now';
  $handler->display->display_options['filters']['notification_validity_value']['year_range'] = '-0:+0';
  /* Filter criterion: Content: Notification validity - end date (notification_validity:value2) */
  $handler->display->display_options['filters']['notification_validity_value2']['id'] = 'notification_validity_value2';
  $handler->display->display_options['filters']['notification_validity_value2']['table'] = 'field_data_notification_validity';
  $handler->display->display_options['filters']['notification_validity_value2']['field'] = 'notification_validity_value2';
  $handler->display->display_options['filters']['notification_validity_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['notification_validity_value2']['granularity'] = 'minute';
  $handler->display->display_options['filters']['notification_validity_value2']['default_date'] = 'now';
  $handler->display->display_options['filters']['notification_validity_value2']['year_range'] = '-0:+0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['path'] = 'notifications';

  /* Display: Notifications */
  $handler = $view->new_display('block', 'Notifications', 'block_1');
  $handler->display->display_options['display_description'] = 'Notifications';
  $translatables['Notifications'] = array(
    t('Master'),
    t('Notifications'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹'),
    t('›'),
    t('last »'),
    t('Page'),
    t('more'),
  );

  $export['opigno_notifications_display_views'] = $view;
  return $export;
}
