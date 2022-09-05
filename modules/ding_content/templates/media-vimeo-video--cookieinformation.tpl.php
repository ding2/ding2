<?php

/**
 * @file
 * Template file for theme('media_vimeo_video').
 *
 * Variables available:
 *  $uri - The media uri for the Vimeo video (e.g., vimeo://v/xsy7x8c9).
 *  $video_id - The unique identifier of the Vimeo video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the Vimeo iframe.
 *  $options - An array containing the Media Vimeo formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: Vimeo file display options.
 *  $height - The height value set in Media: Vimeo file display options.
 *  $title - The Media: YouTube file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 */
?>
<div class="<?php print $classes; ?> media-vimeo-<?php print $id; ?>">
  <div class="consent-placeholder" data-category="cookie_cat_statistic">
    <p><?php print t("This video is not accessible as you haven't accepted marketing-cookies"); ?></p>
    <a href="#" class="js-cookie-popup-trigger"><?php print t('Click here to change your consent'); ?></a>
  </div>
  <iframe class="media-vimeo-player" data-category-consent="cookie_cat_statistic" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="" data-consent-src="<?php print $url; ?>" frameborder="0" allowfullscreen><?php print $alternative_content; ?></iframe>
</div>
