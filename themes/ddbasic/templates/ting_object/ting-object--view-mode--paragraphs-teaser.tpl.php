<?php
/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $classes: The classes for the the paragraph.
 * - $attributes: The view mode attributes.
 * - $ting_object_url_object: A url reference to the ting object
 * - $content: Render array of content.
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <a href="<?php print $ting_object_url_object; ?>" class="cover">
    <?php print render($content['ting_cover']); ?>
  </a>
  <?php print render($content); ?>
</div>
