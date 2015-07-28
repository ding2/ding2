<?php
/**
 * @file
 * Default template implementation for ding-availability-type.
 *
 * Available variables:
 * - label: Label for the type.
 * - links: The availability links.
 */
?>
<?php print $label ?>:
<?php foreach ($links as $link) : ?>
  <?php print render($link['link']); ?>
<?php endforeach; ?>
