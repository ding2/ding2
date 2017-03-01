<?php
/**
 * @file
 *   Ting search carousel template file.
 *
 * * Available variables:
 * - $searches: Array with each tab search.
 * - $hash: string with carousel hash.
 * - $autoplay: configuration for automatic tab switch.
 */
?>

<div class="ting-search-carousel">
  <div id="ting-search-carousel-<?php echo $hash; ?>"
       ting-search-carousel-hash="<?php echo $hash; ?>"
       ting-search-carousel-autoplay="<?php echo $autoplay; ?>"
  >
    <?php foreach ($searches as $i => $search): ?>
      <?php if (!empty($search['search_items'])) : ?>
        <?php foreach ($search['search_items'] as $item_id => $item): ?>
          <div class="ting-search-carousel-item index-<?php echo $i; ?>">
            <?php echo $item; ?>
          </div>
        <?php endforeach; ?>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>

  <!-- Tabs -->
  <div class="ting-search-carousel-tabs">
    <ul class="ting-search-carousel-list-tabs">
      <?php foreach ($searches as $i => $search): ?>
        <li class="ting-search-carousel-item index-<?php echo $i; ?>" tab-index="<?php echo $i; ?>">
          <a href="#"><?php echo $search['title'] ?></a>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>

  <!-- Used for responsive -->
  <select class="ting-search-carousel-select-tabs">
    <?php foreach ($searches as $i => $search): ?>
      <option class="rs-carousel-item">
        <?php echo $search['title'] ?>
      </option>
    <?php endforeach; ?>
  </select>
</div>
