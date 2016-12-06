<?php
/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
 hide($content['group_serendipity']);
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="inner">
    <a href="<?php print $ting_object_url_object; ?>">
      <?php print render($content['ting_cover']); ?>
    </a>
    <?php print render($content); ?>

  </div>
  <?php print render($content['group_serendipity']); ?>
</div>
