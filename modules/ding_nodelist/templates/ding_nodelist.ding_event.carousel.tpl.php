<?php

/**
 * @file
 * Ding event image and text template.
 */
?>
<div class="item">
  <?php if (!empty($item->image)): ?>
    <div class="event-image" style="background-image:url(<?php print $item->image; ?>);"></div>
  <?php endif; ?>
  <div class="event-time">
    <div class="event-day"><?php print format_date($item->timestamp, 'custom', 'D', $item->timezone); ?></div>
    <div class="event-date"><?php print format_date($item->timestamp, 'custom', 'd', $item->timezone); ?></div>
    <div class="event-month"><?php print format_date($item->timestamp, 'custom', 'M', $item->timezone); ?></div>
  </div>
  <div class="article-info">
    <div class="label"><?php print drupal_render($item->category_link); ?></div>
    <div class="node">
      <h3 class="node-title"><?php print l($item->title, 'node/' . $item->nid); ?></h3>
      <div class="item-date"><?php print drupal_render($item->formated_date); ?></div>
      <div>
        <span class="library"><?php print drupal_render($item->library_link); ?></span>
        <span class="item-price"><?php print '&mdash; ' . $item->price; ?></span>
      </div>
      <p><?php print $item->teaser_lead; ?></p>
      <div class="more">
        <?php print l(t('More'), 'node/' . $item->nid);?>
      </div>
    </div>
  </div>
</div>
