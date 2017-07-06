<?php

/**
 * @file
 * * Available variables:
 * - $tab_position: String with settings info, values: top,bottom,left,right.
 * - $searches: Array with each tab search.
 */
?>

<!-- The wrapper div is important because rs-carousel replaces it -->
<div id="<?php print $id;?>" class="rs-carousel-wrapper">
  <div class="rs-carousel">
    <div class="rs-carousel-inner">
      <?php if ($toggle_description): ?>
        <div class="rs-carousel-title"><?php print $subtitle; ?></div>
      <?php endif; ?>
      <div class="rs-carousel-items">
        <ul><?php print $content; ?></ul>
      </div>
    </div>
  </div>
</div>
