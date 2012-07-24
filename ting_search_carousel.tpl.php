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
$path = drupal_get_path('module', 'ting_search_carousel');

drupal_add_library('system', 'ui.widget');
drupal_add_js($path . '/js/jquery.rs.carousel.js');
drupal_add_js($path . '/js/ting_search_carousel.js');
drupal_add_css($path . '/css/ting_search_carousel.css');
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
            <li style="list-style:none;padding-top:5em;">
              <img src="<?php echo $path;?>/images/ajax-loader.gif" />
            </li>
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
