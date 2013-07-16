<?php
/**
 * @file
 * Default theme implementation for displaying ting new materials results.
 *
 */
?>
<?php if ($title) : ?>
  <div class="new-materials-header">
    <h2><?php print $title; ?></h2>
    <?php if ($legend) : ?>
      <div class="ting-search-amount-block">
        <?php print $legend; ?>
      </div>
    <?php endif; ?>
  </div>
<?php endif; ?>
<?php if ($results['results']) : ?>
  <?php print drupal_render($results); ?>
<?php else : ?>
  <div class="no-results-this-period">
    <?php print t('There were no new materials in this period'); ?>
  </div>
<?php endif; ?>

