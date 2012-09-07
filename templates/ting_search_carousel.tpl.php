<?php
/**
 * @file
 *
 *
 * * Available variables:
 * - $tab_position: String with settings info, values: top,bottom,left,right.
 * - $searches: Array with each tab search.
 *
 */
?>

<!-- The wrapper div is important because rs-carousel replaces
     <div class="rs-carousel" so we can't add more classes -->
<div class="rs-carousel-wrapper<?php echo $toggle_description ? ' rs-carousel-wide' : ' rs-carousel-compact'; ?>">
  <div class="rs-carousel">
    <div class="rs-carousel-inner">
      <div class="ajax-loader"></div>
      <?php if ($toggle_description) { ?>
        <div class="rs-carousel-title"></div>
      <?php } ?>
      <ul class="rs-carousel-runner">
      </ul>
    </div>

    <!-- Only print tabs if there is more than 1 -->
    <?php if (count($searches) > 1) { ?>
    <div class="rs-carousel-tabs">
      <ul>
        <?php foreach ($searches as $i => $search) : ?>
          <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
            <a href="#"><?php echo $search['title'] ?></a>
          </li>
        <?php endforeach; ?>
      </ul>
    </div>
    <?php } ?>
  </div>
</div>
