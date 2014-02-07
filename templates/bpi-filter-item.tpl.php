<?php
/**
 * @file
 * Single filter item template.
 */
?>
<div class="bpi-filter bpi-filter-<?php echo $filter['name'];?>">
  <p class="bpi-filter-item">
    <span class="bpi-filter-label"><?php echo $filter['label'] ?>: </span>
    <span class="bpi-filter-value"><?php echo $filter['link'] ?></span>
    <span class="bpi-filter-remove"><?php echo $filter['remove']; ?></span>
  </p>
</div>
