<?php

/**
 * @file
 * Default theme implementation for displaying ting new materials results.
 */
?>
<?php if ($results) : ?>
  <?php print drupal_render($results); ?>
<?php else : ?>
  <div class="no-results-this-period">
    <?php print t('There were no new materials in this period'); ?>
  </div>
<?php endif; ?>
