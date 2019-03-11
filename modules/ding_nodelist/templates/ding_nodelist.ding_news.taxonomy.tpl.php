<?php

/**
 * @file
 * Template file for taxonomy-like layout.
 */
?>
<div class="item">
  <?php if ($item->image): ?>
    <div class="item-list-image">
      <?php print $item->image_link; ?>
    </div>
  <?php endif ?>
  <div class="item-details news">
    <h2 class="item-title"><?php print l($item->title, 'node/' . $item->nid); ?></h2>
    <div class="item-byline">
      <div class="label"><?php print drupal_render($item->category_link); ?></div>
      <div class="author"><?php print $item->author; ?></div>
    </div>
    <div class="item-body">
      <?php print $item->teaser_lead; ?>
    </div>
    <div class="news-link more-link">
      <?php print l(t('Read more'), 'node/' . $item->nid); ?>
    </div>
  </div>
</div>
