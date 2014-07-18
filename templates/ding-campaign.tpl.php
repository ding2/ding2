<?php
/**
 * @file
 * Default template for image campaigns.
 *
 * All the variables mentioned below contains render arrays.
 *
 * Variables:
 *  - $type: The type of campaign (image, plain, text).
 *  - $link: Link to internal or external source.
 *  - $image: The image from the campaign, if link present the image is wrapped
 *            in the link.
 *  - $text: Campaign text.
 */
?>
<div class="ding-campaign ding-campaign--content">
  <?php if (isset($link)) : ?>
    <?php print drupal_render($link); ?>
  <?php endif; ?>
  <?php if (isset($image)) : ?>
    <?php print drupal_render($image); ?>
  <?php endif; ?>
  <?php if (isset($text)) : ?>
    <?php print drupal_render($text); ?>
  <?php endif; ?>
</div>
