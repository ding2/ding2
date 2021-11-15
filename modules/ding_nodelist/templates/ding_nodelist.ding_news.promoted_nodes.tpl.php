<?php

/**
 * @file
 * Ding news promoted nodes template.
 *
 * @var object $item
 * @var array $class
 */

$position = ($class[0] == 'first' && $class[1] == 'left' || $class[0] == 'last' && $class[1] == 'right');
$classes = array("ding_nodelist-pn-item");
$classes[] = (empty($item->image) ? 'no-bgimage' : NULL);
$classes[] = (isset($item->video) ? 'has-video' : NULL);
$classes = implode(" ", $classes);

$case_one = '';
if (!empty($item->image) && $position) {
  $case_one = 'style="background-image: url(' . $item->image . ');"';
}

$case_two = '';
if (!empty($item->image) && !$position) {
  $case_two = '<div class="nb-image" style="background-image:url(' . $item->image . ');"></div>';
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
?>
<div class="<?php print $classes; ?>" <?php print $case_one; ?> aria-labelledby="<?php print 'item-id-' . $item->nid; ?>">
  <?php print $video_player; ?>
  <?php print $case_two; ?>
  <div class="news-info">
    <h3 id="<?php print 'item-id-' . $item->nid; ?>"><?php print l($item->title, 'node/' . $item->nid); ?></h3>
    <?php print drupal_render($item->category_link); ?>
    <div class="date"><?php print $item->date; ?></div>
    <div class="item-body"><?php print $item->teaser_lead; ?></div>
    <div class="read-more">
      <?php print l(t('Read more'), 'node/' . $item->nid); ?>
    </div>
    <?php print $video_play_btn; ?>
  </div>
</div>
