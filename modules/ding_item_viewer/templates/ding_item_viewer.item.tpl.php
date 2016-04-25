<?php
/**
 * @file
 * Template for ding item viewer item.
 *
 * Variables:
 *   $item - Object containing item info.
 *   $item_class - Additional classes for item wrapper.
 */

// Hide VoxB on item using CSS when this item does not have ISBN.
// The structure is needed for other items.
$voxb_class = ' hidden';
if ($item->has_rating):
  $voxb_class = '';
endif;
?>
<div class="browsebar-item <?php echo $item_class; ?>">
  <div class="image-rating-wrapper">
    <img src="<?php echo $item->image; ?>" class="image"
      alt="<?php echo $item->title . ' ' . $item->year; ?>" />
    <div class="rating rating-0<?php echo $voxb_class; ?>"></div>
  </div>
  <span class="title"><?php echo $item->title; ?></span>
  <?php if (!empty($item->creator)): ?>
    <span class="author"><?php echo $item->creator; ?></span>
  <?php endif; ?>
  <span class="more-info"><?php print t('More info'); ?></span>
</div>
