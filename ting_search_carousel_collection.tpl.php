<?php
/**
 * @file
 *
 */
?>
<li class="rs-carousel-item">
  <a href="ting/collection/<?php echo $collection->id; ?>" title="<?php print check_plain($collection->creator); ?>: <?php print check_plain($collection->title); ?>">
    <img src="<?php echo $collection->image; ?>" alt=""/>
    <div class="info">
      <span class="creator"><?php print check_plain($collection->creator); ?></span>
      <span class="title"><?php print check_plain($collection->title); ?></span>
    </div>
  </a>
</li>
