<?php

/**
 * @file
 * Template file for rolltab page layout.
 *
 * Notice: This file is also used by
 * - ding_nodelist.ding_news.rolltab.tpl.php
 * - ding_nodelist.ding_event.rolltab.tpl.php
 */

// We need to make sure that the content is wrapped in a <p> tag,
// however sometimes the content already comes with <p> tag, so we'll check for
// that, to avoid any W3C errors by having multiple p tags.
$body = $item->teaser_lead;
$p_body_wrapper = TRUE;

if (!empty($body) && substr($body, 0, 2) === '<p') {
  $p_body_wrapper = FALSE;
}

$video_player = '';
if (isset($item->video)) {
  $video_player = '<div class="media-container">';
  $video_player .= '<div class="media-content" data-url="' . $item->video . '" data-service="' . $item->video_service . '"></div>';
  $video_player .= '<div class="pn-close-media"><i class="icon-cross"></i></div>';
  $video_player .= '</div>';
}

$video_play_btn = '';
if (isset($item->video)) {
  $video_play_btn = "<div class='pn-media-play'><div class='pn-play pn-round'><i class='icon-play'></i></div></div>";
}

$classes = ['ui-tabs-panel'];
$classes[] = (isset($item->video) ? 'has-video' : NULL);
$classes = implode(' ', $classes);
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print $video_player; ?>
  <div class="image">
    <?php if (!$item->image): ?>
      <span class="no-image"></span>
    <?php else: ?>
      <?php print $item->image_link; ?>
    <?php endif; ?>
  </div>
  <div class="info">
    <h3><?php print l($item->title, 'node/' . $item->nid); ?></h3>
     <?php if ($p_body_wrapper): ?>
      <p>
     <?php endif; ?>
     <?php print $body; ?>
     <?php if ($p_body_wrapper): ?>
      </p>
    <?php endif; ?>
  </div>
  <?php print $video_play_btn; ?>
</div>
