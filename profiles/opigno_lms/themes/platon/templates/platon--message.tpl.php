<div class="messages <?php print $type; ?>">
  <span class="messages-dismiss">x</span>

  <?php if (!empty($heading)): ?>
    <h2 class="element-invisible"><?php print $heading; ?></h2>
  <?php endif; ?>

  <?php if (count($messages) > 1): ?>
    <ul>
      <?php foreach ($messages as $message): ?>
      <li><?php print $message; ?></li>
      <?php endforeach; ?>
    </ul>
  <?php elseif (!empty($messages)): ?>
    <?php print $messages[0]; ?>
  <?php endif; ?>
</div>
