<div id="first-sidebar" class="col col-2-out-of-2 col-1-out-of-4 col-1-out-of-6">
  <?php if (!empty($main_navigation) && ($logged_in || theme_get_setting('platon_menu_show_for_anonymous')) && theme_get_setting('toggle_main_menu')): ?>
    <div id="main-navigation-wrapper">
      <?php print $main_navigation; ?>
    </div>
  <?php endif; ?>

  <?php print render($page['sidebar_first']); ?>
</div>
