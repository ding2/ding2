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
  <div class="no-overlay-text">
    <?php
      print render($content['group_text']['group_inner']['ting_type']);
      print $static_title;
      print render($content['group_text']['group_inner']['ting_author']);
    ?>
  </div>
</div>
