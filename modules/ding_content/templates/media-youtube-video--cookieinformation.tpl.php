<?php

/**
 * @file
 * Template file for theme('media_youtube_video').
 *
 * Variables available:
 *  $uri - The media uri for the YouTube video (e.g., youtube://v/xsy7x8c9).
 *  $video_id - The unique identifier of the YouTube video (e.g., xsy7x8c9).
 *  $id - The file entity ID (fid).
 *  $url - The full url including query options for the Youtube iframe.
 *  $options - An array containing the Media Youtube formatter options.
 *  $api_id_attribute - An id attribute if the Javascript API is enabled;
 *  otherwise NULL.
 *  $width - The width value set in Media: Youtube file display options.
 *  $height - The height value set in Media: Youtube file display options.
 *  $title - The Media: YouTube file's title.
 *  $alternative_content - Text to display for browsers that don't support
 *  iframes.
 */
?>
<div class="<?php print $classes; ?> media-youtube-<?php print $id; ?>">
  <div class="consent-placeholder" data-category="cookie_cat_marketing">
    <p><?php print t("This video is not accessible as you haven't accepted marketing-cookies"); ?></p>
    <a href="#" class="js-cookie-popup-trigger"><?php print t('Click here to change your consent'); ?></a>
  </div>
  <iframe class="media-youtube-player" data-category-consent="cookie_cat_marketing" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="" data-consent-src="<?php print $url; ?>" name="<?php print $title; ?>" frameborder="0" allowfullscreen><?php print $alternative_content; ?></iframe>
</div>
