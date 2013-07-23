<?php
/**
 * @file
 * Single item template.
 */
drupal_add_library('system', 'drupal.ajax');
drupal_add_library('system', 'jquery.form');
drupal_add_library('system', 'ui.dialog');

?>
<div class="bpi-item bpi-single-well-item">
  <h3 class="item-title"><?php echo $item['title']; ?></h3>
  <span class="item-date"><?php echo $item['date']; ?></span>
  <p class="item-teaser"><?php echo $item['teaser']; ?></p>
  <div class="item-filters item-details">
    <div class="details-left">
      <p class="item-details-author">
        <span class="item-details-author-label details-label"><?php echo bpi_label_mapper('author'); ?>: </span>
        <span class="item-details-author-value details-value"><?php echo l($item['author'], 'admin/bpi', array('query' => _bpi_build_query('author', $item['author']))); ?></span>
      </p>
      <p class="item-details-agency">
        <span class="item-details-agency-label details-label"><?php echo bpi_label_mapper('agency'); ?>: </span>
        <span class="item-details-agency-value details-value"><?php echo l($item['agency'], 'admin/bpi', array('query' => _bpi_build_query('agency', $item['agency_id']))); ?></span>
      </p>
    </div>
    <div class="details-right">
      <p class="item-details-category">
        <span class="item-details-category-label details-label"><?php echo bpi_label_mapper('category'); ?>: </span>
        <span class="item-details-category-value details-value"><?php echo l($item['category'], 'admin/bpi', array('query' => _bpi_build_query('category', $item['category']))); ?></span>
      </p>
      <p class="item-details-audience">
        <span class="item-details-audience-label details-label"><?php echo bpi_label_mapper('audience'); ?>: </span>
        <span class="item-details-audience-value details-value"><?php echo l($item['audience'], 'admin/bpi', array('query' => _bpi_build_query('audience', $item['audience']))); ?></span>
      </p>
    </div>
  </div>
  <div class="item-indicate item-indicate-images">
    <?php 
      $variables = array();
      $photos_str = (count($item['assets'])>0) ? t('Photos available for content') : t('No photos available for content');
      $variables['path'] = drupal_get_path('module', 'bpi') . '/images/' . ((count($item['assets'])>0) ? 'photos' : 'no_photos') . '.png' ;
      $variables['alt'] = $photos_str;
      $variables['title'] = $photos_str;
      $variables['attributes'] = array();
      echo theme_image($variables);
    ?>
  </div>
  <p class="item-action item-action-preview">
    <?php echo l(t('Preview'), 'admin/bpi/preview/nojs/' . $item['bpi_id'], array('attributes' => array('class' => 'use-ajax'))); ?>
  </p>
  <p class="item-action item-action-syndicate">
    <?php echo l(t('Syndicate'), 'admin/bpi/syndicate/' . $item['bpi_id']); ?>
  </p>
</div>
