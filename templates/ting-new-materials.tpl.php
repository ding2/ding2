<?php
/**
 * @file
 * Default theme implementation for displaying ting new materials results.
 */
?>
<?php if ($title) : ?>
  <div class="new-materials-header">
    <div class="new-materials-title">
      <h1><?php print $title; ?></h1>
    </div>
    <?php if ($legend) : ?>
      <div class="ting-search-amount">
        <div class="ting-search-amount-block">
          <?php print $legend; ?>
        </div>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
<?php if ($results) : ?>
  <?php print drupal_render($results); ?>
<?php else : ?>
  <div class="no-results-this-period">
    <?php print t('There were no new materials in this period'); ?>
  </div>
<?php endif; ?>
