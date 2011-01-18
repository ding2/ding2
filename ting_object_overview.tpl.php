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
    <h2><?php print $title; ?></h2>
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

  <?php if ($buttons) :?>
    <div class="ting-object-buttons">
    <?php print theme('item_list', $buttons, NULL, 'ul', array('class' => 'buttons')) ?>
    </div>
  <?php endif; ?>
  <?php print render($content); ?>
</div>
