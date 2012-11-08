<?php
/**
 * @file
 * DDBasic theme implementation to display ding footer.
 *
 * Available variables:
 * - $blocks: xxx.
 * - $clases: xxx.
 */
?>
<div class="ding-footer-wrapper">
  <?php foreach($blocks as $bid => $block) { ?>
  <div class="<?php echo $grid_classes[$bid]; ?>">
      <?php echo $block; ?>
  </div>
  <?php } ?>
</div>
