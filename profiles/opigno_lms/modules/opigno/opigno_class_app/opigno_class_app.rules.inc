<?php

/**
 * @file
 * Rules integration for the class app module.
 *
 *
 *
 */

function opigno_class_app_rules_action_info() {
  $items = array();
  $items['class_map_role_to_course'] = array(
    'label' => t('Map class roles to course roles'),
    'group' => t('Class'),
    'parameter' => array(
      'class_role_id' => array(
        'type' => 'integer',
        'label' => t('Class role id'),
        'description' => t('The class role id'),
      ),
      'clgroup_id' => array(
        'type' => 'integer',
        'label' => t('Class group id'),
        'description' => t('The class group id'),
      ),
      'cogroup_id' => array(
        'type' => 'integer',
        'label' => t('Course group id'),
        'description' => t('The course group id'),
      ),
    ),
    'provides' => array(
      'course_role_id' => array(
        'type' => 'integer',
        'label' => t('Course role id'),
      ),
    ),
    'base' => 'opigno_class_app_class_to_course_role_map',
    'access callback' => 'og_rules_integration_access',
  );
  return $items;
}

function opigno_class_app_class_to_course_role_map($class_role_id, $clgroup_id, $cogroup_id) {
  $clog_roles = og_roles('node', 'class', $clgroup_id, $force_group = FALSE, $include_all = TRUE);
  foreach ($clog_roles as $index => $role) {
    switch ($role) {
      case "coach":
        $class_coach = $index;
        break;
      case "student":
        $class_student = $index;
        break;
    }
  }
  $coog_roles = og_roles('node', 'course', $cogroup_id, $force_group = FALSE, $include_all = TRUE);
  foreach ($coog_roles as $index => $role) {
    switch ($role) {
      case "coach":
        $course_coach = $index;
        break;
      case "student":
        $course_student = $index;
        break;
    }
  }

  if ($class_role_id == $class_student) {
    return array('course_role_id' => $course_student);
  }
  if ($class_role_id == $class_coach) {
    return array('course_role_id' => $course_coach);
  }
  return 0;
}
