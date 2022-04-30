<?php

/**
 * @file
 * Ding news node blocks template.
 *
 * @var object $item
 * @var string $column
 */

$image = '';
if (!empty($item->image)) {
  $image = '<div class="ding-news-list-image nb-image" style="background-image:url(' . $item->image . ');"></div>';
}
?>
<article data-row="<?php print $row; ?>" data-column=" <?php print $column; ?>"
         class="node node-ding-news node-promoted nb-item <?php print $item->image ? 'has-image' : ''; ?>" aria-labelledby="<?php print 'link-id-' . $item->nid; ?>"<?php print $attributes; ?>>
  <a href="<?php print '/node/' . $item->nid; ?>" aria-labelledby="<?php print 'link-id-' . $item->nid; ?>">
    <div class="inner">
      <div class="background">
        <div class="button"><?php print t('Read more'); ?></div>
      </div>
      <div class="text news-text">
        <div class="info-top">
          <?php print drupal_render($item->category); ?>
        </div>
        <div class="title-and-lead">
          <h3 class="title" id="<?php print 'link-id-' . $item->nid; ?>"><?php print $item->title; ?></h3>
          <div class="date"><?php print $item->date; ?></div>
          <div
                  class="field field-name-field-ding-news-lead field-type-text-long field-label-hidden element-hidden">
            <div class="field-items">
              <div class="field-item">
                <?php print $item->teaser_lead; ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <?php print $image; ?>
  </a>
</article>
