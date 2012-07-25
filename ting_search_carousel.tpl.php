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
<div class="ting-search-carousel">
  <?php if ($tab_position != 'bottom') : ?>
  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
  <?php endif; ?>
  <div class="ting-search-results">
      <div class="subtitle">
      </div>
      <div class="ting-rs-carousel">
        <div class="rs-carousel-mask">
          <ul class="rs-carousel-runner">
            <li class="ajax-loader"></li>
          </ul>
        </div>
      </div>
      <div class="clearfix"></div>
  </div>
  <?php if ($tab_position == 'bottom') : ?>
  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
  <?php endif; ?>
</div>
