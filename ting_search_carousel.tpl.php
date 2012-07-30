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

<div class="rs-carousel">
  <div class="rs-carousel-inner">
    <div class="ajax-loader"></div>
    <div class="rs-carousel-title"></div>
    <ul class="rs-carousel-runner">
    </ul>
  </div>
  <div class="rs-carousel-tabs">
    <ul>
      <?php foreach ($searches as $i => $search) : ?>
        <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
          <a href="#"><?php echo $search['title'] ?></a>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
