<?php
/**
 * @file
 * Defines the page header for the theme.
 */
?>
<?php if ($logo || $site_name || $site_slogan): ?>
  <?php if ($logo): ?>
    <div class="logo">
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
    </div>
  <?php endif; ?>
  <?php if ($site_name || $site_slogan): ?>
    <div class="site-name-wrapper">
      <?php if ($site_name): ?>
        <h1 class="site-name<?php if ($site_slogan) { print '-with-slogan'; } ?>">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <?php print $site_name; ?>
          </a>
        </h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div class="site-slogan">
          <?php print $site_slogan; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>
<?php endif; ?>
