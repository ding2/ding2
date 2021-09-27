<?php

/**
 * @file
 * Ding event slider template.
 */
?>
<li class="item"<?php print $attributes; ?>>
  <h3 class="node-title">
      <?php print l($item->title, 'node/' . $item->nid); ?>
  </h3>
  <div class="category">
    <span class="label label-info"><?php print drupal_render($item->category_link);?></span>
  </div>
  <div class="node">
    <div class="item-date">
      <?php print $item->formated_date; ?>
    </div>
    <div class="event-details">
      <span class="library"><?php print drupal_render($item->library_link); ?></span>
      <span class="item-price"><?php print '&mdash; ' . $item->price; ?></span>
    </div>
    <div class="item-body"><?php print $item->teaser_lead; ?></div>
  </div>
  <div class="more"><?php print l(t('More'), 'node/' . $item->nid);?></div>
</li>
