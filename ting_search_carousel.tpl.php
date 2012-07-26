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
<div class="ting-search-carousel ting-search-carousel-<?php print $tab_position; ?>">
  <div class="carousel-subtitle"></div>
  <ul class="ting-search-controller ting-search-controller-<?php print $tab_position; ?>">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
  <div class="ting-search-results">
    <div id="rs-carousel" class="rs-carousel">
      <ul class="rs-carousel-runner">
        <li class="ajax-loader"></li>
      </ul>
    </div>
  </div>
</div>
