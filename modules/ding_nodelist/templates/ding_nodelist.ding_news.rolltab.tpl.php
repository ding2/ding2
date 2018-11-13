<?php

/**
 * @file
 * Template file for ding_news rolltab layout.
 */
?>
<div class="ding-tabroll">
  <div class="ui-tabs-panel">
    <div class="image">
      <?php if (!$item->image): ?>
        <span class="no-image"></span>
      <?php else: ?>
        <?php print $item->image_link; ?>
      <?php endif; ?>
    </div>

    <div class="info">
      <h3><?php print l($item->title, 'node/' . $item->nid); ?></h3>
      <p> <?php print $item->teaser_lead; ?>
      </p>
    </div>
  </div>
</div>
