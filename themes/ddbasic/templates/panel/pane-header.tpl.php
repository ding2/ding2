<?php
/**
 * @TODO Missing comments
 */
?>
<div class="logo">
  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
    <div class="site-name-container<?php if ($logo): ?> logo-container<?php endif; ?>">
      <div class="site-name"><?php print $site_name; ?></div>
      <?php if ($logo): ?>
        <img src="<?php print $logo; ?>" />
        <span class="vertical-helper"></span>
      <?php endif; ?>
    </div>
  </a>
</div>

