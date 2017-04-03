<?php
/**
 * @file
 * Default template implementation for ding-availability-list.
 *
 * Available variables:
 * - types: The different types as render array (mostly online and pending).
 */
?>
<?php foreach ($types as $type) : ?>
  <?php print render($type); ?>
<?php endforeach; ?>
