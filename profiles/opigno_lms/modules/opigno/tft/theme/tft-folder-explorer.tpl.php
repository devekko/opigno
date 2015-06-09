<div id="folder-explorer-container">
  <?php if($folders): ?>
    <?php print $folders; ?>
  <?php else: ?>
    <div class="messages notice">
      <?php print t('You must first <a href="!link">create some taxonomy terms</a> before you can see any folders.', array('!link' => url('admin/content/taxonomy/' . variable_get('tft_vocabulary_vid', 0)))); ?>
    </div>
  <?php endif; ?>
</div>