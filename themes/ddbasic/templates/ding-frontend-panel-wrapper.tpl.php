<?php
/**
 * @file
 * Template for ding_frontend_panel_wrapper theme function.
 *
 * It's used to wrap non-panel pages in the right classes to get the right look.
 *
 * @param $variables
 *   An associative array containing:
 */
?>
<div class="empty-sidebars default-layout">
  <div class="layout-wrapper">
    <div class="pane-content">
      <div class="primary-content">
        <?php print $variables['element']['#children'] ?>
      </div>
    </div>
  </div>
</div>
