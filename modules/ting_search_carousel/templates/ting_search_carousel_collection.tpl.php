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
<li class="carousel-item <?php print $classes; ?>">
  <?php if ($path): ?>
    <a href="<?php print $path; ?>" class="carousel-item-link">
  <?php endif; ?>
    <div class="carousel-item-image"><?php print render($image); ?></div>
    <?php if ($title): ?>
      <div class="carousel-item-title"><?php print $title; ?></div>
    <?php endif; ?>
  <?php if ($path): ?>
    </a>
  <?php endif; ?>
</li>
