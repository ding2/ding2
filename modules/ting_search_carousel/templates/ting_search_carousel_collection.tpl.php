<?php
/**
 * @file
 *
 */
?>
<li class="rs-carousel-item">
  <a href="ting/collection/<?php print $collection->id; ?>" class="rs-carousel-item-image"><img src="<?php print $collection->image; ?>" alt=""/></a>
  <a href="ting/collection/<?php print $collection->id; ?>" class="rs-carousel-item-title"><?php print check_plain($collection->title); ?></a>
  <a href="ting/collection/<?php print $collection->id; ?>" class="rs-carousel-item-type"><?php print check_plain($collection->type); ?></a>
</li>
