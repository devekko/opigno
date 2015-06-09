<?php
/**
 * @file
 * opigno_features_field_groups.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function opigno_features_field_groups_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course_settings|node|course|form';
  $field_group->group_name = 'group_course_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Course settings',
    'weight' => '10',
    'children' => array(
      0 => 'group_access',
      1 => 'requires_validation',
      2 => 'anomymous_visibility',
      3 => 'catalogue_visibility',
      4 => 'opigno_course_tools',
      5 => 'opigno_course_categories',
      6 => 'course_required_quiz_ref',
      7 => 'course_required_course_ref',
      8 => 'certificate',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-course-settings field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_course_settings|node|course|form'] = $field_group;

  return $export;
}