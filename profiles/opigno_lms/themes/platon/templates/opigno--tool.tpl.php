<?php
/**
 * @file
 * Tool template file. Renders the tool on the tools page.
 * Available variables:
 *  - $machine_name (filtered)
 *  - $name (filtered)
 *  - $path (escaped)
 *  - $description (escaped)
 *  - $tool (array containing any information the tool module defines. Unfiltered).
 */
?>
<div class="opigno-tool opigno-<?php print str_replace('_', '-', $machine_name); ?>-tool opigno-tool-block col col-1-out-of-2 col-2-out-of-4 col-2-out-of-6">
  <div class="opigno-tool-icon">
    <h4 class="opigno-tool-name">
      <?php if (!empty($path)): ?>
        <?php print l($name, $path, array('attributes' => array('class' => array('opigno-tool-link')))); ?>
      <?php else: ?>
        <?php print $name; ?>
      <?php endif; ?>
    </h4>
  </div>
  <p class="opigno-tool-description"><?php print $description; ?></p>
</div>