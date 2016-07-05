<?php
/**
 * @file
 *
 */
?>
<li class="carousel-item">
  <a href="/ting/collection/<?php print $collection->id; ?>" class="carousel-item-image"><img src="<?php print $collection->image; ?>" alt=""/></a>
  <a href="/ting/collection/<?php print $collection->id; ?>" class="carousel-item-title"><?php print check_plain($collection->title); ?></a>
</li>
