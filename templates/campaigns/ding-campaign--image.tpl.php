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
<?php if (isset($image)) : ?>
  <div class="ding-campaign ding-campaign--image">
    <?php print drupal_render($image); ?>
  </div>
<?php endif; ?>
