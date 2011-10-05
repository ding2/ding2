<?php

/**
 * @file
 */

drupal_add_library('system', 'ui.widget');
drupal_add_js(drupal_get_path('module', 'ting_search_carousel'). '/js/jquery.rs.carousel.js');

?>

<div class="ting-search-carousel">
  <div class="ting-search-results">
      <div class="subtitle">
      </div>
      <div class="ting-rs-carousel">
        <div class="rs-carousel-mask">
          <ul class="rs-carousel-runner" style="width: 2100px; left: 0px; ">
          </ul>
        </div>
      </div>
      <div class="clear"></div>
  </div>

  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
