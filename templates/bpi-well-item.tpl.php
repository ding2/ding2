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
  <table>
    <thead>
      <tr>
        <th>
          <?php echo $item['title']; ?>
        </th>
        <th>
          <?php echo $item['date']; ?>
        </th>
        <th colspan="2">
          <?php echo $item['teaser']; ?>
        </th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>
          <?php echo bpi_label_mapper('author'); ?>:
        </td>
        <td>
          <?php echo l($item['author'], 'admin/bpi', array('query' => _bpi_build_query('author', $item['author']))); ?>
        </td>
        <td>
          <?php echo bpi_label_mapper('category'); ?>:
        </td>
        <td>
          <?php echo l($item['category'], 'admin/bpi', array('query' => _bpi_build_query('category', $item['category']))); ?>
        </td>
      </tr>
      <tr>
        <td>
          <?php echo bpi_label_mapper('agency'); ?>:
        </td>
        <td>
          <?php echo l($item['agency'], 'admin/bpi', array('query' => _bpi_build_query('agency', $item['agency_id']))); ?>
        </td>
        <td>
          <?php echo bpi_label_mapper('audience'); ?>:
        </td>
        <td>
          <?php echo l($item['audience'], 'admin/bpi', array('query' => _bpi_build_query('audience', $item['audience']))); ?>
        </td>
      </tr>
    </tbody>
  </table>
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
