<?php
/**
 * @file
 * Single filter item template.
 */
?>
<div class="bpi-filter bpi-filter-<?php echo $filter['name'];?>">
  <p class="bpi-filter-item">
    <span class="bpi-filter-label"><?php echo bpi_label_mapper($filter['name']); ?>: </span>
    <span class="bpi-filter-value"><?php echo l($filter['value'], 'admin/bpi', array('query' => array(BPI_SEARCH_PHRASE_KEY => $filter['search_value']))); ?></span>
    <span class="bpi-filter-remove"><?php echo l('<img src=/' . drupal_get_path('module', 'bpi') . '/images/cross.png' . ' alt="" width="16" height="16" />', 'admin/bpi', array('query' => $filter['search_stripped_filter'], 'html' => TRUE, 'attributes' => array('class' => array('bpi-filter-remove-cross')))); ?></span>
  </p>
</div>
