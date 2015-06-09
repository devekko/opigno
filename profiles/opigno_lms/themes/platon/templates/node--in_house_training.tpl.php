<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>
  <div class="content"<?php print $content_attributes; ?>>
    <table class="training-stats-table">
      <thead>
      <tr>
        <th><?php print $title; ?></th>
        <th></th>
        <th></th>
        <th></th>
      </tr>
      </thead>
      <tbody>
      <tr>
        <td class="vertical-header">
          <?php print t($content['opigno_iht_comment']['#title']); ?>
        </td>
        <td class="second_td">
          <?php print $node->opigno_iht_comment['und'][0]['value']; ?>
        </td>
        <td class="img_map" rowspan="6">
          <?php print render(field_view_field('node', $node, 'opigno_iht_address', array(
            'type' => 'simple_gmap',
            'label' => 'hidden'
          ))); ?>

        </td>
        <td class="take-button-cell" rowspan="6">
          <?php
          $link = menu_get_item("node/{$node->nid}/edit");
          if (!empty($link) && $link['access'] && (!$page)) {
          print l(t("Read more"), "node/{$node->nid}", array(
            'attributes' => array(
              'class' => array(
                'read-more',
                'action-element',
                'action-sort-element'
              )
            )
          ));
          }
          $link = menu_get_item("node/{$node->nid}/edit");
          if (!empty($link) && $link['access']) {
            print l(t("Edit"), "node/{$node->nid}/edit", array(
              'attributes' => array(
                'class' => array(
                  'edit',
                  'action-element',
                  'action-edit-element'
                )
              )
            ));
          }
          $link = menu_get_item("node/{$node->nid}/score");
          if (!empty($link) && $link['access']) {
            print l(t("Results"), "node/{$node->nid}/score", array(
              'attributes' => array(
                'class' => array(
                  'results',
                  'action-element',
                  'action-results-element'
                )
              )
            ));
          }
          ?>
        </td>
      </tr>
      <?php if (isset($content['opigno_iht_status']['#title'])) { ?>
        <tr>
          <td class="vertical-header">
            <?php print t($content['opigno_iht_status']['#title']); ?>
          </td>
          <td class="second_td">
            <?php print t(render(field_view_field('node', $node, 'opigno_iht_status', array('label' => 'hidden')))); ?>
          </td>
        </tr>
      <?php } ?>
      <tr>
        <td class="vertical-header">
          <?php print t('Duration'); ?>
        </td>
        <td class="second_td">
          <?php
          $time = strtotime($node->opigno_calendar_date['und'][0]['value']);
          $time2 = strtotime($node->opigno_calendar_date['und'][0]['value2']);
          $diff = abs($time2 - $time);
          print gmdate('H \h i \m', $diff);
          ?>
        </td>
      </tr>
      <tr>
        <td class="vertical-header">
          <?php print t($content['opigno_iht_address']['#title']); ?>
        </td>
        <td class="second_td">
          <?php print $node->opigno_iht_address['und'][0]['value']; ?>
        </td>
      </tr>
      <tr>
        <td class="vertical-header">
          <?php print t('My Status'); ?>
        </td>
        <td class="second_td">
          <?php
          Global $user;
          $result = opigno_in_house_training_score_form_get_default_value($node->nid, $user->uid);
          if ($result['status'] == 1) {
            print t('Attended');
          }
          else {
            print t('Absent');
          }
          ?>
        </td>
      </tr>
      <tr>
        <td class="vertical-header">
          <?php print t('Score'); ?>
        </td>
        <td class="second_td">
          <?php print $result['score']; ?>
        </td>
      </tr>
      </tbody>
    </table>
  </div>
</div>