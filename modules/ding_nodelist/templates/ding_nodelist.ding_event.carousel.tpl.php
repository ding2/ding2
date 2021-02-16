<?php

/**
 * @file
 * Ding event image and text template.
 *
 * @var object $item
 */

$image = '';
if (!empty($item->image)) {
  $image = '<div class="event-image" style="background-image:url(' . $item->image . ');"></div>';
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

$classes = ['item'];
$classes[] = (isset($item->video) ? 'has-video' : NULL);
$classes = implode(' ', $classes);
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print $video_player; ?>
  <?php print $image; ?>
  <div class="event-time">
    <div class="event-day"><?php print format_date($item->timestamp, 'custom', 'D', $item->timezone); ?></div>
    <div class="event-date"><?php print format_date($item->timestamp, 'custom', 'd', $item->timezone); ?></div>
    <div class="event-month"><?php print format_date($item->timestamp, 'custom', 'M', $item->timezone); ?></div>
  </div>

  <div class="article-info">
    <div class="node">
      <h3 class="node-title"><?php print l($item->title, 'node/' . $item->nid); ?></h3>
      <div class="item-date"><?php print $item->formated_date; ?></div>
      <div>
        <span class="library"><?php print drupal_render($item->library_link); ?></span>
      </div>
      <p><?php print $item->teaser_lead; ?></p>
      <div class="more">
        <?php print l(t('More'), 'node/' . $item->nid);?>
      </div>
    </div>
  </div>
  <?php print $video_play_btn; ?>
</div>
