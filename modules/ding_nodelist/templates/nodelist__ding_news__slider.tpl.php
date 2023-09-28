<?php

/**
 * @file
 * Ding news slider template.
 */
?>
<li class="item">
  <div class="category">
    <?php print drupal_render($item->category_link);?>
  </div>
  <h3 class="node-title">
      <?php print l($item->title, 'node/' . $item->nid); ?>
  </h3>
  <div class="node"><?php print $item->teaser_lead; ?></div>
  <div class="more"><?php print l(t('More'), 'node/' . $item->nid);?></div>
</li>
