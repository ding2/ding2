<?php

/**
 * @file
 * Ding news horizontal accordion template.
 */
?>
<li class="item news">
  <div class="item_content">
    <div class="expand"><?php print l($item->title, 'node/' . $item->nid);?></div>
    <div class="label"><?php print drupal_render($item->category_link); ?></div>
    <?php if (!empty($item->image)): ?>
      <div class="image"><?php print print $item->image_link; ?></div>
    <?php endif; ?>
    <div class="data">
      <div class="caption">
        <h3 class="node-title">
          <?php print l($item->title, 'node/' . $item->nid);?>
        </h3>
        <div class="category">
          <?php print drupal_render($item->category_link); ?>
        </div>
        <div class="teaser"><p><?php print $item->teaser_lead; ?></p></div>
      </div>
    </div>
  </div>
</li>
