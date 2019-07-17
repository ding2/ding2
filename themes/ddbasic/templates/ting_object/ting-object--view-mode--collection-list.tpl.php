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
<div class="<?php print $classes; ?> list-item-style clearfix"<?php print $attributes; ?>>
  <div class="inner">
    <?php print render($content['group_ting_left_col_collection']); ?>
    <?php print render($content); ?>
  </div>
</div>
