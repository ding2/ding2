<?php

/**
 * @file
 * Ding news image and text template.
 */

?>
<div class="item">
  <div class="article_image">
    <?php print $item->image_link; ?>
  </div>
  <div class="article-info">
    <div class="label-wrapper"><?php print drupal_render($item->category_link); ?></div>
    <div class="node">
      <h3 class="node-title">
        <?php print l($item->title, 'node/' . $item->nid); ?>
      </h3>
      <p>
        <?php print $item->teaser_lead; ?>
      </p>
      <div class="more">
        <?php print l(t('More'), 'node/' . $item->nid); ?>
      </div>
    </div>
  </div>
</div>
