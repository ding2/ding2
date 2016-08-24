<?php
/**
 * @file
 * Default carousel item template.
 *
 * Available variables:
 * - $collection: Legacy item object, do not use.
 * - $title: Title of item (sanitized).
 * - $creator: Author of item (sanitized).
 * - $image: Render array for rendering the cover.
 * - $path: Path to the collection/material.
 */
?>
<li class="carousel-item">
  <a href="<?php print $path; ?>" class="carousel-item-image"><?php print render($image); ?></a>
  <a href="<?php print $path; ?>" class="carousel-item-title"><?php print $title; ?></a>
</li>
