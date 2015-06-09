<?php
/**
 * @file
 * opigno_features_roles.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function opigno_features_roles_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: forum administrator.
  $roles['forum administrator'] = array(
    'name' => 'forum administrator',
    'weight' => 5,
  );

  // Exported role: student manager.
  $roles['student manager'] = array(
    'name' => 'student manager',
    'weight' => 4,
  );

  return $roles;
}
