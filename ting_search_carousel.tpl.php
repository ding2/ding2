<?php
/**
 * @file
 *
 */
$path = drupal_get_path('module', 'ting_search_carousel');

drupal_add_library('system', 'ui.widget');
drupal_add_js($path . '/js/jquery.rs.carousel.js');
drupal_add_js($path . '/js/ting_search_carousel.js');
drupal_add_css($path . '/css/ting_search_carousel.css');

?>
<div class="ting-search-carousel">
  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
  <div class="ting-search-results">
      <div class="subtitle">
      </div>
      <div class="ting-rs-carousel">
        <div class="rs-carousel-mask">
          <ul class="rs-carousel-runner">
          </ul>
        </div>
      </div>
      <div class="clearfix"></div>
  </div>

</div>
