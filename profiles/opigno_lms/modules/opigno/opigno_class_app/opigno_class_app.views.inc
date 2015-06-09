<?php

function opigno_class_app_views_pre_render(&$view) {
  Global $user;
  if ($view->name == "opigno_my_courses") {
    $query = opigno_class_app_get_my_classes($user->uid);
    $result = $query->execute();
    $records = $result->fetchAll();
    foreach ($view->result as $index1 => &$display_item) {
      $im_in_group = FALSE;
      foreach ($records as $index2 => $record) {
        if ($record->nid == $display_item->opigno_class_courses_node_nid) {
          $im_in_group = TRUE;
        }
      }
      if ($im_in_group == FALSE) {
        $display_item->opigno_class_courses_node_title = NULL;
        $display_item->opigno_class_courses_node_nid = NULL;
        if (opigno_class_app_course_already_listed($view->result, $index1, $display_item->node_og_membership_nid)) {
          unset($view->result[$index1]);
        }
      }
    }
  }
  if ($view->name == "opigno_course_catalgue") {
    $private_classes = opigno_class_app_get_private_classes_for_user($user);
    foreach ($view->result as $index => &$object) {
      if (in_array($object->opigno_class_courses_node_nid, $private_classes)) {
        if (isset($object->opigno_sort_groups_weight)) {
          $object->opigno_sort_groups_weight = 99;
        }
        if (isset($object->field_group_group_1)) {
          $object->field_group_group_1 = NULL;
        }
        if (isset($object->opigno_class_courses_node_title)) {
          $object->opigno_class_courses_node_title = NULL;
        }
        if (isset($object->opigno_class_courses_node_nid)) {
          $object->opigno_class_courses_node_nid = NULL;
        }
        if (opigno_class_app_course_already_listed_catalogue($view->result, $object->nid, $index)) {
          unset($view->result[$index]);
        }
      }
    }
    if (module_exists("opigno_sort_groups")) {
      usort($view->result, "opigno_class_app_sort_by_weight");
    }
  }
}

function opigno_class_app_sort_by_weight($a,$b)
{
  return ($a->opigno_sort_groups_weight>$b->opigno_sort_groups_weight);
}

function opigno_class_app_course_already_listed($results, $index, $node_og_membership_nid) {
  $already_exists = FALSE;
  foreach ($results as $index1 => $display_item) {
    if (($index1 != $index) && ($display_item->node_og_membership_nid == $node_og_membership_nid) && (($display_item->opigno_class_courses_node_nid == NULL) || ($results['index']->opigno_class_courses_node_nid == NULL))) {
      $already_exists = TRUE;
    }
  }
  return $already_exists;
}

function opigno_class_app_course_already_listed_catalogue($results,$id,$index)
{
  Global $user;
  foreach($results as $index_ => $object)
  {
    if (($object->nid==$id)&&(($object->opigno_class_courses_node_nid==NULL)||(!in_array($object->opigno_class_courses_node_nid,opigno_class_app_get_private_classes_for_user($user))))&&($index!=$index_))
    {
      return true;
    }
  }
  return false;
}

function opigno_class_app_get_my_classes($userid) {
  $query = db_select('og_membership', 'og');
  $query->condition('og.state', '1', '=');
  $query->condition('og.group_type', 'node', '=');
  $query->condition('og.entity_type', 'user', '=');
  $query->condition('og.etid', $userid, '=');
  $query->join('node', 'n', 'n.nid = og.gid');
  $query->condition('n.type', 'class', '=');
  $query->addField('n', 'nid', 'nid');
  return $query;
}

function opigno_class_app_get_private_classes_for_user($user)
{
  $classes=array('0'=>0);
  $result = db_select('node', 'n')
    ->fields('n')
    ->condition('n.type',"class",'=')
    ->execute();
  while($record = $result->fetchAssoc())
  {
    $node=node_load($record['nid']);
    if (!node_access("view",$node,$user))
    {
      $classes[$node->nid]=$node->nid;
    }
  }
  return $classes;
}
