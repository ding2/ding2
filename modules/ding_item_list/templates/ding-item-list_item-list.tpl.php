<?php
/**
 * @file
 * Wrapper template for item list.
 */
?>
<div class="ding-item-list" <?php if (!empty($hash)): ?> data-hash="<?php print $hash; ?>"><?php endif; ?>
  <?php if (!empty($items)) : ?>
  <div class="ding-item-list-items">
    <?php foreach ($items as $item): ?>

      <div class="ding-item-list-item">
        <div class="item-cover">
          <a href="/ting/object/<?php print $item['faust']; ?>">
            <?php print render($item['cover']); ?>
          </a>
        </div>
        <div class="item-details">
          <div class="item-title"><a href="/ting/object/<?php print $item['faust']; ?>"><?php print $item['title']; ?></a></div>
          <div class="item-author">
            <?php if (!empty($item['author'])): ?>
              <?php print t('By @author', array('@author' => $item['author'])); ?>
              <?php if(!empty($item['year'])): ?>
                (<?php print $item['year'];?>)
              <?php endif; ?>
            <?php endif; ?>
          </div>
          <?php if ($item['has_rating']): ?>
            <div class="item-rating">
              <div class="rating-value-<?php print $item['rating']; ?>"><?php print $item['rating']; ?></div>
              <span class="rating-count">(<?php print $item['rating_count']; ?>)</span>
            </div>
            <div class="item-reviews">(<?php print $item['review_count'];?>) <?php print t('reviews'); ?></div>
          <?php endif; ?>
          <div class="item-loan"><?php print drupal_render($item['loan_form']); ?></div>
        </div>
      </div>
    <?php endforeach; ?>
  </div>
  <?php endif; ?>
</div>
