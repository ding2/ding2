<?php
/**
 * @file
 * ddbasic implementation to present a Panels layout.
 *
 * Available variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 * - $css_id: unique id if present.
 */
?>
<div <?php if (!empty($css_id)) { print 'id="' . $css_id . '"'; } ?> class="default-panel-layout">
  <?php if(!empty($content['left_sidebar']) || !empty($content['main_content'])) : ?>
  <div class="left-and-main-content">
    <div class="layout-wrapper">
      <?php if (!empty($content['left_sidebar'])): ?>
        <aside class="secondary-content">
          <?php print $content['left_sidebar']; ?>
        </aside>
      <?php endif ?>
      <div class="primary-content">
        <?php print $content['main_content']; ?>
      </div>
    </div>
  </div>
  <?php endif; ?>
  <?php if (!empty($content['attachment_1_1'])): ?>
    <div class="attachments-wrapper attachments-1-1">
      <div class="attachment-first">
        <div class="grid-inner"><?php print $content['attachment_1_1']; ?></div>
      </div>
    </div>
  <?php endif ?>
</div>