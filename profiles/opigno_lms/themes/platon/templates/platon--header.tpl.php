<header id="site-header"<?php print $site_header_attributes; ?>>
  <div class="row">
    <div class="col col-1-out-of-2 col-1-out-of-4 col-1-out-of-6">
      <?php if (!empty($logo)): ?>
        <a href="<?php print $front_page; ?>" id="logo"><img src="<?php print $logo; ?>" alt="Opigno"></a>
      <?php endif; ?>
    </div>

    <div class="col col-1-out-of-2 col-3-out-of-4 col-5-out-of-6">
      <?php if (!empty($search_form)): ?>
        <a href="<?php print url('search/node'); ?>" class="mobile-link-icon">
          <img src="<?php print $base_path . $directory; ?>/img/search-submit.png">
        </a>

        <a href="#top" id="menu-toggle-link" class="mobile-link-icon">
          <img src="<?php print $base_path . $directory; ?>/img/menu-toggle-icon.png">
        </a>

        <?php if ($logged_in): ?>
          <a href="<?php print url('user/logout'); ?>" class="mobile-link-icon">
            <img src="<?php print $base_path . $directory; ?>/img/logout-icon.png">
          </a>
        <?php endif; ?>

        <div id="header-search">
          <?php print render($search_form); ?>
        </div>
      <?php endif; ?>

      <div id="user-account-information">
        <div id="user-account-information-picture">
          <a href="<?php print url('user'); ?>">
            <img src="<?php print $base_path . $directory; ?>/img/anonymous-account.png">
          </a>
        </div>

        <div id="user-account-information-name">
          <?php print t("welcome @user", array('@user' => $logged_in ? $user->name : t("guest"))); ?>

          <div id="user-account-information-links">
            <?php if ($logged_in): ?>
              <?php print l(t("my account"), 'user'); ?> | <?php print l(t("logout"), 'user/logout'); ?>
            <?php else: ?>
              <?php if ($can_register): ?>
                <?php print l(t("register"), 'user/register'); ?> |
              <?php endif; ?>
              <?php print l(t("login"), 'user/login'); ?>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
</header>
