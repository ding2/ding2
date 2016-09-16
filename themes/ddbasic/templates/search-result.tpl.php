<?php

/**
 * @file
 * Modified version of the default theme implementation for displaying a single
 * search result. The h3 title have been removed.
 *
 * @see template_preprocess()
 * @see template_preprocess_search_result()
 * @see template_process()
 */
?>
<li class="list-item <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($snippet): ?>
    <?php print $snippet; ?>
  <?php endif; ?>
  <?php if ($info): ?>
    <p class="search-info"><?php print $info; ?></p>
  <?php endif; ?>
</li>
