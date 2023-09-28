<?php

/**
 * @file
 * Template file for taxonomy-like layout.
 */
?>
<div class="item">
  <?php if ($item->image): ?>
    <div class="item-list-image">
      <?php print $item->image_link; ?>
    </div>
  <?php endif ?>
  <div class="item-details">
    <h2 class="item-title"><?php print l($item->title, 'node/' . $item->nid); ?></h2>
    <div class="item-body">
      <?php print $item->teaser_lead; ?>
    </div>
  </div>
</div>
