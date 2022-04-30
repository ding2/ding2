<?php

/**
 * @file
 * Ding news promoted nodes template.
 *
 * @var array $class
 * @var array $item
 */

$position = ($class[0] == 'first' && $class[1] == 'left' || $class[0] == 'last' && $class[1] == 'right');
$classes = array("ding_nodelist-pn-item");
$classes[] = (empty($item->image) ? 'no-bgimage' : NULL);
$classes[] = (isset($item->video) ? 'has-video' : NULL);
$classes = implode(" ", $classes);
?>
<div
  class="<?php print $classes; ?>"
  <?php if (!empty($item->image) && $position): ?>
    style="background-image: url(<?php print $item->image; ?>);"
  <?php
  endif;
  ?>
  aria-labelledby="<?php print 'item-id-' . $item->nid; ?>"
>
  <?php if (isset($item->video)): ?>
    <div class="media-container">
      <div class="media-content" data-url="<?php print $item->video; ?>"></div>
      <div class="pn-close-media"><i class="icon-cross"></i></div>
    </div>
  <?php
  endif;
  ?>
  <?php if (!empty($item->image) && !$position): ?>
    <div class="nb-image" style="background-image:url(<?php print $item->image; ?>);"></div>
  <?php
  endif;
  ?>
  <div class="eresource-info">
    <h3 id="<?php print 'item-id-' . $item->nid; ?>"><?php print l($item->title, 'node/' . $item->nid); ?></h3>
    <?php print drupal_render($item->category_link); ?>
    <div class="item-body"><?php print $item->teaser_lead; ?></div>
    <div class="read-more">
      <?php print l(t('Read more'), 'node/' . $item->nid); ?>
    </div>
    <?php if (isset($item->video)): ?>
      <div class='pn-media-play'>
        <div class='pn-play pn-round'><i class='icon-play'></i></div>
      </div>
    <?php
    endif;
    ?>
  </div>
</div>
