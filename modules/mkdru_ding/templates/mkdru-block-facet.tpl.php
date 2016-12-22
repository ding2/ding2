<?php
/**
 * @file
 * Facet item template.
 */
?>
<div class="mkdru-facet-section">
  <?php if (isset($name)) : ?>
    <h3 class="mkdru-facet-title"><?php print $name ?></h3>
  <?php endif; ?>
  <div class="mkdru-facet <?php print $class ?>"></div>
</div>
