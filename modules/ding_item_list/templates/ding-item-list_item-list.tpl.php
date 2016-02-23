<?php
/**
 * @file
 * Wrapper template for item list.
 */
?>
<div class="ding-item-list">
  <?php if (!empty($items)) : ?>
  <div class="ding-item-list-items">
    <?php print $items; ?>
  </div>
  <?php ;endif ?>
</div>
