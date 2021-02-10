<?php

/**
 * @file
 * Template file for ding_news rolltab layout.
 *
 * @var array $item
 */

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

$classes = ['ding-tabroll'];
$classes[] = (isset($item->video) ? 'has-video' : NULL);
$classes = implode(' ', $classes);
?>
<div class="<?php print $classes; ?>">
  <div class="ui-tabs-panel">
    <?php print $video_player; ?>
    <div class="image">
      <?php if (!$item->image): ?>
        <span class="no-image"></span>
      <?php
      else:
        ?>
        <?php print $item->image_link; ?>
      <?php
      endif;
      ?>
    </div>

    <div class="info">
      <h3><?php print l($item->title, 'node/' . $item->nid); ?></h3>
      <p> <?php print $item->teaser_lead; ?>
      </p>
    </div>

    <?php print $video_play_btn; ?>
  </div>
</div>
