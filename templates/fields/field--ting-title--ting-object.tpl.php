<?php

/**
 * @file field.tpl.php
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <div class="<?php print $classes; ?>"><?php print render($item); ?></div>
<?php endforeach; ?>
