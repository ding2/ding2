<?php

/**
 * @file
 * Ding List list template.
 */
?>

<div <?php print ($sortable !== FALSE) ? 'ref="' . $sortable . '"' : ''; ?> class="<?php print $classes; ?>">
  <div class="ding-list-items">
    <?php print render($items); ?>
  </div>
</div>
