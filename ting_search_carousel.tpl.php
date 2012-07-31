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
drupal_add_js($path . '/scripts/jquery.rs.carousel.js');
drupal_add_js($path . '/scripts/ting_search_carousel.js');
drupal_add_css($path . '/css/ting_search_carousel.css');

?>

<div class="rs-carousel<?php echo (variable_get('ting_search_carousel_description_toggle', 0)) ? ' rs-carousel-wide' : ' rs-carousel-compact'; ?>">
  <div class="rs-carousel-inner">
    <div class="ajax-loader"></div>
<?php if (variable_get('ting_search_carousel_description_toggle', 0)) { ?>
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
