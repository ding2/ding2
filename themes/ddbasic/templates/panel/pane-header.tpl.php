<?php

/**
 * @file
 * Theme implementation to display the header block on a Drupal page.
 *
 * This utilizes the following variables thata re normally found in
 * page.tpl.php:
 * - $logo
 * - $front_page
 * - $site_name
 * - $front_page
 * - $site_slogan
 * - $search_box.
 *
 * Additional items can be added via theme_preprocess_pane_header(). See
 * template_preprocess_pane_header() for examples.
 */
?>
<div class="site-header-site-name <?php print $classes; ?>">
  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
    <div class="site-header-site-name-inner<?php if ($logo): ?> site-header-site-name-logo-container<?php endif; ?>">
      <div class="site-header-site-name-container"><?php print $site_name; ?></div>
      <?php if ($logo): ?>
        <img src="<?php print $logo; ?>" />
        <span class="vertical-helper vertical-helper-tablet-and-above"></span>
      <?php endif; ?>
    </div>
  </a>
</div>
