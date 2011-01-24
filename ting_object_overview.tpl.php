<?php
// $Id$
/**
 * @file
 */
?>
<div class="ting-overview clearfix">
  <div class="left-column left">
    <div class="picture">
      <?php if (isset($image)) { ?>
        <?php print $image; ?>
      <?php } ?>
    </div>
    <?php print render($content['left']); ?>
  </div>

  <div class="right-column left">
    <?php print render($title_prefix); ?>
    <?php if (!$page && !$search_result): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <?php if ($other_titles) { ?>
      <h2><?php print $other_titles; ?></h2>
    <?php } ?>
    <?php if ($alternative_titles) { ?>
      <?php foreach ($alternative_titles as $title) { ?>
        <h2>(<?php print $title; ?>)</h2>
      <?php } ?>
    <?php } ?>

    <div class='creator'>
      <span class='byline'><?php echo ucfirst(t('by')); ?></span>
      <?php print $creators; ?>
      <?php if ($date) { ?>
        <span class='date'>(<?php print $date; ?>)</span>
      <?php } ?>
    </div>
    <p><?php print $abstract; ?></p>

    <?php print render($content['right']); ?>
  </div>

  <?php print render($content); ?>
</div>
