<?php

/**
 * @file
 * Defines the theme settings logic.
 */

/**
 * Implements hook_form_FORM_ID_alter() for system_theme_settings().
 */
function platon_form_system_theme_settings_alter(&$form, $form_state) {
  $path = drupal_get_path('theme', 'platon');

  // If using a different Admin theme, we get a Fatal Error. Include the
  // template.php file.
  require_once DRUPAL_ROOT . "/$path/template.php";

  $form['#attached'] = array(
    'js' => array(
      '//cdnjs.cloudflare.com/ajax/libs/ace/1.1.01/ace.js' => array('type' => 'file', 'cache' => FALSE),
      "$path/js/platon.theme-settings.js" => array('type' => 'file', 'cache' => FALSE),
    ),
  );

  // Deactivate irrelevant settings.
  foreach (array('toggle_name', 'toggle_slogan', 'toggle_favicon', 'toggle_main_menu', 'toggle_secondary_menu') as $option) {
    $form['theme_settings'][$option]['#access'] = FALSE;
  }

  if (module_exists('color')) {
    // Add some descriptions to clarify what each color is used for.
    foreach (array(
       'white' => t("e.g. main menu active menu link background"),
       'very_light_gray' => t("e.g. body background color"),
       'light_gray' => t('e.g content background color'),
       'medium_gray' => t('e.g. title background color, table background color'),
       'dark_gray' => t('e.g. forum tools background'),
       'light_blue' => t('e.g. link hover color, tabs background, fieldset titles'),
       'dark_blue' => t('e.g. link color, tabs active/hover background color'),
       'deep_blue' => t('e.g. header background color, footer background color'),
       'leaf_green' => t('e.g. form submit buttons, local actions'),
       'blood_red' => t('e.g. form delete buttons'),
    ) as $color => $description) {
      $form['color']['palette'][$color]['#description'] = $description;
    }

    // Hide the base and link ones. They're just there to prevent Notices.
    $form['color']['palette']['base']['#type'] = 'hidden';
    $form['color']['palette']['link']['#type'] = 'hidden';

    // Make color section collapsible.
    $form['color']['#collapsible'] = TRUE;
    $form['color']['#collapsed'] = TRUE;

    if (isset($form['#submit']) && !in_array('platon_form_system_theme_settings_alter_color_submit', $form['#submit'])) {
      $form['#submit'][] = 'platon_form_system_theme_settings_alter_color_submit';
    }
  }

  // Header image settings.
  $form['platon_header_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t("Header background"),
  );

  $form['platon_header_settings']['platon_use_header_background'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use another image for the header background"),
    '#description' => t("Check here if you want the theme to use a custom image for the header background."),
    '#default_value' => theme_get_setting('platon_use_header_background'),
  );

  $form['platon_header_settings']['platon_header_image_path'] = array(
    '#type' => 'textfield',
    '#title' => t("The path to the header background image."),
    '#description' => t("The path to the image file you would like to use as your custom header background (relative to sites/default/files). The suggested size for the header background is 3000x134."),
    '#default_value' => theme_get_setting('platon_header_image_path'),
    '#states' => array(
      'invisible' => array(
        'input[name="platon_use_header_background"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['platon_header_settings']['platon_header_image_upload'] = array(
    '#type' => 'file',
    '#title' => t("Upload an image"),
    '#description' => t("If you don't have direct file access to the server, use this field to upload your header background image."),
    '#states' => array(
      'invisible' => array(
        'input[name="platon_use_header_background"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Home page settings.
  $form['platon_home_page_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t("Homepage settings"),
  );

  $form['platon_home_page_settings']['platon_use_home_page_markup'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use a different homepage for anonymous users."),
    '#description' => t("Check here if you want the theme to use a custom page for users that are not logged in."),
    '#default_value' => theme_get_setting('platon_use_home_page_markup'),
  );

  $settings = theme_get_setting('platon_home_page_markup');
  $form['platon_home_page_settings']['platon_home_page_markup_wrapper'] = array(
    '#type' => 'fieldset',
    '#states' => array(
      'invisible' => array(
        'input[name="platon_use_home_page_markup"]' => array('checked' => FALSE),
      ),
    ),
    'platon_home_page_markup' => array(
      '#type' => 'text_format',
      '#base_type' => 'textarea',
      '#title' => t("Home page content"),
      '#description' => t("Set the content for the home page. This will be used for users that are not logged in."),
      '#format' => !empty($settings['format']) ? $settings['format'] : filter_default_format(),
      '#default_value' => !empty($settings['value']) ? $settings['value'] : '',
    ),
  );

  $form['platon_home_page_settings']['platon_use_home_page_background'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use an image for the home page background"),
    '#description' => t("Check here if you want the theme to use a custom image for the homepage background."),
    '#default_value' => theme_get_setting('platon_use_home_page_background'),
  );

  $form['platon_home_page_settings']['platon_home_page_image_path'] = array(
    '#type' => 'textfield',
    '#title' => t("The path to the home page background image."),
    '#description' => t("The path to the image file you would like to use as your custom home page background (relative to sites/default/files)."),
    '#default_value' => theme_get_setting('platon_home_page_image_path'),
    '#states' => array(
      'invisible' => array(
       'input[name="platon_use_home_page_background"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['platon_home_page_settings']['platon_home_page_image_upload'] = array(
    '#type' => 'file',
    '#title' => t("Upload an image"),
    '#description' => t("If you don't have direct file access to the server, use this field to upload your background image."),
    '#states' => array(
      'invisible' => array(
       'input[name="platon_use_home_page_background"]' => array('checked' => FALSE),
      ),
    ),
  );


  // Main menu settings.
  if (module_exists('menu')) {
    $form['platon_menu_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t("Menu settings"),
    );

    $form['platon_menu_settings']['platon_menu_source'] = array(
      '#type' => 'select',
      '#title' => t("Main menu source"),
      '#options' => array(0 => t("None")) + menu_get_menus(),
      '#description' => t("The menu source to use for the tile navigation. If 'none', Platon will use a default list of tiles."),
      '#default_value' => theme_get_setting('platon_menu_source'),
    );

    $form['platon_menu_settings']['platon_menu_show_for_anonymous'] = array(
      '#type' => 'checkbox',
      '#title' => t("Show menu for anonymous users"),
      '#description' => t("Show the main menu for users that are not logged in. Only links that users have access to will show up."),
      '#default_value' => theme_get_setting('platon_menu_show_for_anonymous'),
    );
  }

  // CSS overrides.
  $form['platon_css_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t("CSS overrides"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $css_content = _platon_get_css_override_file_content();
  $form['platon_css_settings']['platon_css_override_content'] = array(
    '#type' => 'textarea',
    '#title' => t("CSS overrides"),
    '#description' => t("You can write CSS rules here. They will be stored in a CSS file in your public files directory. Change it's content to alter the display of your site."),
    '#default_value' => $css_content,
  );

  $form['platon_css_settings']['platon_css_override_fid'] = array(
    '#type' => 'value',
    '#value' => _platon_get_css_override_file(),
  );

  if (isset($form['#validate']) && !in_array('platon_form_system_theme_settings_alter_validate', $form['#validate'])) {
    $form['#validate'][] = 'platon_form_system_theme_settings_alter_validate';
  }
  
  if (isset($form['#submit']) && !in_array('platon_form_system_theme_settings_alter_submit', $form['#submit'])) {
    array_unshift($form['#submit'], 'platon_form_system_theme_settings_alter_submit');
  }

  $form['platon_group_style'] = array(
    '#type' => 'checkbox',
    '#title' => t("Platon group style"),
    '#description' => t("Check here if you want the new group style, left block with lessons"),
    '#default_value' => variable_get('platon_group_style',1),
  );
}

/**
 * Validation callback for platon_form_system_theme_settings_alter().
 */
function platon_form_system_theme_settings_alter_validate($form, &$form_state) {
  if (!empty($_FILES['files']['name']['platon_header_image_upload'])) {
    $file = file_save_upload('platon_header_image_upload', array(
      'file_validate_is_image' => array(),
      'file_validate_extensions' => array('png gif jpg jpeg'),
    ), 'public://');

    if ($file) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      $form_state['storage']['header_file'] = $file;
    }
    else {
      form_set_error('platon_header_image_upload', t("Couldn't upload file."));
    }
  }

  if (!empty($_FILES['files']['name']['platon_home_page_image_upload'])) {
    $file = file_save_upload('platon_home_page_image_upload', array(
      'file_validate_is_image' => array(),
      'file_validate_extensions' => array('png gif jpg jpeg'),
    ), 'public://');

    if ($file) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      $form_state['storage']['home_file'] = $file;
    }
    else {
      form_set_error('platon_home_page_image_upload', t("Couldn't upload file."));
    }
  }

  if (!empty($form_state['values']['platon_css_override_content'])) {
    if ($fid = _platon_store_css_override_file($form_state['values']['platon_css_override_content'])) {
      $form_state['storage']['css_fid'] = $fid;
    }
    else {
      form_set_error('platon_css_override_content', t("Could not save the CSS in a file. Perhaps the server has no write access. Check your public files folder permissions."));
    }
  }
}

/**
 * Submission callback for platon_form_system_theme_settings_alter().
 */
function platon_form_system_theme_settings_alter_submit($form, &$form_state) {
  if (isset($form_state['storage']['header_file'])) {
    $form_state['values']['platon_header_image_path'] = str_replace('public://', '', $form_state['storage']['header_file']->uri);
  }

  if (isset($form_state['storage']['home_file'])) {
    $form_state['values']['platon_home_page_image_path'] = str_replace('public://', '', $form_state['storage']['home_file']->uri);
  }

  if (!empty($form_state['values']['platon_css_override_content'])) {
    if (!empty($form_state['storage']['css_fid'])) {
      $form_state['values']['platon_css_override_fid'] = $form_state['storage']['css_fid'];
    }
  }
  else {
    // If there is a file existing already, we must get rid of it.
    if ($file = _platon_get_css_override_file()) {
      // "Store" an empty string. This will not create a file, but set the old one as a temporary one.
      _platon_store_css_override_file('');

      // Set the setting to 0 to not use any file.
      $form_state['values']['platon_css_override_fid'] = 0;
    }
  }

  variable_set('platon_group_style',$form_state['values']['platon_group_style']);
}

/**
 * Submission callback for platon_form_system_theme_settings_alter().
 *
 * Specific logic for color integration. Remove white from the images to make them
 * transparent.
 */
function platon_form_system_theme_settings_alter_color_submit($form, $form_state) {
  if ($files = variable_get('color_platon_files', FALSE)) {
    foreach ($files as $generated_file) {
      _platon_color_remove_white($generated_file);
    }
  }
}
