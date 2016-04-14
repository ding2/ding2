<?php
/**
 * Default template for gateway self registration information page.
 *
 * Available variables:
 *  - $title: Headline and page title.
 *  - $content: The content for the page.
 *  - $link: Link to login page.
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
      <div class="primary-content">
        <h2 class="pane-title"><?php print render($title); ?></h2>
        <?php print render($content); ?>
        <div class="ding-gatewayf--link-wrapper">
          <?php print render($link); ?>
        </div>
      </div>
    </div>
  </div>
</div>

