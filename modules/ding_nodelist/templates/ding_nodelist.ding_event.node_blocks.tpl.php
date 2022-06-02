<?php
/**
 * @file
 * Ding event node blocks template.
 */

?>

<article data-row="<?php print $row; ?>" data-column="<?php print $column; ?>"
         class="node node-ding-event node-promoted nb-item <?php print $item->image ? 'has-image' : ''; ?>" aria-labelledby="<?php print 'link-id-' . $item->nid; ?>"<?php print $attributes; ?>>
  <a href="<?php print '/node/' . $item->nid; ?>" aria-labelledby="<?php print 'link-id-' . $item->nid; ?>">
    <div class="inner">
      <div class="background">
        <div class="button"><?php print t('Read more'); ?></div>
      </div>
      <div class="text event-text">
        <div class="info-top">
          <?php print drupal_render($item->category); ?>
        </div>
        <div class="date"><?php print $item->date; ?></div>
        <div class="title-and-lead">
          <h3 class="title" id="<?php print 'link-id-' . $item->nid; ?>"><?php print $item->title; ?></h3>
          <div
                  class="field field-name-field-ding-event-lead field-type-text-long field-label-hidden element-hidden">
            <div class="field-items">
              <div class="field-item">
                <?php print $item->teaser_lead; ?>
              </div>
            </div>
          </div>
        </div>
        <div class="info-bottom">
          <div class="library">
            <?php print drupal_render($item->library); ?>
          </div>
          <div class="date-time"><?php print $item->hours; ?></div>
          <div class="price"><?php print $item->price; ?></div>
        </div>
      </div>
    </div>
    <?php if (!empty($item->image)): ?>
      <div class="event-list-image nb-image" style="background-image:url(<?php print $item->image; ?>);"></div>
    <?php endif; ?>
  </a>
</article>
