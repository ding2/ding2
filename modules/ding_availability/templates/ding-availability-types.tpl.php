<?php
/**
 * @file
 * Default template implementation for ding-availability-types.
 *
 * Available variables:
 * - types: The different types as render array (mostly online and pending).
 */
?>
<?php foreach ($types as $type) : ?>
  <p class="<?php print $type['#class']; ?>"><?php print render($type); ?></p>
<?php endforeach; ?>
