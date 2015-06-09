<div id="apps-featured-panel" class="row">
  <div class="col col-2-out-of-2 col-4-out-of-4 col-6-out-of-6">
    <div class="apps-featured-panel-wrapper">
      <div class="app-featured-info">
        <div class="app-featured-label"><?php print t("Featured app"); ?>:</div>

        <h3 class="app-name"><?php print $name ?></h3>

        <?php print drupal_render($rating); ?>
      </div>
    </div>
  </div>
</div>
