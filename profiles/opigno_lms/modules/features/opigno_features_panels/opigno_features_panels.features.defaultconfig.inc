<?php
/**
 * @file
 * opigno_features_panels.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function opigno_features_panels_defaultconfig_features() {
  return array(
    'opigno_features_panels' => array(
      'field_default_fields' => 'field_default_fields',
      'panelizer_defaults' => 'panelizer_defaults',
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function opigno_features_panels_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-basic_file-field_basic_file_file'.
  $fields['fieldable_panels_pane-basic_file-field_basic_file_file'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_file_file',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'file',
      'settings' => array(
        'display_default' => 0,
        'display_field' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'file',
    ),
    'field_instance' => array(
      'bundle' => 'basic_file',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'file',
          'settings' => array(),
          'type' => 'file_default',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_file_file',
      'label' => 'File',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'file_directory' => 'general',
        'file_extensions' => 'pdf txt',
        'max_filesize' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'file',
        'settings' => array(
          'progress_indicator' => 'throbber',
        ),
        'type' => 'file_generic',
        'weight' => 2,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-basic_file-field_basic_file_text'.
  $fields['fieldable_panels_pane-basic_file-field_basic_file_text'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_file_text',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'basic_file',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_file_text',
      'label' => 'Text',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-image-field_basic_image_caption'.
  $fields['fieldable_panels_pane-image-field_basic_image_caption'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_image_caption',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_with_summary',
    ),
    'field_instance' => array(
      'bundle' => 'image',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_image_caption',
      'label' => 'Caption',
      'required' => 0,
      'settings' => array(
        'display_summary' => 0,
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 3,
          'summary_rows' => 5,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => 2,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-image-field_basic_image_image'.
  $fields['fieldable_panels_pane-image-field_basic_image_image'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_image_image',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'image',
      'settings' => array(
        'default_image' => 45,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'image',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => 'panopoly_image_full',
          ),
          'type' => 'image',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_image_image',
      'label' => 'Image',
      'required' => 0,
      'settings' => array(
        'alt_field' => 1,
        'default_image' => 0,
        'file_directory' => 'general',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-map-field_map_address'.
  $fields['fieldable_panels_pane-map-field_map_address'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_map_address',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(
        'max_length' => 255,
      ),
      'translatable' => 0,
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'map',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => 'The street address of the location you wish to map. This widget will contact Google and try to do its best to create a map!',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'simple_gmap',
          'settings' => array(
            'iframe_height' => 400,
            'iframe_width' => 600,
            'include_link' => 0,
            'include_map' => 1,
            'include_text' => 0,
            'information_bubble' => 0,
            'langcode' => 'en',
            'link_text' => 'View larger map',
            'map_type' => 'm',
            'zoom_level' => 14,
          ),
          'type' => 'simple_gmap',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_map_address',
      'label' => 'Address',
      'required' => 0,
      'settings' => array(
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => -4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-map-field_map_information'.
  $fields['fieldable_panels_pane-map-field_map_information'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_map_information',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'map',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_map_information',
      'label' => 'Information',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 3,
        ),
        'type' => 'text_textarea',
        'weight' => -3,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-quick_links-field_quick_links_links'.
  $fields['fieldable_panels_pane-quick_links-field_quick_links_links'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_quick_links_links',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'link',
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'rel' => '',
          'target' => 'default',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
      ),
      'translatable' => 0,
      'type' => 'link_field',
    ),
    'field_instance' => array(
      'bundle' => 'quick_links',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_quick_links_links',
      'label' => 'Links',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'configurable_title' => 0,
          'rel' => '',
          'target' => 'default',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_field',
        'weight' => -4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-spotlight-field_basic_spotlight_items'.
  $fields['fieldable_panels_pane-spotlight-field_basic_spotlight_items'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_spotlight_items',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'panopoly_widgets',
      'settings' => array(
        'default_image' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'panopoly_spotlight',
    ),
    'field_instance' => array(
      'bundle' => 'spotlight',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'panopoly_widgets',
          'settings' => array(
            'image_style' => 'panopoly_image_spotlight',
          ),
          'type' => 'panopoly_spotlight_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_spotlight_items',
      'label' => 'Items',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'file_directory' => 'general',
        'file_extensions' => 'jpg jpeg gif png',
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'panopoly_widgets',
        'settings' => array(),
        'type' => 'panopoly_spotlight_form',
        'weight' => -4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-table-field_basic_table_table'.
  $fields['fieldable_panels_pane-table-field_basic_table_table'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_table_table',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'tablefield',
      'settings' => array(
        'cell_processing' => 0,
        'lock_values' => 0,
      ),
      'translatable' => 0,
      'type' => 'tablefield',
    ),
    'field_instance' => array(
      'bundle' => 'table',
      'default_value' => array(
        0 => array(
          'tablefield' => array(
            'cell_0_0' => '',
            'cell_0_1' => '',
            'cell_1_0' => '',
            'cell_1_1' => '',
            'cell_2_0' => '',
            'cell_2_1' => '',
            'import' => array(
              'rebuild_field_basic_table_table_0' => 'Upload CSV',
              'tablefield_csv_field_basic_table_table_0' => '',
            ),
            'rebuild' => array(
              'count_cols' => 2,
              'count_rows' => 3,
              'rebuild' => 'Rebuild Table',
            ),
          ),
        ),
      ),
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'tablefield',
          'settings' => array(),
          'type' => 'default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_table_table',
      'label' => 'Table',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'tablefield',
        'settings' => array(),
        'type' => 'tablefield',
        'weight' => -4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-text-field_basic_text_text'.
  $fields['fieldable_panels_pane-text-field_basic_text_text'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_basic_text_text',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'text',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_basic_text_text',
      'label' => 'Text',
      'required' => 0,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => -4,
      ),
    ),
  );

  // Exported field: 'fieldable_panels_pane-video-field_video_file'.
  $fields['fieldable_panels_pane-video-field_video_file'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_video_file',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'file',
      'settings' => array(
        'display_default' => 0,
        'display_field' => 0,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'file',
    ),
    'field_instance' => array(
      'bundle' => 'video',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'file_entity',
          'settings' => array(
            'file_view_mode' => 'default',
          ),
          'type' => 'file_rendered',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_video_file',
      'label' => 'Video',
      'required' => 0,
      'settings' => array(
        'description_field' => 0,
        'file_directory' => '',
        'file_extensions' => 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp mp3 mov m4v mp4 mpeg avi ogg oga ogv wmv ico',
        'max_filesize' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'media',
        'settings' => array(
          'allowed_schemes' => array(
            'public' => 0,
            'vimeo' => 'vimeo',
            'youtube' => 'youtube',
          ),
          'allowed_types' => array(
            'audio' => 0,
            'default' => 0,
            'image' => 0,
            'video' => 'video',
          ),
          'browser_plugins' => array(
            'library' => 0,
            'media_default--media_browser_1' => 'media_default--media_browser_1',
            'media_default--media_browser_my_files' => 0,
            'media_internet' => 'media_internet',
            'upload' => 0,
          ),
          'progress_indicator' => 'throbber',
        ),
        'type' => 'media_generic',
        'weight' => -2,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Caption');
  t('File');
  t('Image');
  t('Information');
  t('Items');
  t('Links');
  t('Table');
  t('Text');
  t('The street address of the location you wish to map. This widget will contact Google and try to do its best to create a map!');
  t('Video');

  return $fields;
}

/**
 * Implements hook_defaultconfig_panelizer_defaults().
 */
function opigno_features_panels_defaultconfig_panelizer_defaults() {
  $export = array();

  return $export;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function opigno_features_panels_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_node_view_disabled';
  $strongarm->value = TRUE;
  $export['page_manager_node_view_disabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_basic_file';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_basic_file'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_fieldable_panels_pane';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_fieldable_panels_pane'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_image';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_map';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_quick_links';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_quick_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_spotlight';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_spotlight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_table';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_table'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_text';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_fieldable_panels_pane_video';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_fieldable_panels_pane_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_calendar_event';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'page_manager' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'rss' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'search_index' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'search_result' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_calendar_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_course';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_course'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_user_user';
  $strongarm->value = array(
    'status' => 0,
    'view modes' => array(
      'page_manager' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_user_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:11:"panels_page";s:23:"allowed_layout_settings";a:9:{s:8:"flexible";b:0;s:14:"twocol_stacked";b:0;s:13:"twocol_bricks";b:1;s:17:"threecol_25_50_25";b:0;s:25:"threecol_25_50_25_stacked";b:0;s:25:"threecol_33_34_33_stacked";b:1;s:6:"onecol";b:0;s:6:"twocol";b:1;s:17:"threecol_33_34_33";b:1;}s:10:"form_state";N;}';
  $export['panels_page_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_allowed_types';
  $strongarm->value = array(
    'forum_topic_legend-forum_topic_legend' => 'forum_topic_legend-forum_topic_legend',
    'vocabulary_terms-vocabulary_terms' => 0,
    'term_description-term_description' => 0,
    'term_list-term_list' => 0,
    'node_links-node_links' => 0,
    'node_created-node_created' => 0,
    'node_author-node_author' => 0,
    'node_comment_form-node_comment_form' => 0,
    'node_body-node_body' => 0,
    'node_terms-node_terms' => 0,
    'node_comments-node_comments' => 0,
    'node_type_desc-node_type_desc' => 0,
    'node_content-node_content' => 0,
    'node_attachments-node_attachments' => 0,
    'node_updated-node_updated' => 0,
    'node_title-node_title' => 0,
    'search_form-search_form' => 0,
    'search_result-search_result' => 0,
    'user_picture-user_picture' => 0,
    'user_signature-user_signature' => 0,
    'user_profile-user_profile' => 0,
    'comment_reply_form-comment_reply_form' => 0,
    'node_form_comment-node_form_comment' => 0,
    'node_form_title-node_form_title' => 0,
    'node_form_log-node_form_log' => 0,
    'node_form_language-node_form_language' => 0,
    'node_form_buttons-node_form_buttons' => 0,
    'node_form_author-node_form_author' => 0,
    'node_form_path-node_form_path' => 0,
    'node_form_publishing-node_form_publishing' => 0,
    'node_form_menu-node_form_menu' => 0,
    'node-node' => 0,
    'page_breadcrumb-page_breadcrumb' => 0,
    'page_primary_links-page_primary_links' => 0,
    'page_help-page_help' => 0,
    'page_logo-page_logo' => 0,
    'page_secondary_links-page_secondary_links' => 0,
    'page_actions-page_actions' => 0,
    'page_slogan-page_slogan' => 0,
    'page_tabs-page_tabs' => 0,
    'page_messages-page_messages' => 0,
    'page_title-page_title' => 0,
    'page_site_name-page_site_name' => 0,
    'page_feed_icons-page_feed_icons' => 0,
    'form-form' => 0,
    'node_prepopulate-node_prepopulate' => 0,
    'node_create_links-node_create_links' => 0,
    'membership_links-membership_links' => 0,
    'views_pager-views_pager' => 0,
    'views_attachments-views_attachments' => 0,
    'views_footer-views_footer' => 0,
    'views_row-views_row' => 0,
    'views_empty-views_empty' => 0,
    'views_header-views_header' => 0,
    'views_exposed-views_exposed' => 0,
    'views_feed-views_feed' => 0,
    'views_view-views_view' => 0,
    'forum_statistics-forum_statistics' => 0,
    'forum_search-forum_search' => 0,
    'forum_mark_read-forum_mark_read' => 0,
    'forum_node_create_list-forum_node_create_list' => 0,
    'forum_legend-forum_legend' => 0,
    'forum_topic_list_sort-forum_topic_list_sort' => 0,
    'forum_list-forum_list' => 0,
    'forum_tools-forum_tools' => 0,
    'forum_topic_list-forum_topic_list' => 0,
    'panelizer_form_default-panelizer_form_default' => 0,
    'entity_field_extra-fieldable_panels_pane:title' => 0,
    'entity_field_extra-node:take' => 0,
    'entity_field_extra-node:stats' => 0,
    'entity_field_extra-privatemsg_message:body' => 0,
    'entity_field_extra-file:file' => 0,
    'entity_field_extra-taxonomy_term:description' => 0,
    'entity_field_extra-user:privatemsg_send_new_message' => 0,
    'entity_field_extra-user:summary' => 0,
    'entity_field-comment:comment_body' => 0,
    'entity_field-fieldable_panels_pane:field_quick_links_links' => 0,
    'entity_field-fieldable_panels_pane:field_basic_file_file' => 0,
    'entity_field-fieldable_panels_pane:field_basic_file_text' => 0,
    'entity_field-fieldable_panels_pane:field_basic_image_caption' => 0,
    'entity_field-fieldable_panels_pane:field_basic_image_image' => 0,
    'entity_field-fieldable_panels_pane:field_basic_text_text' => 0,
    'entity_field-fieldable_panels_pane:field_map_address' => 0,
    'entity_field-fieldable_panels_pane:field_map_information' => 0,
    'entity_field-fieldable_panels_pane:field_basic_table_table' => 0,
    'entity_field-fieldable_panels_pane:field_video_file' => 0,
    'entity_field-fieldable_panels_pane:field_basic_spotlight_items' => 0,
    'entity_field-node:body' => 0,
    'entity_field-node:og_group_ref' => 0,
    'entity_field-node:group_content_access' => 0,
    'entity_field-node:field_date' => 0,
    'entity_field-node:group_group' => 0,
    'entity_field-node:field_courses' => 0,
    'entity_field-node:field_expiration' => 0,
    'entity_field-node:opigno_course_tools' => 0,
    'entity_field-node:course_required_quiz_ref' => 0,
    'entity_field-node:course_pretest_ref' => 0,
    'entity_field-node:group_access' => 0,
    'entity_field-node:field_course_places' => 0,
    'entity_field-node:quiz_weight' => 0,
    'entity_field-node:quiz_type' => 0,
    'entity_field-node:field_notification_add_calendar' => 0,
    'entity_field-node:field_notification_message' => 0,
    'entity_field-node:field_notification_send_email' => 0,
    'entity_field-node:taxonomy_forums' => 0,
    'entity_field-og_membership:og_membership_request' => 0,
    'entity_field-file:field_file_image_alt_text' => 0,
    'entity_field-file:field_file_image_title_text' => 0,
    'entity_field-taxonomy_term:og_group_ref' => 0,
    'entity_field-user:og_user_node' => 0,
    'token-node:comment-count' => 'token-node:comment-count',
    'token-node:comment-count-new' => 'token-node:comment-count-new',
    'token-node:comment' => 'token-node:comment',
    'token-node:course-required-quiz-ref' => 'token-node:course-required-quiz-ref',
    'token-node:course-pretest-ref' => 'token-node:course-pretest-ref',
    'token-node:group-access' => 'token-node:group-access',
    'token-node:field-course-places' => 'token-node:field-course-places',
    'token-node:quiz-weight' => 'token-node:quiz-weight',
    'token-node:og-group-ref' => 'token-node:og-group-ref',
    'token-node:group-content-access' => 'token-node:group-content-access',
    'token-node:quiz-type' => 'token-node:quiz-type',
    'token-node:og-membership' => 'token-node:og-membership',
    'token-node:og-membership--1' => 'token-node:og-membership--1',
    'token-node:og-membership--2' => 'token-node:og-membership--2',
    'token-node:og-membership--3' => 'token-node:og-membership--3',
    'token-node:og-group-ref--og-membership' => 'token-node:og-group-ref--og-membership',
    'token-node:og-group-ref--og-membership--1' => 'token-node:og-group-ref--og-membership--1',
    'token-node:og-group-ref--og-membership--2' => 'token-node:og-group-ref--og-membership--2',
    'token-node:og-group-ref--og-membership--3' => 'token-node:og-group-ref--og-membership--3',
    'token-node:field-courses' => 'token-node:field-courses',
    'token-node:field-expiration' => 'token-node:field-expiration',
    'token-node:taxonomy-forums' => 'token-node:taxonomy-forums',
    'token-node:field-date' => 'token-node:field-date',
    'token-node:field-notification-add-calendar' => 'token-node:field-notification-add-calendar',
    'token-node:field-notification-message' => 'token-node:field-notification-message',
    'token-node:field-notification-send-email' => 'token-node:field-notification-send-email',
    'token-comment:cid' => 'token-comment:cid',
    'token-comment:hostname' => 'token-comment:hostname',
    'token-comment:name' => 'token-comment:name',
    'token-comment:mail' => 'token-comment:mail',
    'token-comment:homepage' => 'token-comment:homepage',
    'token-comment:title' => 'token-comment:title',
    'token-comment:body' => 'token-comment:body',
    'token-comment:url' => 'token-comment:url',
    'token-comment:edit-url' => 'token-comment:edit-url',
    'token-comment:created' => 'token-comment:created',
    'token-comment:changed' => 'token-comment:changed',
    'token-comment:parent' => 'token-comment:parent',
    'token-comment:node' => 'token-comment:node',
    'token-comment:author' => 'token-comment:author',
    'token-comment:subject' => 'token-comment:subject',
    'token-comment:status' => 'token-comment:status',
    'token-comment:comment-body' => 'token-comment:comment-body',
    'token-date-field-value:date' => 'token-date-field-value:date',
    'token-date-field-value:to-date' => 'token-date-field-value:to-date',
    'token-privatemsg_message:mid' => 'token-privatemsg_message:mid',
    'token-privatemsg_message:thread-id' => 'token-privatemsg_message:thread-id',
    'token-privatemsg_message:url' => 'token-privatemsg_message:url',
    'token-privatemsg_message:subject' => 'token-privatemsg_message:subject',
    'token-privatemsg_message:body' => 'token-privatemsg_message:body',
    'token-privatemsg_message:timestamp' => 'token-privatemsg_message:timestamp',
    'token-privatemsg_message:author' => 'token-privatemsg_message:author',
    'token-privatemsg_message:recipient' => 'token-privatemsg_message:recipient',
    'token-site:og-context--node' => 'token-site:og-context--node',
    'token-term:tid' => 'token-term:tid',
    'token-term:name' => 'token-term:name',
    'token-term:description' => 'token-term:description',
    'token-term:node-count' => 'token-term:node-count',
    'token-term:url' => 'token-term:url',
    'token-term:vocabulary' => 'token-term:vocabulary',
    'token-term:parent' => 'token-term:parent',
    'token-term:weight' => 'token-term:weight',
    'token-term:parents-all' => 'token-term:parents-all',
    'token-term:og-group-ref' => 'token-term:og-group-ref',
    'token-term:og-membership' => 'token-term:og-membership',
    'token-term:og-membership--1' => 'token-term:og-membership--1',
    'token-term:og-membership--2' => 'token-term:og-membership--2',
    'token-term:og-membership--3' => 'token-term:og-membership--3',
    'token-term:og-group-ref--og-membership' => 'token-term:og-group-ref--og-membership',
    'token-term:og-group-ref--og-membership--1' => 'token-term:og-group-ref--og-membership--1',
    'token-term:og-group-ref--og-membership--2' => 'token-term:og-group-ref--og-membership--2',
    'token-term:og-group-ref--og-membership--3' => 'token-term:og-group-ref--og-membership--3',
    'token-vocabulary:vid' => 'token-vocabulary:vid',
    'token-vocabulary:name' => 'token-vocabulary:name',
    'token-vocabulary:description' => 'token-vocabulary:description',
    'token-vocabulary:node-count' => 'token-vocabulary:node-count',
    'token-vocabulary:term-count' => 'token-vocabulary:term-count',
    'token-list<comment>:0' => 'token-list<comment>:0',
    'token-list<comment>:1' => 'token-list<comment>:1',
    'token-list<comment>:2' => 'token-list<comment>:2',
    'token-list<comment>:3' => 'token-list<comment>:3',
    'token-list<privatemsg_message>:0' => 'token-list<privatemsg_message>:0',
    'token-list<privatemsg_message>:1' => 'token-list<privatemsg_message>:1',
    'token-list<privatemsg_message>:2' => 'token-list<privatemsg_message>:2',
    'token-list<privatemsg_message>:3' => 'token-list<privatemsg_message>:3',
    'token-list<term>:0' => 'token-list<term>:0',
    'token-list<term>:1' => 'token-list<term>:1',
    'token-list<term>:2' => 'token-list<term>:2',
    'token-list<term>:3' => 'token-list<term>:3',
    'token-list<vocabulary>:0' => 'token-list<vocabulary>:0',
    'token-list<vocabulary>:1' => 'token-list<vocabulary>:1',
    'token-list<vocabulary>:2' => 'token-list<vocabulary>:2',
    'token-list<vocabulary>:3' => 'token-list<vocabulary>:3',
    'token-node:nid' => 0,
    'token-node:vid' => 0,
    'token-node:tnid' => 0,
    'token-node:type' => 0,
    'token-node:type-name' => 0,
    'token-node:title' => 0,
    'token-node:body' => 0,
    'token-node:summary' => 0,
    'token-node:language' => 0,
    'token-node:url' => 0,
    'token-node:edit-url' => 0,
    'token-node:created' => 0,
    'token-node:changed' => 0,
    'token-node:author' => 0,
    'token-node:is-new' => 0,
    'token-node:status' => 0,
    'token-node:promote' => 0,
    'token-node:sticky' => 0,
    'token-node:source' => 0,
    'token-node:log' => 0,
    'token-node:revision' => 0,
    'token-node:group-group' => 0,
    'token-node:members' => 0,
    'token-node:members--1' => 0,
    'token-node:members--2' => 0,
    'token-node:members--3' => 0,
    'token-file-type:name' => 0,
    'token-file-type:machine-name' => 0,
    'token-file-type:count' => 0,
    'token-file-type:edit-url' => 0,
    'token-file:type' => 0,
    'token-file:fid' => 0,
    'token-file:name' => 0,
    'token-file:path' => 0,
    'token-file:mime' => 0,
    'token-file:size' => 0,
    'token-file:url' => 0,
    'token-file:timestamp' => 0,
    'token-file:owner' => 0,
    'token-file:field-file-image-alt-text' => 0,
    'token-file:field-file-image-title-text' => 0,
    'token-site:name' => 0,
    'token-site:slogan' => 0,
    'token-site:mail' => 0,
    'token-site:url' => 0,
    'token-site:url-brief' => 0,
    'token-site:login-url' => 0,
    'token-site:current-user' => 0,
    'token-site:current-date' => 0,
    'token-site:current-page' => 0,
    'token-date:short' => 0,
    'token-date:medium' => 0,
    'token-date:long' => 0,
    'token-date:custom' => 0,
    'token-date:since' => 0,
    'token-date:raw' => 0,
    'token-user:uid' => 0,
    'token-user:name' => 0,
    'token-user:mail' => 0,
    'token-user:url' => 0,
    'token-user:edit-url' => 0,
    'token-user:last-login' => 0,
    'token-user:created' => 0,
    'token-user:last-access' => 0,
    'token-user:roles' => 0,
    'token-user:status' => 0,
    'token-user:theme' => 0,
    'token-user:og-user-node' => 0,
    'token-user:og-membership' => 0,
    'token-user:og-membership--1' => 0,
    'token-user:og-membership--2' => 0,
    'token-user:og-membership--3' => 0,
    'token-user:og-user-node--og-membership' => 0,
    'token-user:og-user-node--og-membership--1' => 0,
    'token-user:og-user-node--og-membership--2' => 0,
    'token-user:og-user-node--og-membership--3' => 0,
    'token-view:name' => 0,
    'token-view:description' => 0,
    'token-view:machine-name' => 0,
    'token-view:title' => 0,
    'token-view:url' => 0,
    'token-rules_text:value' => 0,
    'token-rules_integer:value' => 0,
    'token-rules_uri:value' => 0,
    'token-rules_token:value' => 0,
    'token-rules_decimal:value' => 0,
    'token-rules_date:value' => 0,
    'token-rules_duration:value' => 0,
    'token-fieldable_panels_pane:field-quick-links-links' => 0,
    'token-fieldable_panels_pane:field-basic-file-file' => 0,
    'token-fieldable_panels_pane:field-basic-file-text' => 0,
    'token-fieldable_panels_pane:field-basic-image-caption' => 0,
    'token-fieldable_panels_pane:field-basic-image-image' => 0,
    'token-fieldable_panels_pane:field-basic-text-text' => 0,
    'token-fieldable_panels_pane:field-map-address' => 0,
    'token-fieldable_panels_pane:field-map-information' => 0,
    'token-fieldable_panels_pane:field-video-file' => 0,
    'token-og_membership_type:id' => 0,
    'token-og_membership_type:description' => 0,
    'token-og_membership_type:status' => 0,
    'token-og_membership_type:module' => 0,
    'token-og_membership_type:language' => 0,
    'token-og_membership:id' => 0,
    'token-og_membership:type' => 0,
    'token-og_membership:entity-type' => 0,
    'token-og_membership:group-type' => 0,
    'token-og_membership:state' => 0,
    'token-og_membership:created' => 0,
    'token-og_membership:field-name' => 0,
    'token-og_membership:language' => 0,
    'token-og_membership:og-membership-request' => 0,
    'token-rules_config:id' => 0,
    'token-rules_config:label' => 0,
    'token-rules_config:plugin' => 0,
    'token-rules_config:active' => 0,
    'token-rules_config:weight' => 0,
    'token-rules_config:status' => 0,
    'token-rules_config:dirty' => 0,
    'token-rules_config:module' => 0,
    'token-rules_config:access-exposed' => 0,
    'token-list<fieldable_panels_pane>:0' => 0,
    'token-list<fieldable_panels_pane>:1' => 0,
    'token-list<fieldable_panels_pane>:2' => 0,
    'token-list<fieldable_panels_pane>:3' => 0,
    'token-list<node>:0' => 0,
    'token-list<node>:1' => 0,
    'token-list<node>:2' => 0,
    'token-list<node>:3' => 0,
    'token-list<og_membership_type>:0' => 0,
    'token-list<og_membership_type>:1' => 0,
    'token-list<og_membership_type>:2' => 0,
    'token-list<og_membership_type>:3' => 0,
    'token-list<og_membership>:0' => 0,
    'token-list<og_membership>:1' => 0,
    'token-list<og_membership>:2' => 0,
    'token-list<og_membership>:3' => 0,
    'token-list<file>:0' => 0,
    'token-list<file>:1' => 0,
    'token-list<file>:2' => 0,
    'token-list<file>:3' => 0,
    'token-list<user>:0' => 0,
    'token-list<user>:1' => 0,
    'token-list<user>:2' => 0,
    'token-list<user>:3' => 0,
    'token-list<rules_config>:0' => 0,
    'token-list<rules_config>:1' => 0,
    'token-list<rules_config>:2' => 0,
    'token-list<rules_config>:3' => 0,
    'token-list<date>:0' => 0,
    'token-list<date>:1' => 0,
    'token-list<date>:2' => 0,
    'token-list<date>:3' => 0,
    'entity_form_field-comment:comment_body' => 'entity_form_field-comment:comment_body',
    'entity_form_field-fieldable_panels_pane:field_quick_links_links' => 'entity_form_field-fieldable_panels_pane:field_quick_links_links',
    'entity_form_field-fieldable_panels_pane:field_basic_file_file' => 'entity_form_field-fieldable_panels_pane:field_basic_file_file',
    'entity_form_field-fieldable_panels_pane:field_basic_file_text' => 'entity_form_field-fieldable_panels_pane:field_basic_file_text',
    'entity_form_field-fieldable_panels_pane:field_basic_image_caption' => 'entity_form_field-fieldable_panels_pane:field_basic_image_caption',
    'entity_form_field-fieldable_panels_pane:field_basic_image_image' => 'entity_form_field-fieldable_panels_pane:field_basic_image_image',
    'entity_form_field-fieldable_panels_pane:field_basic_text_text' => 'entity_form_field-fieldable_panels_pane:field_basic_text_text',
    'entity_form_field-fieldable_panels_pane:field_map_address' => 'entity_form_field-fieldable_panels_pane:field_map_address',
    'entity_form_field-fieldable_panels_pane:field_map_information' => 'entity_form_field-fieldable_panels_pane:field_map_information',
    'entity_form_field-fieldable_panels_pane:field_basic_table_table' => 'entity_form_field-fieldable_panels_pane:field_basic_table_table',
    'entity_form_field-fieldable_panels_pane:field_video_file' => 'entity_form_field-fieldable_panels_pane:field_video_file',
    'entity_form_field-fieldable_panels_pane:field_basic_spotlight_items' => 'entity_form_field-fieldable_panels_pane:field_basic_spotlight_items',
    'entity_form_field-node:body' => 'entity_form_field-node:body',
    'entity_form_field-node:og_group_ref' => 'entity_form_field-node:og_group_ref',
    'entity_form_field-node:group_content_access' => 'entity_form_field-node:group_content_access',
    'entity_form_field-node:field_date' => 'entity_form_field-node:field_date',
    'entity_form_field-node:group_group' => 'entity_form_field-node:group_group',
    'entity_form_field-node:field_courses' => 'entity_form_field-node:field_courses',
    'entity_form_field-node:field_expiration' => 'entity_form_field-node:field_expiration',
    'entity_form_field-node:opigno_course_tools' => 'entity_form_field-node:opigno_course_tools',
    'entity_form_field-node:course_required_quiz_ref' => 'entity_form_field-node:course_required_quiz_ref',
    'entity_form_field-node:course_pretest_ref' => 'entity_form_field-node:course_pretest_ref',
    'entity_form_field-node:group_access' => 'entity_form_field-node:group_access',
    'entity_form_field-node:field_course_places' => 'entity_form_field-node:field_course_places',
    'entity_form_field-node:quiz_weight' => 'entity_form_field-node:quiz_weight',
    'entity_form_field-node:quiz_type' => 'entity_form_field-node:quiz_type',
    'entity_form_field-node:field_notification_add_calendar' => 'entity_form_field-node:field_notification_add_calendar',
    'entity_form_field-node:field_notification_message' => 'entity_form_field-node:field_notification_message',
    'entity_form_field-node:field_notification_send_email' => 'entity_form_field-node:field_notification_send_email',
    'entity_form_field-node:taxonomy_forums' => 'entity_form_field-node:taxonomy_forums',
    'entity_form_field-og_membership:og_membership_request' => 'entity_form_field-og_membership:og_membership_request',
    'entity_form_field-file:field_file_image_alt_text' => 'entity_form_field-file:field_file_image_alt_text',
    'entity_form_field-file:field_file_image_title_text' => 'entity_form_field-file:field_file_image_title_text',
    'entity_form_field-taxonomy_term:og_group_ref' => 'entity_form_field-taxonomy_term:og_group_ref',
    'entity_form_field-user:og_user_node' => 'entity_form_field-user:og_user_node',
    'block-opigno-opigno_tools_block' => 'block-opigno-opigno_tools_block',
    'block-opigno-opigno_tool_actions_block' => 'block-opigno-opigno_tool_actions_block',
    'block-calendar-calendar_legend' => 0,
    'block-comment-recent' => 0,
    'block-crumbs-breadcrumb' => 0,
    'block-locale-language' => 0,
    'block-menu-devel' => 0,
    'block-node-syndicate' => 0,
    'block-node-recent' => 0,
    'block-og_extras-group_info' => 0,
    'block-og_extras-node_links' => 0,
    'block-privatemsg-privatemsg-menu' => 0,
    'block-privatemsg-privatemsg-new' => 0,
    'block-search-form' => 0,
    'block-system-powered-by' => 0,
    'block-system-help' => 0,
    'block-system-navigation' => 0,
    'block-system-management' => 0,
    'block-system-user-menu' => 0,
    'block-system-main-menu' => 0,
    'block-user-login' => 0,
    'block-user-new' => 0,
    'block-user-online' => 0,
    'block-forum-active' => 0,
    'block-forum-new' => 0,
    'block-devel-execute_php' => 0,
    'block-devel-switch_user' => 0,
    'custom-custom' => 'custom-custom',
    'entity_view-comment' => 0,
    'entity_view-fieldable_panels_pane' => 0,
    'entity_view-node' => 0,
    'entity_view-og_membership_type' => 0,
    'entity_view-og_membership' => 0,
    'entity_view-file' => 0,
    'entity_view-taxonomy_term' => 0,
    'entity_view-user' => 0,
    'entity_view-rules_config' => 0,
    'fieldable_panels_pane-quick_links' => 'fieldable_panels_pane-quick_links',
    'fieldable_panels_pane-basic_file' => 'fieldable_panels_pane-basic_file',
    'fieldable_panels_pane-image' => 'fieldable_panels_pane-image',
    'fieldable_panels_pane-text' => 'fieldable_panels_pane-text',
    'fieldable_panels_pane-map' => 'fieldable_panels_pane-map',
    'fieldable_panels_pane-table' => 'fieldable_panels_pane-table',
    'fieldable_panels_pane-video' => 'fieldable_panels_pane-video',
    'fieldable_panels_pane-spotlight' => 'fieldable_panels_pane-spotlight',
    'fieldable_panels_pane-fieldable_panels_pane' => 0,
    'menu_tree-_active' => 0,
    'menu_tree-devel' => 0,
    'menu_tree-management' => 0,
    'menu_tree-main-menu' => 0,
    'menu_tree-navigation' => 0,
    'menu_tree-user-menu' => 0,
    'views_panes-opigno_quizzes-panel_pane_1' => 'views_panes-opigno_quizzes-panel_pane_1',
    'views_panes-opigno_quiz_student_views-panel_pane_1' => 'views_panes-opigno_quiz_student_views-panel_pane_1',
    'views_panes-opigno_quiz_teacher_views-panel_pane_1' => 'views_panes-opigno_quiz_teacher_views-panel_pane_1',
    'views_panes-og_members-panel_pane_1' => 'views_panes-og_members-panel_pane_1',
    'views_panes-og_nodes-panel_pane_1' => 'views_panes-og_nodes-panel_pane_1',
    'views_panes-panopoly_widgets_general_content-list_of_content' => 'views_panes-panopoly_widgets_general_content-list_of_content',
    'views_panes-og_user_groups-panel_pane_1' => 0,
    'views_panes-og_all_user_group_content-panel_pane_1' => 0,
    'views_panes-panopoly_widgets_general_content-piece_of_content' => 0,
    'views-opigno_quizzes' => 'views-opigno_quizzes',
    'views-opigno_quiz_student_views' => 'views-opigno_quiz_student_views',
    'views-opigno_quiz_teacher_views' => 'views-opigno_quiz_teacher_views',
    'views-og_members' => 'views-og_members',
    'views-og_user_groups' => 0,
    'views-course_catalogue' => 0,
    'views-og_extras_members' => 0,
    'views-og_extras_groups' => 0,
    'views-notification_view' => 0,
    'views-advanced_forum_active_topics' => 0,
    'views-advanced_forum_group_topic_list' => 0,
    'views-advanced_forum_new_topics' => 0,
    'views-advanced_forum_topic_list' => 0,
    'views-advanced_forum_unanswered_topics' => 0,
    'views-fieldable_pane_entities' => 0,
    'views-fieldable_pane_entity_revisions' => 0,
    'views-media_default' => 0,
    'views-og_all_user_group_content' => 0,
    'views-og_extras_nodes' => 0,
    'views-og_massadd' => 0,
    'views-og_members_admin' => 0,
    'views-og_nodes' => 0,
    'views-calendar_dashboard' => 0,
    'views-opigno_forum_display_view' => 0,
    'views-panopoly_widgets_general_content' => 0,
    'views-questions_by_quiz' => 0,
    'views-questions_by_quiz_version' => 0,
    'views-quiz_by_author' => 0,
    'views-quiz_by_taker' => 0,
  );
  $export['panels_page_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panels_page_default';
  $strongarm->value = array(
    'entity_field_extra' => 'entity_field_extra',
    'entity_field' => 'entity_field',
    'token' => 'token',
    'entity_form_field' => 'entity_form_field',
    'block' => 'block',
    'custom' => 'custom',
    'entity_view' => 'entity_view',
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'menu_tree' => 'menu_tree',
    'views_panes' => 'views_panes',
    'views' => 'views',
    'other' => 'other',
  );
  $export['panels_page_default'] = $strongarm;

  return $export;
}
