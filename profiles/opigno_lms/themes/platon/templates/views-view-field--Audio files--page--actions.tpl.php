<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php
$path_view='node/'.$row->nid;
$link_view= menu_get_item($path_view);
if (!empty($link_view) && $link_view['access']) {
  print l(t("Start playing"), $path_view, array('attributes' => array('class' => 'action-element action-sort-element active')));
}
$path_edit='node/'.$row->nid.'/edit';
$link_edit = menu_get_item($path_edit);
if (!empty($link_edit) && $link_edit['access']) {
  print l(t("Edit"), $path_edit, array('attributes' => array('class' => 'edit action-element action-edit-element')));
}
?>