<?php
/**
 * @file
 */
?>

<?php
  drupal_add_library('system', 'ui.widget');
  drupal_add_js(drupal_get_path('module', 'ting_search_carousel'). '/js/jquery.rs.carousel.js');
?>

<div class="ting-search-carousel">
  <div id="container">
    <div id="ting-rs-carousel-1" class="module rs-carousel">
      <div class="rs-carousel-mask">
        <ul class="rs-carousel-runner" style="width: 2100px; left: 0px; ">
          <li class="rs-carousel-item color-1">0</li>
          <li class="rs-carousel-item color-2">1</li>
          <li class="rs-carousel-item color-3">2</li>
          <li class="rs-carousel-item color-1">3</li>
          <li class="rs-carousel-item color-2">4</li>
          <li class="rs-carousel-item color-4">5</li>
          <li class="rs-carousel-item color-7">6</li>
          <li class="rs-carousel-item color-5">7</li>
          <li class="rs-carousel-item color-6">8</li>
          <li class="rs-carousel-item color-1">9</li>
          <li class="rs-carousel-item color-2">10</li>
          <li class="rs-carousel-item color-2">11</li>
          <li class="rs-carousel-item color-3">12</li>
          <li class="rs-carousel-item color-1">13</li>
          <li class="rs-carousel-item color-2">14</li>
          <li class="rs-carousel-item color-4">15</li>
          <li class="rs-carousel-item color-7">16</li>
          <li class="rs-carousel-item color-5">17</li>
          <li class="rs-carousel-item color-6">18</li>
          <li class="rs-carousel-item color-1">19</li>
        </ul>
      </div>
  </div>
  <ul class="search-results">
    <?php foreach ($searches as $i => $search) :?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <div class="subtitle">
          <?php echo $search['subtitle']; ?>
        </div>
        <ul class="jcarousel-skin-ting-search-carousel">
        </ul>
      </li>
    <?php endforeach; ?>
  </ul>

  <ul class="search-controller">
    <?php foreach ($searches as $i => $search) : ?>
      <li class="<?php echo ($i == 0) ? 'active' : ''; ?>">
        <a href="#"><?php echo $search['title'] ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
