<?php

/**
 * @file
 * Ding event horizontal accordion template.
 */
?>
<li class="event item">
  <div class="item_content">
    <div class="expand"><?php print l($item->title, 'node/' . $item->nid);?></div>
    <div class="event-time">
      <div class="event-day"><?php print format_date($item->timestamp, 'custom', 'D', $item->timezone); ?></div>
      <div class="event-date"><?php print format_date($item->timestamp, 'custom', 'd', $item->timezone); ?></div>
      <div class="event-month"><?php print format_date($item->timestamp, 'custom', 'M', $item->timezone); ?></div>
    </div>
    <?php if (!empty($item->image)): ?>
      <div class="image">
        <?php print print $item->image_link; ?>
      </div>
    <?php endif; ?>
    <div class="data">
      <div class="caption">
        <h3 class="node-title">
          <?php print l($item->title, 'node/' . $item->nid);?>
        </h3>
      </div>
      <div class="library">
        <div class="event-timestamp">
          <span><?php print t('Time:');?></span>
          <span><?php print $item->hours; ?></span>
        </div>
        <div class="event-details">
          <span class="event-library">
            <?php print drupal_render($item->library_link); ?>
          </span>
          <span class="event-fee"><?php print $item->price; ?></span>
        </div>
      </div>
      <div class="teaser"><p><?php print $item->teaser_lead; ?></p></div>
    </div>
  </div>
</li>
