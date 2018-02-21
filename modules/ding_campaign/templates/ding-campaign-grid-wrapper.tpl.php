<?php
/**
 * @file
 * Default template for grid image campaigns.
 *
 * Variables:
 *  $content - contains an array of campaign items.
 *  $more_link - contain rendered link.
 */
?>
<div class="ding-campaign-grid-wrapper">
  <?php foreach ($content as $campaign) : ?>
    <?php print $campaign; ?>
  <?php endforeach; ?>

  <?php if (!empty($more_link)): ?>
      <div class="more-link">
        <?php print $more_link; ?>
      </div>
  <?php endif; ?>
</div>
