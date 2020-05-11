<?php
/**
 * @file
 * Render search preview.
 */
?>
<div id="search-lookup-wrapper">
  <h2>Search lookup</h2>
  <div class="search-result">
    <?php if ($content !== FALSE): ?>
      <?php print render($content) ?>
    <?php else: ?>
      <?php print t('No results found'); ?>
    <?php endif; ?>
  </div>
</div>
