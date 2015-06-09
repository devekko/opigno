<?php
/**
 * @file
 * opigno_features_og_roles.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function opigno_features_og_roles_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:class:coach'.
  $roles['node:class:coach'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'coach',
  );

  // Exported OG Role: 'node:class:manager'.
  $roles['node:class:manager'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'class',
    'name' => 'manager',
  );

  // Exported OG Role: 'node:course:coach'.
  $roles['node:course:coach'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'course',
    'name' => 'coach',
  );

  // Exported OG Role: 'node:course:forum moderator'.
  $roles['node:course:forum moderator'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'course',
    'name' => 'forum moderator',
  );

  // Exported OG Role: 'node:course:manager'.
  $roles['node:course:manager'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'course',
    'name' => 'manager',
  );

  // Exported OG Role: 'node:course:student'.
  $roles['node:course:student'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'course',
    'name' => 'student',
  );

  // Exported OG Role: 'node:course:teacher'.
  $roles['node:course:teacher'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'course',
    'name' => 'teacher',
  );

  return $roles;
}
