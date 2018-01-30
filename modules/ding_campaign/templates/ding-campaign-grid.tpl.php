<?php
/**
 * @file
 * Default template for grid image campaign item.
 *
 * Variables:
 *  $image
 *  $title
 *  $description
 */
?>
<div class="ding-campaign-grid-item">
  <div class="campaign-info">
    <div class="ding-campaign-grid-image"><?php print $image; ?>
      <?php if (isset($description)): ?>
        <div class="ding-campaign-grid-description"><?php print $description; ?></div>
      <?php endif; ?>
    </div>
  </div>
  <h2 class="ding-campaign-grid-title"><?php print $title; ?></h2>
</div>
