<?php

/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 * Provides a default API for Apps and modules to use. This will simplify the
 * user experience.
 */

define('OPIGNO_LMS_COURSE_STUDENT_ROLE',   'course student member');
define('OPIGNO_LMS_COURSE_COACH_ROLE',     'course coach member');
define('OPIGNO_LMS_COURSE_TEACHER_ROLE',   'course teacher member');
define('OPIGNO_LMS_COURSE_ADMIN_ROLE',     'course admin member');
define('OPIGNO_LMS_COURSE_MODERATOR_ROLE', 'course forum moderator');

// Platform roles.
define('OPIGNO_LMS_STUDENT_MANAGER_ROLE',     'student manager');
define('OPIGNO_LMS_ADMIN_ROLE',               'administrator');
define('OPIGNO_LMS_FORUM_ADMINISTRATOR_ROLE', 'forum administrator');

define('OPIGNO_LMS_VERSION', '1.18.0');

/**
 * Implements hook_init().cd .drush
 */
function opigno_lms_init() {
  // We need to store the default roles so other modules can use them easily.
  // Using this in hook_install() does not work, as the feature is not completely
  // done installing at that point (or so it seems - it doesn't make any sense).
  // Check the roles are found and set. If not, get them now.
  // Make sure we find at least one of them. If not, don't store anything and wait
  // for the next page load.
  $og_roles = variable_get('opigno_lms_default_og_roles', array());
  if (empty($og_roles)) {
    module_load_include('install', 'opigno_lms');

    // Get the role IDs to set them as variables.
    // If not a single role is found, then we still haven't finished installing the roles.
    // In that case, don't store the variable so we re-run this logic on the next page load.
    $found = FALSE;
    foreach (array(
      OPIGNO_LMS_COURSE_ADMIN_ROLE     => 'manager',
      OPIGNO_LMS_COURSE_COACH_ROLE     => 'coach',
      OPIGNO_LMS_COURSE_TEACHER_ROLE   => 'teacher',
      OPIGNO_LMS_COURSE_STUDENT_ROLE   => 'student',
      OPIGNO_LMS_COURSE_MODERATOR_ROLE => 'forum moderator',
    ) as $role_key => $role_name) {
      $rid = _opigno_lms_install_get_role_by_name($role_name, OPIGNO_COURSE_BUNDLE);
      if (!empty($rid)) {
        $og_roles[$role_key] = $rid;
        $found = TRUE;
      }
    }
    if ($found) {
      variable_set('opigno_lms_default_og_roles', $og_roles);
      variable_set('og_group_manager_default_rids_node_course', array($og_roles[OPIGNO_LMS_COURSE_ADMIN_ROLE]));

      $rid = _opigno_lms_install_get_role_by_name('manager', 'class');
      if (!empty($rid)) {
        variable_set('og_group_manager_default_rids_node_class', array($rid));
      }
    }
  }

  $platform_roles = variable_get('opigno_lms_default_platform_roles', array());
  if (empty($platform_roles)) {
    module_load_include('install', 'opigno_lms');

    // Get the role IDs to set them as variables.
    // If not a single role is found, then we still haven't finished installing the roles.
    // In that case, don't store the variable so we re-run this logic on the next page load.
    $found = FALSE;
    foreach (array(
      OPIGNO_LMS_STUDENT_MANAGER_ROLE => 'student manager',
      OPIGNO_LMS_ADMIN_ROLE => 'administrator',
      OPIGNO_LMS_FORUM_ADMINISTRATOR_ROLE => 'forum administrator',
    ) as $role_key => $role_name) {
      $role = user_role_load_by_name($role_name);
      if (!empty($role->rid)) {
        $platform_roles[$role_key] = $role->rid;
        $found = TRUE;
      }
    }
    if ($found) {
      variable_set('opigno_lms_default_platform_roles', $platform_roles);
    }
  }
}

/**
 * Implements hook_form_node_form_alter().
 *
 * If Drupal locale module is enabled, it forces all nodes - and its fields - to have the default
 * language (usually 'en'). This is stupid beyond words, and breaks many modules that try to theme
 * their own fields, but only expect to find the 'und' (LANGUAGE_NONE) key.
 *
 * If the site has only one language, and entity translation is not enabled, force the node to
 * be LANGUAGE_NONE, as one would expect.
 */
function opigno_lms_form_node_form_alter(&$form, $form_state) {
  if (!(module_exists('entity_translation') || module_exists('translation'))) {
    $form['language']['#value'] = LANGUAGE_NONE;
  }
}

/**
 * Implements hook_install_tasks()
 */
function opigno_lms_install_tasks(&$install_state) {
  // Add our custom CSS file for the installation process
  drupal_add_css(drupal_get_path('profile', 'opigno_lms') . '/css/opigno_lms.css');
  $tasks=array();
  $tasks['opigno_lms_install_task_post_install']=array();
  $tasks['opigno_lms_verify_requirements']=array(
    'display_name' => st('Check Opigno requirements'),
    'type' => 'form',
  );
  if (!empty($install_state['parameters']['opigno_requirements_finished']))
  {
    $tasks['opigno_lms_verify_requirements']['run']=INSTALL_TASK_SKIP;
  }
  return $tasks;
}

/**
 * Implements hook_install_tasks_alter()
 * Hides messages for non english installs
 */
function opigno_lms_install_tasks_alter(&$tasks, $install_state)
{
  if (isset($tasks['opigno_lms_verify_requirements'])) {
    $pos = array_search('opigno_lms_verify_requirements', array_keys($tasks));
    if ($pos == '11') {
      $save = $tasks['opigno_lms_verify_requirements'];
      unset($tasks['opigno_lms_verify_requirements']);
      $first_array = array_splice($tasks, 0, 4);
      $tasks = array_merge($first_array, array('opigno_lms_verify_requirements' => $save), $tasks);
    }
  }
  if ($install_state['active_task']=="install_import_locales")
  {
    drupal_get_messages('status');
    drupal_get_messages('warning');
  }
}

/**
 * Verifies Opigno requirements
 */
function opigno_lms_verify_requirements($form, &$form_state, &$install_state) {
  $form = array();
  $error = FALSE;
  $warnings = FALSE;
  $t = get_t();
  $available_memory = ini_get("memory_limit");
  if ($available_memory == -1) {
    $available_memory = 2048;
  }

  $available_memory = preg_replace('/\D/', '', $available_memory);
  if ($available_memory < 256) {
    drupal_set_message($t("The minimum memory requirement for Opigno installation is 256M, you only have %available_memory. Please change the memory_limit in your php.ini settings file or using ini_set in the settings.php file before continuing", array('%available_memory' => $available_memory)), 'error', $repeat = FALSE);
    $error = TRUE;
  }

  $xdebug_max_nesting_level = ini_get("xdebug.max_nesting_level");
  if ((!empty($xdebug_max_nesting_level)) && ($xdebug_max_nesting_level < 200) && ($xdebug_max_nesting_level != -1)) {
    drupal_set_message($t("Your system has Zend Xdebug enabled. In order to install Opigno with Xdebug enabled please set xdebug.max_nesting_level to at least 200 in your php.ini settings file or using ini_set in the settings.php file before continuing. Currently it is set as %xdebug_max_nesting_level.", array('%xdebug_max_nesting_level' => $xdebug_max_nesting_level)), "error", $repeat = FALSE);
    $error = TRUE;
  }

  $max_execution_time = ini_get("max_execution_time");
  if (($max_execution_time < 30) && ($max_execution_time != -1)) {
    drupal_set_message($t("Your system has the maximum_execution_time as %max_execution_time. Minimum required for Opigno installation is 30. If your machine is old and depending on its current load you may want to raise it even higher (120). Please change the maximum_execution_time in your php.ini settings file or using ini_set in the settings.php file before continuing.", array('%max_execution_time' => $max_execution_time)), "error", $repeat = FALSE);
    $error = TRUE;
  }

  if (($max_execution_time < 120) && ($max_execution_time != -1)) {
    $warnings[] = $t("Your system has the maximum_execution_time as %max_execution_time. Minimum required for Opigno installation is 30. But depending on your system performance and current load you may want to raise this setting above (120). You can change the maximum_execution_time in your php.ini settings file or using ini_set in the settings.php file.", array('%max_execution_time' => $max_execution_time));
  }

  $max_input_time = ini_get("max_input_time");
  if (($max_input_time < 60) && ($max_input_time != -1)) {
    drupal_set_message($t("Your system has the max_input_time as %max_input_time. Minimum required for Opigno installation is 60. If your machine is old and depending on its current load you may want to raise it even higher (120). Please change the max_input_time in your php.ini settings file or using ini_set in the settings.php file before continuing", array('%max_input_time' => $max_input_time)), "error", $repeat = FALSE);
    $error = TRUE;
  }

  if (($max_input_time < 120) && ($max_input_time != -1)) {
    $warnings[] = $t("Your system has the max_input_time as %max_input_time. Minimum required for Opigno installation is 60. But depending on your system performance and current load you may want to raise this setting above (120). You can change the max_input_time in your php.ini settings file or using ini_set in the settings.php file.", array('%max_input_time' => $max_input_time));
  }

  if ($error == FALSE) {
    drupal_set_message($t("Your system has passed Opigno requirements, you may proceed"), 'status', $repeat = FALSE);
    if ($warnings != FALSE) {
      foreach ($warnings as $warning) {
        drupal_set_message($warning, 'warning', $repeat = FALSE);
      }
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Continue'),
    );
    $form_state['build_info']['args']['install_state']=&$install_state;
  }
  return $form;
}

function opigno_lms_verify_requirements_submit($form, &$form_state)
{
  $install_state=&$form_state['build_info']['args']['install_state'];
  $install_state['parameters']['opigno_requirements_finished']=TRUE;
}

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function opigno_lms_form_install_configure_form_alter(&$form, $form_state) {
  // Hide some messages from various modules that are just too chatty.
  drupal_get_messages('status');
  drupal_get_messages('warning');

  drupal_set_message(st("Please note that Opigno ships with the !dompdf library for generating certificates in PDF format. This works fine, but we strongly recommend to use !wkhtml instead, if you can. !wkhtml is much more powerful, and will allow you to make nicer certificates. However, !wkhtml requires manual installation, and your server might not be compatible. Please refer to these <a href='!url' target='_blank'>instructions</a> for more information, or visit our support forums.", array('!dompdf' => '<a href="https://github.com/dompdf/dompdf" target="_blank">DomPDF</a>', '!wkhtml' => '<a href="https://code.google.com/p/wkhtmltopdf/" target="_blank">WKHTML</a>', '!url' => 'https://drupal.org/node/306882')), 'warning');
  drupal_set_message(st("Please note that Opigno ships with the pdf module that allows users to view pdf files inside slides. In order to use this functionality you need to manually download the pdfjs library. <a href='!url' target='_blank'>Instructions on our forum</a>", array('!url' => 'https://www.opigno.org/node/820')), 'warning');

  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = st('Opigno LMS');

  // Use "admin" as the default username.
  $form['admin_account']['account']['name']['#default_value'] = 'admin';

  // Hide Update Notifications.
  $form['update_notifications']['#access'] = FALSE;
  $form['update_notifications']['#default_value'] = TRUE;

  // Define a default email address if we can guess a valid one
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }

  // Opigno LMS options
  /* @todo
  $form['opigno_lms'] = array(
    '#type' => 'fieldset',
    '#title' => st("LMS settings"),
    '#tree' => TRUE,
  );
  $form['opigno_lms']['demo_content'] = array(
    '#type' => 'checkbox',
    '#title' => st("Enable demo content"),
    '#description' => st("You can enable demo content on your platform to get you started. This will create several user accounts, courses, certificates and quizzes to get you started."),
    '#default_value' => 0,
  );
  */
  $form['#submit'][] = 'opigno_lms_form_install_configure_form_alter_submit';
}

/**
 * Submit callback for opigno_lms_form_install_configure_form_alter().
 */
function opigno_lms_form_install_configure_form_alter_submit($form, $form_state) {
  if (!empty($form_state['values']['opigno_lms']['demo_content'])) {
    // @todo
  }
  if (module_exists('locale')) {
  opigno_lms_refresh_strings_and_import(array('field','rules'));
  }
  // Installs H5P Libraries
  $path = file_get_contents(drupal_get_path("profile","opigno_lms")."/h5plib/libraries.h5p");
  $temporary_file_path = 'public://' . variable_get('h5p_default_path', 'h5p') . '/temp/' . uniqid('h5p-');
  $prepare=file_prepare_directory($temporary_file_path, FILE_CREATE_DIRECTORY);
  $temporary_file_name=$temporary_file_path."/libraries.h5p";
  $file=file_save_data($path,$temporary_file_name,FILE_EXISTS_REPLACE);
  $_SESSION['h5p_upload'] = drupal_realpath($file->uri);
  $_SESSION['h5p_upload_folder'] = drupal_realpath($temporary_file_path);
  $validator = _h5p_get_instance('validator');
  $isvalid=$validator->isValidPackage(TRUE, FALSE);
  $h5p_core = _h5p_get_instance('storage');
  $save_package=$h5p_core->savePackage(NULL, NULL, TRUE);
  unset($_SESSION['h5p_upload'], $_SESSION['h5p_upload_folder']);
  /////////////////////////////////////////////////////////////////////
}

/**
 * Implements hook_update_status_alter().
 *
 * Disable reporting of projects that are in the distribution, but only
 * if they have not been updated manually.
 */
function opigno_lms_update_status_alter(&$projects) {
  $bad_statuses = array(
    UPDATE_NOT_SECURE,
    UPDATE_REVOKED,
    UPDATE_NOT_SUPPORTED,
  );

  $make_filepath = drupal_get_path('profile', 'opigno_lms') . '/drupal-org.make';
  if (!file_exists($make_filepath)) {
    return;
  }

  $make_info = drupal_parse_info_file($make_filepath);
  foreach ($projects as $project_name => $project_info) {
    // Never unset the drupal project to avoid hitting an error with
    // _update_requirement_check(). See http://drupal.org/node/1875386.
    /*if ($project_name == 'drupal' || !isset($project_info['releases']) || !isset($project_info['recommended'])) {
      continue;
    }*/
    // Never unset the opigno_lms project. We want them to update.
    if ($project_name == 'opigno_lms') {
      continue;
    }
    // Hide Opigno LMS projects, they have no update status of their own.
    if (strpos($project_name, 'opigno_features_') !== FALSE) {
      unset($projects[$project_name]);
    }
    // Hide bad releases (insecure, revoked, unsupported).
    elseif (isset($project_info['status']) && in_array($project_info['status'], $bad_statuses)) {
      unset($projects[$project_name]);
    }
    // Hide projects shipped with Opigno LMS if they haven't been manually
    // updated.
    elseif (isset($make_info['projects'][$project_name]['version'])) {
      $version = $make_info['projects'][$project_name]['version'];
      if (strpos($version, 'dev') !== FALSE || (DRUPAL_CORE_COMPATIBILITY . '-' . $version == $project_info['info']['version'])) {
        unset($projects[$project_name]);
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Disable the update for Opigno LMS.
 */
function opigno_lms_form_update_manager_update_form_alter(&$form, &$form_state, $form_id) {
  if (isset($form['projects']['#options']) && isset($form['projects']['#options']['opigno_lms'])) {
    if (count($form['projects']['#options']) > 1) {
      unset($form['projects']['#options']['opigno_lms']);
    }
    else {
      unset($form['projects']);
      // Hide Download button if there's no other (disabled) projects to update.
      if (!isset($form['disabled_projects'])) {
        $form['actions']['#access'] = FALSE;
      }
      $form['message']['#markup'] = t('All of your projects are up to date.');
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for og_ui_add_users().
 */
function opigno_lms_form_og_ui_add_users_alter(&$form, $form_state) {
  $gid = $form['gid']['#value'];
  $node = node_load($gid);
  _opigno_lms_hide_coach_checkbox($node);
}

/**
 * Implements hook_form_FORM_ID_alter() for og_ui_edit_membership().
 */
function opigno_lms_form_og_ui_edit_membership_alter(&$form, $form_state) {
  $gid = $form['gid']['#value'];
  $node = node_load($gid);
  _opigno_lms_hide_coach_checkbox($node);
}

/**
 * Implements hook_form_FORM_ID_alter() for og_massadd_massadd_form().
 */
function opigno_lms_form_og_massadd_massadd_form_alter(&$form, $form_state) {
  $gid = current($form['group_ids']['#value']);
  $node = node_load($gid);
  _opigno_lms_hide_coach_checkbox($node);
}

/**
 * Implements hook_block_info().
 */
function opigno_lms_block_info() {
  return array(
    'version' => array(
      'info' => t("Opigno version information"),
      'cache' => DRUPAL_CACHE_GLOBAL,
    )
  );
}

/**
 * Implements hook_block_view().
 */
function opigno_lms_block_view($delta = '') {
  return array(
    'subject' => '<none>',
    'content' => t("Opigno LMS !version", array('!version' => OPIGNO_LMS_VERSION)),
  );
}

/**
 * Hides the coach role checkbox by adding some inline CSS. This is only to simplify the administration interface.
 *
 * @param  object $node
 */
function _opigno_lms_hide_coach_checkbox($node) {
  if (module_exists('opigno_simple_ui') && !empty($node->nid) && $node->type === OPIGNO_COURSE_BUNDLE) {
    $rid = opigno_lms_get_role_id(OPIGNO_LMS_COURSE_COACH_ROLE);
    if (!empty($rid)) {
      drupal_add_css(".form-type-checkbox.form-item-roles-$rid { display: none; }", array('type' => 'inline'));
    }
  }
}

/**
 * Install task: call modules that implement the opigno_lms_post_install hook to do some final tasks when installing the platform.
 */
function opigno_lms_install_task_post_install() {
  module_invoke_all('opigno_lms_post_install');
}

/**
 * @defgroup opigno_lms_api Opigno LMS API
 * @{
 * Opigno LMS provides an API that modules can use when inside the Opigno distribution context. These functions are meant
 * to simplify the life of end users by allowing modules to set sensible defaults when installed. This is especially useful
 * for apps and permissions. Many less-technical users will expect apps/modules to work out of the box. They will not expect
 * to have to dig through long permission lists to check boxes for specific roles.
 *
 * When a new app/module is coded, developers should think about the different permissions and to which kind of users they
 * would -- in most cases -- apply. Opigno ships with default OG roles, which are available as constants. Modules that provide
 * other group bundles are encouraged to expose similar constants so that the same API can be used for similar purposes.
 *
 * The available role constants Opigno LMS provides apply to the course bundle:
 *  - OPIGNO_LMS_COURSE_STUDENT_ROLE
 *  - OPIGNO_LMS_COURSE_TEACHER_ROLE
 *  - OPIGNO_LMS_COURSE_COACH_ROLE
 *  - OPIGNO_LMS_COURSE_ADMIN_ROLE
 *
 * The available role constants Opigno LMS provides for the platform:
 *  - OPIGNO_LMS_ADMIN_ROLE
 *  - OPIGNO_LMS_STUDENT_MANAGER_ROLE
 *  - OPIGNO_LMS_FORUM_ADMINISTRATOR_ROLE
 */

/**
 * Get the default OG role ids.
 *
 * @deprecated Use the opigno_lms_get_og_role_id() function instead.
 *
 * @param  string $key
 *
 * @return int
 */
function opigno_lms_get_role_id($key) {
  return opigno_lms_get_og_role_id($key);
}

/**
 * Get the default OG role ids.
 *
 * @param  string $key
 *
 * @return int
 */
function opigno_lms_get_og_role_id($key) {
  $roles = &drupal_static(__FUNCTION__);

  if (empty($roles)) {
    $roles = variable_get('opigno_lms_default_og_roles', array());
  }

  return !empty($roles[$key]) ? $roles[$key] : 0;
}

/**
 * Get the default platform role ids.
 *
 * @param  string $key
 *
 * @return int
 */
function opigno_lms_get_platform_role_id($key) {
  $roles = &drupal_static(__FUNCTION__);

  if (empty($roles)) {
    $roles = variable_get('opigno_lms_default_platform_roles', array());
  }

  return !empty($roles[$key]) ? $roles[$key] : 0;
}

/**
 * Set OG permissions for a specific bundle and specific roles.
 * This function is globally available and modules and apps should use it to set default permissions, simplifying module
 * installation and site management.
 *
 * @param  string $bundle
 * @param  array $permissions
 *               An array of permissions, keyed by group role ID. Modules that define group types are encouraged to
 *               expose constants for their default group roles so other modules can use this function for the same purpose.
 */
function opigno_lms_set_og_permissions($bundle, $permissions) {
  foreach ($permissions as $role_key => $role_permissions) {
    $rid = opigno_lms_get_og_role_id($role_key);
    og_role_grant_permissions($rid, $role_permissions);
  }
}

/**
 * Set platform permissions for specific roles.
 * This function is globally available and modules and apps should use it to set default permissions, simplifying module
 * installation and site management.
 *
 * @param  array $permissions
 *               An array of permissions, keyed by role ID.
 */
function opigno_lms_set_platform_permissions($permissions) {
  foreach ($permissions as $role_key => $role_permissions) {
    $rid = opigno_lms_get_platform_role_id($role_key);
    user_role_grant_permissions($rid, $role_permissions);
  }
}

/**
 * Refreshes the translation strings and imports the translations
 * that ship with Opigno. This is necessary, especially for fields
 * and rules, as Drupal does not refresh translation groups.
 *
 * @param array $groups
 *        The groups we want to refresh.
 */
function opigno_lms_refresh_strings_and_import($groups) {
  $languages = language_list();
  foreach ($languages as $index => $language) {
    if (in_array($index, array('fr', 'de'))) {
      module_load_include('inc', 'i18n_string', 'i18n_string.admin');
      opigno_lms_i18n_string_refresh_batch($groups, $index);
    }
  }
}

/**
 * Batch definition for refreshing string groups.
 *
 * @param array $groups
 *        The groups we want to refresh.
 */
function opigno_lms_i18n_string_refresh_batch($groups, $lang) {
  module_load_include('inc', 'i18n_string', 'i18n_string.admin');
  $operations = array();
  foreach ($groups as $group) {
    $context = NULL;
    _i18n_string_batch_refresh_prepare($group, $context);
    // First try to find string list
    _i18n_string_batch_refresh_list($group, $context);
    // Then invoke refresh callback
    _i18n_string_batch_refresh_callback($group, $context);
    // Output group summary
    _i18n_string_batch_refresh_summary($group, $context);
    $path = file_unmanaged_copy('profiles/opigno_lms/group_translations/' . $lang . '-' . $group . '.po', NULL, FILE_EXISTS_REPLACE);
    $files = file_load_multiple(array(), array('uri' => $path));
    $file = reset($files);
    if (empty($file)) {
      $file = new stdClass();
      $file->status = 0;
      $file->uri = $path;
      $file->filename = $lang . ".po";
      $file = file_save($file);
    }
    _locale_import_po($file, $lang, 1, $group);
  }
}


/**
 * @} End of "defgroup opigno_lms_api".
 */
