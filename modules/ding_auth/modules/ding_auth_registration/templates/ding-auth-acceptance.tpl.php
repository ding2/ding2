<?php
/**
 * Default template for user self registration acceptance page.
 *
 * Note: The page have pane classes to make it look correct in DDB default theme
 *       this is not optimal, but the only other solution would be to use
 *       exiting_pages module to convert this to an panel page (but it seams
 *       faster for performance and easier to just use the classes).
 */
?>
<div class="empty-sidebars default-layout">
  <div class="layout-wrapper">
    <div class="pane-content">
      <div class="primary-content ding-auth">
        <h2 class="pane-title"><?php print t('Self registration form'); ?></h2>
        <div class="ding-auth--registration-acceptance">
          <?php print $variables['element']['#children'] ?>
        </div>
      </div>
    </div>
  </div>
</div>

