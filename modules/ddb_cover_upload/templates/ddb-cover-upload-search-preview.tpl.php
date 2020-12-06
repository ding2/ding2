<?php

/**
 * @file
 * Render search preview.
 */
?>
<div id="preview-wrapper">
  <h2><?php print t("Entity preview") ?></h2>
  <div class="search-result">
    <?php if ($content !== FALSE): ?>
      <?php print render($content) ?>
    <?php else: ?>
      <?php print t('No results found'); ?>
    <?php endif; ?>
  </div>
</div>
