<?php
/**
 * @file
 * Render cover.
 *
 * Available variables:
 * - $title: Title of item (sanitized).
 * - $creator: Author of item (sanitized).
 * - $image: Render array for rendering the cover.
 * - $path: Path to the collection/material.
 */
?>
<?php if ($path): ?>
<a href="<?php print $path; ?>" class="search-carousel-cover-link">
<?php endif; ?>
  <div class="search-carousel-cover-image"><?php print render($image); ?></div>
  <?php if ($title): ?>
  <div class="search-carousel-cover-title"><?php print $title; ?></div>
  <?php endif; ?>
<?php if ($path): ?>
  </a>
<?php endif; ?>
