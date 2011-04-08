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
        
    <?php if ($serie_title && $page) { ?>
      <h3>
        <?php echo t('Serie title: '); print $serie_title; ?>
      </h3>
    <?php } ?>
        
        
    <div class='creator'>
      <?php if ($creators) { ?>
        <span class='byline'><?php echo ucfirst(t('by')); ?></span>
        <?php print $creators; ?>
      <?php } ?>
      <?php if ($date) { ?>
        <span class='date'>(<?php print $date; ?>)</span>
      <?php } ?>
    </div>

    <?php if (isset($abstract)) { ?>
      <div class="abstract"><?php print $abstract; ?></div>
    <?php } ?>

    <?php print render($content['right']); ?>
  </div>

  <?php if (isset($subjects)) { ?>
    <div class="subjects"><?php print $subjects; ?></div>
  <?php } ?>

</div>
