<?php
/**
 * @file
 *
 */
?>
<li class="rs-carousel-item">
  <a href="ting/collection/<?php echo $collection->id; ?>" class="rs-carousel-item-image"><img src="<?php echo $collection->image; ?>" alt=""/></a>
  <a href="ting/collection/<?php echo $collection->id; ?>" class="rs-carousel-item-title"><?php print check_plain($collection->title); ?></a>
</li>
