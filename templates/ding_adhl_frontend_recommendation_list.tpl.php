<?php
/**
 * @file
 * Default template for the recommendation item list.
 *
 * Available variables:
 * - $items: Render array with recommended Ting Entities.
 * - $type: The list type.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 */
?>
<h3><?php print t("Others borrowed"); ?></h3>
<<?php print $type; ?>>
  <?php foreach ($items as $item) : ?>
    <?php print drupal_render($item); ?>
  <?php endforeach; ?>
</<?php print $type; ?>>
