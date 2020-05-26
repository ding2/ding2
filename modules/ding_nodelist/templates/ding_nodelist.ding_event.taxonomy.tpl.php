<?php

/**
 * @file
 * Template file for taxonomy-like layout.
 *
 * Available variables:
 *
 * $title
 *   Node title.
 * $body
 *   Node body teaser.
 * $image
 *   Node list image html tag.
 * $date
 *   Node date, created or published if set.
 * $author
 *   Node author name.
 */
?>

<?php if (isset($item->has_header)): ?>
  <div class="event-list-leaf">
    <div class="event-list-date-wrapper">
      <span class="event-list-day">
        <?php print format_date($item->timestamp, 'custom', 'D', $item->timezone); ?>
      </span>
      <div class="event-list-inner-wrapper">
        <span class="event-list-date">
          <?php print format_date($item->timestamp, 'custom', 'd', $item->timezone); ?>
        </span>
        <span class="event-list-month">
          <?php print format_date($item->timestamp, 'custom', 'M', $item->timezone); ?>
        </span>
      </div>
    </div>
  <span class="event-list-fulldate">
    <?php print format_date($item->timestamp, 'custom', 'l j. F Y', $item->timezone); ?>
  </span>
  </div>
<?php endif; ?>
<div class="item"<?php print $attributes; ?>>
  <?php if ($item->image): ?>
    <div class="item-list-image">
      <?php print $item->image_link; ?>
    </div>
  <?php endif ?>
  <div class="item-details">
    <h2 class="item-title"><?php print l($item->title, 'node/' . $item->nid); ?></h2>
    <span class="item-library"><?php print drupal_render($item->library_link); ?></span>
    <div class="date-time"><?php print $item->hours; ?></div>
    <span class="item-price"><?php print $item->price; ?></span>
    <div class="item-body">
      <span><?php print $item->teaser_lead; ?></span>
    </div>
    <div class="event-arrow-link">
      <?php print l('<i class="icon-chevron-right"></i>', 'node/' . $item->nid, array('html' => TRUE)); ?>
    </div>
  </div>
</div>
