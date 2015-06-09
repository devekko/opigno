<div class="app-teaser-wrapper clearfix">
  <h2 class="app-name"><?php print $name ?></h2>

  <div class="app-teaser">
    <?php if ($logo): ?>
      <div class="app-logo">
        <?php print $logo ?>
      </div>
    <?php endif; ?>

    <div class="app-info">
      <div class="app-status"><?php print $status ?></div>
      <?php print drupal_render($rating); ?>
    </div>
  </div>

  <div class="app-action"><?php print $action; ?></div>
</div>
