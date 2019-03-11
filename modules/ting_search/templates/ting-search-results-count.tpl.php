<?php
/**
 * @file
 * Default theme implementation for displaying search results count.
 *
 * @see template_preprocess_ting_search_results()
 */
?>
<div class="search-results-count">
  <span class="count"><?php print format_plural($count, '1 Result', '@count Results'); ?></span>
</div>
