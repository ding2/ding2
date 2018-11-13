<?php

/**
 * @file
 * Ding news node blocks template.
 */

?>

<article data-row="<?php print $row; ?>" data-column="<?php print $column; ?>"
    class="node node-ding-news node-promoted node-teaser nb-item <?php print $item->image ? 'has-image' : ''; ?>">
  <a href="<?php print '/node/' . $item->nid; ?>">
    <div class="inner">
      <div class="background">
        <div class="button"><?php print t('Read more'); ?></div>
      </div>
      <div class="text news-text">
        <div class="info-top">
          <?php print drupal_render($item->category); ?>
        </div>
        <div class="title-and-lead">
          <h3 class="title"><?php print $item->title; ?></h3>
          <div
             class="field field-name-field-ding-news-lead field-type-text-long field-label-hidden">
            <div class="field-items">
              <div class="field-item">
                <?php print $item->teaser_lead; ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
      <?php if (!empty($item->image)): ?>
          <div class="ding-news-list-image nb-image" style="background-image:url(<?php print $item->image; ?>);"></div>
      <?php endif; ?>
  </a>
</article>
