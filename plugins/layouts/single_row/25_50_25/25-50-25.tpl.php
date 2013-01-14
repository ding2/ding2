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
<div <?php if (!empty($css_id)) { print " id=\"$css_id\""; } ?> class="panel-content-wrapper">
  <div class="primary-content">
    <div class="grid-inner"><?php print $content['main_content']; ?></div>
  </div>
  <?php if (!empty($content['left_sidebar'])): ?>
    <aside class="secondary-content">
      <div class="grid-inner"><?php print $content['left_content']; ?></div>
    </aside>
  <?php endif ?>
  <?php if (!empty($content['right_sidebar'])): ?>
    <aside class="tertiary-sidebar">
      <div class="grid-inner"><?php print $content['right_sidebar']; ?></div>
    </aside>
  <?php endif ?>
</div>