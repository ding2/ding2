<?php
// $Id: search-results.tpl.php,v 1.7 2010/08/18 18:40:50 dries Exp $

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
    <ul class="list floated">
      <?php print $search_results; ?>
    </ul>
    <?php print $pager; ?>
  </div>
<?php else : ?>
  <div class="search-results">
    <h2><?php print t('Your search yielded no results');?></h2>
    <?php print search_help('search#noresults', drupal_help_arg()); ?>
  </div>
<?php endif; ?>
