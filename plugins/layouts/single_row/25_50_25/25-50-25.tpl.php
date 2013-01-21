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

/**
 * Add a css class based on wich sidebars have content
 */

// No sidebars
if (empty($content['left_sidebar']) && empty($content['right_sidebar'])) {
  $add_class = 'no-sidebars';
}
// Only tertiary content (right sidebar)
else if (empty($content['left_sidebar']) && !empty($content['right_sidebar'])) {
  $add_class = 'right-sidebar';
}
// Only secondary content (left sidebar)
else if (!empty($content['left_sidebar']) && empty($content['right_sidebar'])) {
  $add_class = 'left-sidebar';
}
// Both secondary and tertiary content (left and right sidebars)
else if (!empty($content['left_sidebar']) && !empty($content['right_sidebar'])) {
  $add_class = 'sidebars';
}
?>
<div <?php if (!empty($css_id)) { print " id=\"$css_id\""; } ?> class="<?php echo $add_class; ?> panel-content-wrapper">
  <div class="primary-content">
    <div class="grid-inner"><?php print $content['main_content']; ?></div>
  </div>
  <?php if (!empty($content['left_sidebar'])): ?>
    <aside class="secondary-content">
      <div class="grid-inner"><?php print $content['left_sidebar']; ?></div>
    </aside>
  <?php endif ?>
  <?php if (!empty($content['right_sidebar'])): ?>
    <aside class="tertiary-content">
      <div class="grid-inner"><?php print $content['right_sidebar']; ?></div>
    </aside>
  <?php endif ?>
</div>