<?php

/**
 * @file
 * Defines all page callbacks.
 */

function opigno_sort_groups_form($form, $form_state,$nid) {
  $form['table'] = array(
    '#tree' => TRUE,
  );

  $node=node_load($nid);

  $form['cgid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );

  foreach (opigno_sort_group_courses($node) as $coursenid)
  {
    $coursenode=node_load($coursenid);
    $form['table']["course_{$coursenid}"]['nid'] = array(
      '#type' => 'hidden',
      '#value' => $coursenid,
    );
    $form['table']["course_{$coursenid}"]['title'] = array(
      '#markup' => check_plain($coursenode->title),
    );
    $form['table']["course_{$coursenid}"]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 50,
      '#default_value' => opigno_sort_groups_get_groups_weight($node->nid,$coursenid),
      '#attributes' => array('class' => array('opigno-sort-course-weight')),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save order"),
  );

  return $form;
}

function opigno_sort_groups_form_submit($form, $form_state) {
  foreach ($form_state['values']['table'] as $values) {
    opigno_sort_groups_set_groups_weight($form_state['values']['cgid'], $values['nid'], $values['weight']);
  }
}
