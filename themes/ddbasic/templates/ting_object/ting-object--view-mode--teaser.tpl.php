<?php

/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="inner">
    <?php print render($content['ting_cover']); ?>
    <?php print render($content); ?>

  </div>
</div>
