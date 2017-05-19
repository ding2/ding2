<?php

/**
 * @file
 * Defoult carousel template.
 *
 * Available variables:
 * - $title: Title of carousel.
 * - $items: individual items of the carousel.
 * - $offset: Ajax callback offset to start at. -1 for no ajax.
 * - $path: Ajax path for getting more content.
 */
?>
<div class="<?php print $classes; ?>"
  data-title="<?php print $title ?>"
  data-offset="<?php print $offset; ?>"
  data-path="<?php print $path; ?>"
  >
  <ul class="carousel"><?php print render($items); ?></ul>
</div>
