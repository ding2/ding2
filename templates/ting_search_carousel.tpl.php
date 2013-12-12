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

<!-- The wrapper div is important because rs-carousel replaces it -->
<div class="rs-carousel-wrapper <?php echo $toggle_description; ?>">
  <div class="rs-carousel">
    <div class="rs-carousel-inner">
      <div class="ajax-loader"></div>
      <?php if ($toggle_description): ?>
        <div class="rs-carousel-title"></div>
      <?php endif; ?>
      <div class="rs-carousel-items">
        <ul></ul>
      </div>
    </div>

    <!-- Only print tabs if there is more than 1 -->
    <?php if (count($searches) > 1): ?>
    <div class="rs-carousel-tabs">
      <ul class="rs-carousel-list-tabs">
        <?php foreach ($searches as $i => $search): ?>
          <li class="rs-carousel-item">
            <a href="#"><?php echo $search['title'] ?></a>
          </li>
        <?php endforeach; ?>
      </ul>

      <!-- Used for responsive -->
      <select class="rs-carousel-select-tabs">
        <?php foreach ($searches as $i => $search): ?>
          <option class="rs-carousel-item">
            <?php echo $search['title'] ?>
          </option>
        <?php endforeach; ?>
      </select>
    </div>
    <?php endif; ?>
  </div>
</div>
