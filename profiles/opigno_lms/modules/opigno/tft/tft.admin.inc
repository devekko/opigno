<?php

/**
 * Taxonomy File Tree settings form
 */
function tft_settings_form() {
  $taxonomy = taxonomy_get_vocabularies();
  $vocabularies = array();
  $node_types = array();
  
  // Get all vocabularies
  foreach ($taxonomy as $vid => $voc) {
    $vocabularies[$vid] = $voc->name;
  }
  
  $result = db_query("SELECT {field_config_instance}.bundle, {field_config_instance}.field_name FROM {field_config_instance}
                        LEFT JOIN {field_config} ON {field_config}.field_name = {field_config_instance}.field_name
                      WHERE {field_config}.module = 'file'");
  
  // Get all node types with a filefield
  while ($row = $result->fetchAssoc()) {
    $node_types[$row['bundle'] . '-' . $row['field_name']] = $row['bundle'] . '->' . $row['field_name'];
  }  
  
  $form['tft_vocabulary_vid'] = array(
    '#type' => 'radios',
    '#title' => t("File tree vocabulary"),
    '#options' => $vocabularies,
    '#required' => TRUE,
    '#default_value' => variable_get('tft_vocabulary_vid', 0),
  );
  
  $form['tft_content_type'] = array(
    '#type' => 'radios',
    '#title' => t("File node type -> filefield"),
    '#description' => t("Set which node type must act as the 'file' (must contain a filefield)."),
    '#options' => $node_types,
    '#required' => TRUE,
    '#default_value' => variable_get('tft_content_type', 0),
  );

  $form['add_archive_folders'] = array(
    '#type' => 'button',
    '#name' => 'add_archive_folders',
    '#value' => t("Add archive folders to all OG file trees"),
  );

  return system_settings_form($form);
}

function tft_settings_form_validate($form, $form_state) {
  if ($form_state['clicked_button']['#name'] == 'add_archive_folders') {
    tft_archive_folder_batch();

    batch_process();
  }
}

/**
 * Reorganise terms under the given term tid.
 * 
 * @param int $tid = 0
 *          The top most parent term tid or 0 for root terms
 *
 * @return string
 *          The HTML
 */
function tft_manage_folders_form($form, $form_state, $tid = 0, $use_hierarchy = TRUE, $use_weight = TRUE) {
  drupal_add_css(drupal_get_path('module', 'tft') . '/css/tft.css');
  drupal_add_js(drupal_get_path('module', 'tft') . '/js/tft.js');
//  drupal_add_js(drupal_get_path('module', 'tft') . '/js/tft.tabledrag.js');
  $tree = tft_tree($tid);
  $form = array();

  if (!tft_term_access($tid)) {
    drupal_access_denied();
    return;
  }

  if (!$tid) {
    $root_depth = 0;
  }
  else {
    $root_depth = tft_get_depth($tid) + 1;
  }

  $form['#tid'] = $tid;
  
  $form['table'] = array(
    '#tree' => TRUE,
  );
  
  _tft_manage_folders_form($tree, $form, $root_depth, $tid, $use_hierarchy, $use_weight);
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  if (isset($_GET['destination'])) {
    $_SESSION['tft']['q'] = $_GET['destination'];
    
    $url = str_replace('%23', '#', $_GET['destination']);
  }
  elseif (isset($_SESSION['tft']['q'])) {
    $url = str_replace('%23', '#', $_SESSION['tft']['q']);
  }
  
  if ($url) {
    $form['cancel'] = array(
      '#value' => '<a href="' . base_path() . $url . '">' . t("cancel") . '</a>',
    );
  }
  
  return $form;
}

/**
 * Form helper. Flattens the terms tree and creates the form elements.
 * @see tft_manage_folders_form()
 *
 * @param array $tree
 *            The current tree level to be rendered
 * @param array &$form
 *            A reference to the form array
 * @param int $root_depth = 0
 *            The depth of the root term
 * @param int $root_tid = NULL
 *            The root tid
 * @param bool $use_hierarchy = TRUE
 *            Allow users to change the hierarchy.
 * @param bool $use_wight = FALSE
 *            Allow users to reorder elements.
 */
function _tft_manage_folders_form($tree, &$form, $root_depth = 0, $root_tid = NULL, $use_hierarchy = TRUE, $use_weight = FALSE) {
  if (!isset($form['#use_hierarchy'])) {
    $form['#use_hierarchy'] = $use_hierarchy;
    $form['#use_weight'] = $use_weight;
  }

  foreach ($tree as $data) {
    if ($root_tid && isset($data['tid']) && $data['tid'] == tft_get_archive_tid($root_tid)) {
      continue;
    }

    $data['depth'] = isset($data['tid']) ? tft_get_depth($data['tid']) - $root_depth : tft_get_depth($data['parent']) - $root_depth + 1;
    
    $key = 'tft-admin-' . (isset($data['nid']) ? 'node-' . $data['nid'] : 'term-' . $data['tid']);

    $form['table'][$key] = array();

    $form['table'][$key]['name'] = array(
      '#type' => 'textfield',
      '#default_value' => $data['name'],
      '#maxlength' => 255,
      '#required' => TRUE,
    );

    if (isset($data['type']) && $data['type'] == 'node') {
      $form['table'][$key]['name']['#required'] = FALSE;
      $form['table'][$key]['name']['#attributes'] = array(
        'disabled' =>  'disabled',
      );
    }

    if ($use_hierarchy) {
      $form['table'][$key]['parent'] = array(
        '#type' => 'textfield',
        '#default_value' => $data['parent'],
        '#size' => 6,
        '#attributes' => array('class' => array('taxonomy_term_hierarchy-parent')),
      );
    }

    $form['table'][$key]['id'] = array(
      '#type' => 'hidden',
      '#default_value' => isset($data['nid']) ? $data['nid'] : $data['tid'],
      '#attributes' => array('class' => array('taxonomy_term_hierarchy-tid')),
    );

    $form['table'][$key]['type'] = array(
      '#type' => 'hidden',
      '#value' => isset($data['type']) ? $data['type'] : 'term',
    );

    if ($use_hierarchy) {
      $form['table'][$key]['depth'] = array(
        '#type' => 'value',
        '#value' => $data['depth'],
      );
    }

    if ($use_weight) {
      $form['table'][$key]['weight'] = array(
        '#type' => 'weight',
        '#delta' => 50,
        '#default_value' => $data['weight'],
        '#attributes' => array('class' => array('taxonomy_term_hierarchy-weight')),
      );
    }
    
    if (isset($data['children'])) {
      _tft_manage_folders_form($data['children'], $form, $root_depth, $root_tid, $use_hierarchy, $use_weight);
    }
  }
}

/**
 * Theme the term reordering form.
 * @see tft_manage_folders_form()
 *
 * @param array $form
 *              The form
 *
 * @return string
 *              The rendered form as HTML
 */
function theme_tft_manage_folders_form($vars) {
  $form = $vars['form'];

  if ($form['#use_hierarchy']) {
    drupal_add_tabledrag('tft-outline', 'match', 'parent', 'taxonomy_term_hierarchy-parent', 'taxonomy_term_hierarchy-parent', 'taxonomy_term_hierarchy-tid');
  }

  if ($form['#use_weight']) {
    drupal_add_tabledrag('tft-outline', 'order', 'sibling', 'taxonomy_term_hierarchy-weight');
  }

  $header = array(t('Name'));

  if ($form['#use_hierarchy']) {
    $header[] = t('Parent');
  }

  if ($form['#use_weight']) {
    $header[] = t('Weight');
  }

  $rows = array();

  foreach ($form['table'] as $key => $item) {
    if (is_array($item) && preg_match('/tft\-admin\-(node|term)-[0-9]+/', $key)) {
      $data = array();

      if ($item['type']['#value'] == 'term') {
        $path = drupal_get_path('module', 'tft') . '/img/folder.png';
      }
      else {
        $setting = tft_get_file_setting();

        $db_table = 'field_data_' . $setting['field'];

        $db_table = db_escape_field($db_table);
        $db_field = db_escape_field($setting['field'] . '_fid');

        $mime = db_query("SELECT f.filemime FROM {node_revision} v
                            LEFT JOIN {node} n ON n.vid = v.vid
                              LEFT JOIN {".$db_table."} c ON c.revision_id = v.vid
                                LEFT JOIN {file_managed} f ON c.$db_field = f.fid
                        WHERE n.nid = :nid", array(':nid' => $item['id']['#default_value']))->fetchField();

        $file = (object) array('filemime' => $mime);
        $path = file_icon_path($file);
      }

      $icon = theme('image', array('path' => $path, 'attributes' => array('class' => array('tft-admin-folder-content-item'))));

      $data[] = theme('indentation', array('size' => isset($item['depth']['#value']) ? $item['depth']['#value'] : 0)) . $icon . drupal_render($item['name']);

      if ($form['#use_hierarchy']) {
        $data[] = drupal_render($item['parent']) . drupal_render($item['id']) . drupal_render($item['type']);
      }
      
      if ($form['#use_weight']) {
        $data[] = drupal_render($item['weight']);
      }

      $row = array('data' => $data);

      if (isset($item['#attributes'])) {
        $row = array_merge($row, $item['#attributes']);
      }
      
      $row['class'][] = 'draggable' . ($item['type']['#value'] == 'node' ? ' tabledrag-leaf' : '');
      
      $rows[] = $row;
    }
  }
  
  $form['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'tft-outline'))),
    '#weight' => 1,
  );

  return drupal_render_children($form);
}

/**
 * Form submission callback.
 * @see tft_manage_folders_form()
 */
function tft_manage_folders_form_submit($form, &$form_state) {
  foreach ($form_state['values']['table'] as $key => $item) {
    if ($form['#use_hierarchy'] && $item['type'] == 'term') {
      db_update('taxonomy_term_hierarchy')->fields(array('parent' => $item['parent']))->condition('tid', $item['id'])->execute();
    }
    else {
      $node = node_load($item['id']);
      // Reconstruct list of terms by removing all folder terms.
      $node->tft_folder[LANGUAGE_NONE][0]['tid'] = $item['parent'];

      node_save($node);
    }

    if ($form['#use_weight']) {
      db_delete('tft_folder_content_weight')->condition('type', $item['type'])->condition('id', $item['id'])->execute();
      db_insert('tft_folder_content_weight')->fields(array(
        'id' => $item['id'],
        'type' => $item['type'],
        'parent_tid' => $form['#tid'],
        'weight' => $item['weight']
      ))->execute();
    }

    if ($item['type'] == 'term') {
      db_update('taxonomy_term_data')->fields(array('name' => $item['name']))->condition('tid', $item['id'])->execute();
    }
  }
}

/**
 * Add a term form.
 */
function tft_add_term_form() {
  // Check that a vocabulary is set for Taxonomy File Tree
  tft_check_vocabulary_setting();
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t("Name"),
    '#required' => TRUE,
    '#weight' => -10,
  );
  
  $parent = !empty($_GET['parent']) ? (int) $_GET['parent'] : 0;
  
  if (!tft_term_access($parent)) {
    drupal_set_message(t("You do not have access to this folder. You cannot modify or delete it."), 'error');
    
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
  
  $form['parent'] = array(
    '#type' => 'hidden',
    '#value' => $parent,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Add"),
  );
  
  $form['cancel'] = array(
    '#value' => '<a href="/' . str_replace('%23', '#', $_GET['destination']) . '">' . t("cancel") . '</a>',
  );
  
  return $form;
}

/**
 * Validation callback.
 * @see tft_add_term_form()
 */
function tft_add_term_form_validate($form, &$form_state) {
  // If the user can only add terms to an OG term
  if (!user_access(TFT_ADD_TERMS)) {
    if (!tft_term_access($form_state['values']['parent'])) {
      form_set_error('name');
      
      drupal_set_message(t("You must select a parent folder that is part of a group you're a member of."), 'error');
      
      if ($_GET['destination']) {
        drupal_goto(urldecode($_GET['destination']));
      }
      else {
        drupal_goto();
      }
      
      exit();
    }
  }
  
  // Check for forbidden characters
  if (strpos($form_state['values']['name'], ',') !== FALSE || strpos($form_state['values']['name'], '+') !== FALSE) {
    form_set_error('name', t("The following characters are not allowed: ',' (comma) and +"));
  }
}

/**
 * Submission callback.
 * @see tft_add_term_form()
 *
 * @return int
 *        The last inserted term tid
 */
function tft_add_term_form_submit($form, &$form_state) {
  // Add the term data
  $term = (object) array(
    'vid' => variable_get('tft_vocabulary_vid', 0),
    'name' => $form_state['values']['name'],
    'parent' => $form_state['values']['parent'],
  );
  taxonomy_term_save($term);
  return $term->tid;
}

/**
 * Edit a term form.
 */
function tft_edit_term_form($form, $form_state, $tid) {
  // Check that a vocabulary is set for Taxonomy File Tree
  tft_check_vocabulary_setting();
  
  if (!tft_term_access($tid)) {
    drupal_set_message(t("You do not have access to this folder. You cannot modify or delete it."), 'error');
    
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  if (tft_is_archive_folder($tid)) {
    drupal_set_message(t("Archive folders cannot be edited."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
  
  $name = db_query("SELECT name FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $tid))->fetchField();
  
  // If no name was found
  if (!$name) {
    drupal_set_message(t("An error occured. The '@tid' folder could not be found. Please contac tthe site administrator.", array('@tid' => $tid)), 'error');
    
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t("Name"),
    '#required' => TRUE,
    '#default_value' => $name,
    '#weight' => -10,
  );
  
  $form['tid'] = array(
    '#type' => 'hidden',
    '#value' => $tid,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save"),
  );
  
  $form['cancel'] = array(
    '#value' => '<a href="/' . str_replace('%23', '#', $_GET['destination']) . '">' . t("cancel") . '</a>',
  );
  
  return $form;
}

/**
 * Validation callback
 * @see tft_edit_term_form()
 */
function tft_edit_term_form_validate($form, &$form_state) {
  // Check for forbidden characters
  if (strpos($form_state['values']['name'], ',') !== FALSE || strpos($form_state['values']['name'], '+') !== FALSE) {
    form_set_error('name', t("The following characters are not allowed: ',' (comma) and +"));
  }
}

/**
 * Submission callback
 * @see tft_edit_term_form()
 */
function tft_edit_term_form_submit($form, &$form_state) {
  // Update the term name
  db_update('taxonomy_term_data')->fields(array('name' => $form_state['values']['name']))->condition('tid', $form_state['values']['tid'])->execute();
  
  drupal_set_message(t("The folder '@name' was updated.", array('@name' => $form_state['values']['name'])));
}

/**
 * Delete a term form
 */
function tft_delete_term_form($form, $form_state, $tid) {
  // Check that a vocabulary is set for Taxonomy File Tree
  tft_check_vocabulary_setting();
  
  if (!tft_term_access($tid)) {
    drupal_set_message(t("You do not have access to this folder. You cannot modify or delete it."), 'error');
    
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  if (tft_is_archive_folder($tid)) {
    drupal_set_message(t("Archive folders cannot be deleted."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
  
  $name = db_query("SELECT name FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $tid))->fetchField();
    
  // If no name was found
  if (!$name) {
    drupal_set_message(t("An error occured. The '@tid' folder could not be found. Please contac tthe site administrator.", array('@tid' => $tid)), 'error');
    
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
  
  // Check that this term has no child terms or files
  if (tft_check_term_is_deletable($tid)) {    
    drupal_set_title(t("Are you sure you want to delete the folder @term ?", array('@term' => $name)));
    
    $form['tid'] = array(
      '#type' => 'hidden',
      '#value' => $tid,
    );
    
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Delete"),
      '#attributes' => array('class' => array('delete-button')),
    );
    
    $form['cancel'] = array(
      '#markup' => '<a href="/' . str_replace('%23', '#', $_GET['destination']) . '">' . t("cancel") . '</a>',
    );
  
    return $form;
  }
  else {
    drupal_set_message(t("<em>@name</em> contains files and/or child folders. Move or delete these before deleting this folder.", array('@name' => $name)), 'error');
      
    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }
}

/**
 * Submission callback
 * @see tft_delete_term_form()
 */
function tft_delete_term_form_submit($form, $form_state) {
  taxonomy_term_delete($form_state['values']['tid']);
}

/**
 * Check if the term has no files or child terms
 */
function tft_check_term_is_deletable($tid) {
  $count = (int) db_query("SELECT COUNT(tid) FROM {taxonomy_term_hierarchy} WHERE parent = :tid", array(':tid' => $tid))->fetchField();
  
  if ($count) {
    return FALSE;
  }
  
  $count = (int) db_query("SELECT COUNT({taxonomy_index}.nid) FROM {taxonomy_index}
                              RIGHT JOIN {node} ON {node}.nid = {taxonomy_index}.nid
                            WHERE {taxonomy_index}.tid = :tid", array(':tid' => $tid))->fetchField();
  
  if ($count) {
    return FALSE;
  }
  
  return TRUE;
}

/**
 * Archive a term form
 */
function tft_archive_term_form($form, $form_state, $tid) {
  // Check that a vocabulary is set for Taxonomy File Tree
  tft_check_vocabulary_setting();

  if (!tft_term_access($tid)) {
    drupal_set_message(t("You do not have access to this folder. You cannot edit or delete it."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  if (tft_is_archive_folder($tid)) {
    drupal_set_message(t("Archive folders cannot be archived."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  $name = db_query("SELECT name FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $tid))->fetchField();

  // If no name was found
  if (!$name) {
    drupal_set_message(t("An error occured. The '@tid' folder could not be found. Please contac tthe site administrator.", array('@tid' => $tid)), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  drupal_set_title(t("Are you sure you want to delete folder <em>@term</em> ?", array('@term' => $name)));

  $form['tid'] = array(
    '#type' => 'hidden',
    '#value' => $tid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => "Archiver",
  );

  $form['cancel'] = array(
    '#value' => '<a href="/' . str_replace('%23', '#', $_GET['destination']) . '">' . t("cancel") . '</a>',
  );

  return $form;
}

/**
 * Submission callback
 * @see tft_archive_term_form()
 */
function tft_archive_term_form_submit($form, $form_state) {
  $name = db_query("SELECT name FROM {taxonomy_term_data} WHERE tid = :tid", array(':tid' => $form_state['values']['tid']))->fetchField();

  $nid = tft_get_og_nid($form_state['values']['tid']);
  $og_tid = tft_get_og_tid($nid);
  $archive_tid = tft_get_archive_tid($og_tid);
  $parent_tid = db_query("SELECT parent FROM {taxonomy_term_hierarchy} WHERE tid = :tid", array(':tid' => $form_state['values']['tid']))->fetchField();

  db_update('taxonomy_term_hierarchy')->fields(array(
    'parent' => $archive_tid,
  ))->condition('tid', $form_state['values']['tid'])->execute();

  tft_log_archive($form_state['values']['tid'], 'term', $parent_tid, $nid);

  drupal_set_message(t("The <em>@term</em> folder was archived.", array('@term' => $name)));
}

/**
 * Archive a term form
 */
function tft_archive_file_form($form, $form_state, $nid) {
  // Check that a vocabulary is set for Taxonomy File Tree
  tft_check_vocabulary_setting();

  $node = node_load($nid);

  if (!node_access('update', $node)) {
    drupal_set_message(t("You cannot edit this file."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  if (empty($node->taxonomy)) {
    drupal_set_message(t("This file is not part of any tree. You cannot archive it."), 'error');

    if ($destination = str_replace('%23', '#', $_GET['destination'])) {
      drupal_goto($destination);
    }
    else {
      drupal_goto();
    }
  }

  drupal_set_title(t("Are you sure you want to archive file <em>@title</em> ?", array('@title' => $node->title)));

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => "Archiver",
  );

  $form['cancel'] = array(
    '#value' => '<a href="/' . str_replace('%23', '#', $_GET['destination']) . '">' . t("cancel") . '</a>',
  );

  return $form;
}

/**
 * Submission callback
 * @see tft_archive_term_form()
 */
function tft_archive_file_form_submit($form, $form_state) {
  $node = node_load($form_state['values']['nid']);

  // Get original folder.
  // Reconstruct list of terms by removing all folder terms.
  $taxonomy = array();
  foreach ($node->taxonomy as $term) {
    if ($term->vid != variable_get('tft_vocabulary_vid', 1)) {
      $taxonomy[] = $term->tid;
    }
    else {
      $tid = $term->tid;
    }
  }

  $og_nid = tft_get_og_nid($tid);

  $og_tid = tft_get_og_tid($og_nid);

  $archive_tid = tft_get_archive_tid($og_tid);

  $taxonomy[] = $archive_tid;

  $node->taxonomy = $taxonomy;

  node_save($node);

  tft_log_archive($node->nid, 'node', $tid, $og_nid);

  drupal_set_message(t("The <em>@title</em> file was archived.", array('@title' => $node->title)));
}
