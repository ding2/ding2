<?php
/**
 * @file
 * Default implementation of the ding filter in-place-editor for panels.
 *
 * Available variables:
 *  - $links:
 *  - $selections:
 */
?>
<div class="panels-ipe-newblock panels-ipe-on">
  <?php echo drupal_render($links) ?>
</div>
<div id="ipe-add-<?php echo $region_id ?>" class="panels-ipe-newblock ipe-popup element-hidden">
  <?php echo drupal_render($selections) ?>
</div>

