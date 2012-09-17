<div class="header-inner">
  <?php if ($logo || $site_name || $site_slogan): ?>
    <?php if ($logo): ?>
      <div class="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      </div>
    <?php endif; ?>
    <?php if ($site_name || $site_slogan): ?>
      <?php if ($site_name): ?>
        <div class="site-name">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <?php print $site_name; ?>
          </a>
        </div>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div class="site-slogan">
          <?php print $site_slogan; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>
  <?php endif; ?>
</div>