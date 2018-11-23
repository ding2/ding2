<?php
/**
 * @file
 * Default theme implementation for displaying ting search results.
 *
 * We need a custom template because we need a special pager.
 *
 * @see template_preprocess_ting_search_results()
 */
?>
<?php if ($search_results) : ?>
  <div class="search-results">
    <h2><?php print t('Search results');?></h2>
    <ol class="search-results <?php print $module; ?>-results">
      <?php print $search_results; ?>
    </ol>

    <?php if (isset($search_results_count)): ?>
      <?php print $search_results_count; ?>
    <?php endif ?>

    <?php print $pager; ?>
  </div>
<?php else : ?>
  <div class="search-results">
    <h2><?php print t('Your search yielded no results');?></h2>
    <?php print search_help('search#noresults', drupal_help_arg()); ?>
  </div>
<?php endif; ?>
