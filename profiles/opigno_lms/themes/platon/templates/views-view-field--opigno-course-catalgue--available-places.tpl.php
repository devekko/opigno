<?php
$node=node_load($row->nid);
$info=opigno_course_quota_app_students_info($node);
if ((isset($info['places']))&&($info['places']!=-1))
{
 print $info['available_places'];
}
?>