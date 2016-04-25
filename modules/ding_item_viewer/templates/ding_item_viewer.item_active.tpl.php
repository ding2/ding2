<?php
/**
 * @file
 * Template for ding item viewer item.
 *
 * Variables:
 *   $item - Object containing item info.
 */

// Hide VoxB on active item using CSS when this item does not have ISBN.
// The structure is needed for other items.
$voxb_class = ' hidden';
if ($item->has_rating):
  $voxb_class = '';
endif;
?>
<div class="browsebar-item active">
  <div class="active-item-title">
    <h2>
      <a href="<?php echo url('ting/object/' . $item->id); ?>" class="active-title active-more-info"><?php echo $item->title; ?></a>
    </h2>
  </div>
  <div class="cover-wrapper">
    <div class="cover-wrapper-inner">
      <img src="<?php echo $item->image; ?>" class="image"
        alt="<?php echo $item->title . ' ' . $item->year; ?>" />
    </div>
  </div>
  <div class="properties-wrapper">
    <?php if (!empty($item->creator)): ?>
      <span class="active-author"><?php echo $item->creator; ?></span>
    <?php endif; ?>
    <span class="active-description"><?php echo $item->description; ?></span>
    <span class="genre"><?php print t('Genre'); ?>:
      <a href="<?php echo url('search/ting/' . $item->subject); ?>"><?php echo $item->subject; ?></a>
    </span>
    <div class="active-rating rating-<?php echo $item->rating . $voxb_class; ?>"></div>
    <span class="rating-count<?php echo $voxb_class; ?>">(<?php echo $item->rating_count;?>)</span>
    <a href="#" class="reviews<?php echo $voxb_class; ?>">
      <?php print t('Reviews'); ?><span class="review-count">(<?php echo $item->comment_count; ?>)</span>
    </a>
    <a href="<?php echo url('ting/object/' . $item->id); ?>" class="active-more-info"><?php print t('More info'); ?></a>
    <div class="reserve-container">
      <div class="item-loan">
        <?php print l(
          t('Reserve'),
          'reservation/reserve/' . $item->localId,
          array('attributes' => array('id' => 'reserve-' . $item->localId))
          );
        ?>
      </div>
    </div>
  </div>
</div>
