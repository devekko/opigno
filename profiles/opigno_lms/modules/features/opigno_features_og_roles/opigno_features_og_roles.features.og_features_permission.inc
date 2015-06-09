<?php
/**
 * @file
 * opigno_features_og_roles.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function opigno_features_og_roles_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:class:access class results'
  $permissions['node:class:access class results'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:class:add user'
  $permissions['node:class:add user'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:class:administer group'
  $permissions['node:class:administer group'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:class:can be messaged'
  $permissions['node:class:can be messaged'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:class:can message anyone'
  $permissions['node:class:can message anyone'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:class:manage members'
  $permissions['node:class:manage members'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:class:notify group members'
  $permissions['node:class:notify group members'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:class:update group'
  $permissions['node:class:update group'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:access class results'
  $permissions['node:course:access class results'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:access quiz'
  $permissions['node:course:access quiz'] = array(
    'roles' => array(
      'member' => 'member',
      'student' => 'student',
      'coach' => 'coach',
      'forum moderator' => 'forum moderator',
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:add user'
  $permissions['node:course:add user'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:administer group'
  $permissions['node:course:administer group'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:approve and deny subscription'
  $permissions['node:course:approve and deny subscription'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:can be messaged'
  $permissions['node:course:can be messaged'] = array(
    'roles' => array(
      'coach' => 'coach',
      'student' => 'student',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:can message anyone'
  $permissions['node:course:can message anyone'] = array(
    'roles' => array(
      'coach' => 'coach',
      'forum moderator' => 'forum moderator',
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:cancel own vote'
  $permissions['node:course:cancel own vote'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:create calendar_event content'
  $permissions['node:course:create calendar_event content'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create forum content'
  $permissions['node:course:create forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:create long_answer content'
  $permissions['node:course:create long_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create matching content'
  $permissions['node:course:create matching content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create multichoice content'
  $permissions['node:course:create multichoice content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create notification content'
  $permissions['node:course:create notification content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create poll content'
  $permissions['node:course:create poll content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create quiz content'
  $permissions['node:course:create quiz content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create quiz_ddlines content'
  $permissions['node:course:create quiz_ddlines content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create quiz_directions content'
  $permissions['node:course:create quiz_directions content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create scale content'
  $permissions['node:course:create scale content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create short_answer content'
  $permissions['node:course:create short_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create tft_file content'
  $permissions['node:course:create tft_file content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:create truefalse content'
  $permissions['node:course:create truefalse content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete any calendar_event content'
  $permissions['node:course:delete any calendar_event content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any forum content'
  $permissions['node:course:delete any forum content'] = array(
    'roles' => array(
      'forum moderator' => 'forum moderator',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any long_answer content'
  $permissions['node:course:delete any long_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any matching content'
  $permissions['node:course:delete any matching content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any multichoice content'
  $permissions['node:course:delete any multichoice content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any notification content'
  $permissions['node:course:delete any notification content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any poll content'
  $permissions['node:course:delete any poll content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any quiz content'
  $permissions['node:course:delete any quiz content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any quiz results'
  $permissions['node:course:delete any quiz results'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete any quiz_ddlines content'
  $permissions['node:course:delete any quiz_ddlines content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any quiz_directions content'
  $permissions['node:course:delete any quiz_directions content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any scale content'
  $permissions['node:course:delete any scale content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any short_answer content'
  $permissions['node:course:delete any short_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any tft_file content'
  $permissions['node:course:delete any tft_file content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete any truefalse content'
  $permissions['node:course:delete any truefalse content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:delete own calendar_event content'
  $permissions['node:course:delete own calendar_event content'] = array(
    'roles' => array(
      'coach' => 'coach',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own forum content'
  $permissions['node:course:delete own forum content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:delete own long_answer content'
  $permissions['node:course:delete own long_answer content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own matching content'
  $permissions['node:course:delete own matching content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own multichoice content'
  $permissions['node:course:delete own multichoice content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own notification content'
  $permissions['node:course:delete own notification content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own poll content'
  $permissions['node:course:delete own poll content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own quiz content'
  $permissions['node:course:delete own quiz content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own quiz_ddlines content'
  $permissions['node:course:delete own quiz_ddlines content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own quiz_directions content'
  $permissions['node:course:delete own quiz_directions content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own scale content'
  $permissions['node:course:delete own scale content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own short_answer content'
  $permissions['node:course:delete own short_answer content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own tft_file content'
  $permissions['node:course:delete own tft_file content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete own truefalse content'
  $permissions['node:course:delete own truefalse content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:delete results for own quiz'
  $permissions['node:course:delete results for own quiz'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:import quiz questions xls'
  $permissions['node:course:import quiz questions xls'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:inspect all votes'
  $permissions['node:course:inspect all votes'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:manage members'
  $permissions['node:course:manage members'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:manage permissions'
  $permissions['node:course:manage permissions'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:manage roles'
  $permissions['node:course:manage roles'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:moderate'
  $permissions['node:course:moderate'] = array(
    'roles' => array(
      'forum moderator' => 'forum moderator',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:notify group members'
  $permissions['node:course:notify group members'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:score any quiz'
  $permissions['node:course:score any quiz'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:score own quiz'
  $permissions['node:course:score own quiz'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:score taken quiz answer'
  $permissions['node:course:score taken quiz answer'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:skip display of results'
  $permissions['node:course:skip display of results'] = array(
    'roles' => array(
      'coach' => 'coach',
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:sort quizzes'
  $permissions['node:course:sort quizzes'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:subscribe'
  $permissions['node:course:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:course:subscribe without approval'
  $permissions['node:course:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:create tft_file content'
  $permissions['node:course:tft access file tree'] = array(
    'roles' => array(
      'manager' => 'member',
    ),
  );

  // Exported og permission: 'node:course:tft add a file to any term'
  $permissions['node:course:tft add a file to any term'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:tft add child terms'
  $permissions['node:course:tft add child terms'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:tft archive child terms'
  $permissions['node:course:tft archive child terms'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:tft delete child terms'
  $permissions['node:course:tft delete child terms'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:tft reorder terms'
  $permissions['node:course:tft reorder terms'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:unsubscribe'
  $permissions['node:course:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update any calendar_event content'
  $permissions['node:course:update any calendar_event content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any forum content'
  $permissions['node:course:update any forum content'] = array(
    'roles' => array(
      'forum moderator' => 'forum moderator',
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any long_answer content'
  $permissions['node:course:update any long_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any matching content'
  $permissions['node:course:update any matching content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any multichoice content'
  $permissions['node:course:update any multichoice content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any notification content'
  $permissions['node:course:update any notification content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any poll content'
  $permissions['node:course:update any poll content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any quiz content'
  $permissions['node:course:update any quiz content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any quiz_ddlines content'
  $permissions['node:course:update any quiz_ddlines content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any quiz_directions content'
  $permissions['node:course:update any quiz_directions content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any scale content'
  $permissions['node:course:update any scale content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any short_answer content'
  $permissions['node:course:update any short_answer content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any tft_file content'
  $permissions['node:course:update any tft_file content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update any truefalse content'
  $permissions['node:course:update any truefalse content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  // Exported og permission: 'node:course:update group'
  $permissions['node:course:update group'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own calendar_event content'
  $permissions['node:course:update own calendar_event content'] = array(
    'roles' => array(
      'coach' => 'coach',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own forum content'
  $permissions['node:course:update own forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update own long_answer content'
  $permissions['node:course:update own long_answer content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own matching content'
  $permissions['node:course:update own matching content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own multichoice content'
  $permissions['node:course:update own multichoice content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own notification content'
  $permissions['node:course:update own notification content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own poll content'
  $permissions['node:course:update own poll content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own quiz content'
  $permissions['node:course:update own quiz content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own quiz_ddlines content'
  $permissions['node:course:update own quiz_ddlines content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own quiz_directions content'
  $permissions['node:course:update own quiz_directions content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own scale content'
  $permissions['node:course:update own scale content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own short_answer content'
  $permissions['node:course:update own short_answer content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own tft_file content'
  $permissions['node:course:update own tft_file content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:update own truefalse content'
  $permissions['node:course:update own truefalse content'] = array(
    'roles' => array(
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:view any quiz results'
  $permissions['node:course:view any quiz results'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  // Exported og permission: 'node:course:view own quiz results'
  $permissions['node:course:view own quiz results'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:view results for own quiz'
  $permissions['node:course:view results for own quiz'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:vote on polls'
  $permissions['node:course:vote on polls'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'skip pre-required group when added as a member'
  $permissions['node:course:skip pre-required group when added as a member'] = array(
    'roles' => array(
      'manager' => 'manager',
      'coach' => 'coach',
      'teacher' => 'teacher',
    ),
  );

 $permissions['node:course:create cloze content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update own cloze content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update any cloze content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:delete own cloze content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:delete any cloze content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:create opigno_scorm_quiz_question content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update own opigno_scorm_quiz_question content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update any opigno_scorm_quiz_question content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:delete own opigno_scorm_quiz_question content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:delete any opigno_scorm_quiz_question content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:create quizfileupload content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update own quizfileupload content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update any quizfileupload content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:delete own quizfileupload content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:delete any quizfileupload content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:create quiz_drag_drop content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update own quiz_drag_drop content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update any quiz_drag_drop content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:delete own quiz_drag_drop content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:delete any quiz_drag_drop content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:create h5p_content content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update own h5p_content content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:update any h5p_content content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  $permissions['node:course:delete own h5p_content content'] = array(
    'roles' => array(
      'manager' => 'manager',
      'teacher' => 'teacher',
    ),
  );

  $permissions['node:course:delete any h5p_content content'] = array(
    'roles' => array(
      'manager' => 'manager',
    ),
  );

  return $permissions;
}
