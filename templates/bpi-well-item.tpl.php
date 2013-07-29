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
        <th width="30%">
          Title
        </th>
        <th>
          Date
        </th>
        <th>
          Details
        </th>
        <th>
          Photos
        </th>
        <th>
          Actions
        </th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>
          <?php echo $item['title']; ?>
          <?php echo $item['teaser']; ?>
        </td>
        <td>
          <?php echo $item['date']; ?>
        </td>
        <td width="20%">
          <?php echo bpi_label_mapper('category'); ?>:
          <?php echo l($item['category'], 'admin/bpi', array('query' => _bpi_build_query('category', $item['category']))); ?> <br>
          <?php echo bpi_label_mapper('author'); ?>:
          <?php echo l($item['author'], 'admin/bpi', array('query' => _bpi_build_query('author', $item['author']))); ?> <br>
          <?php echo bpi_label_mapper('agency'); ?>:
          <?php echo l($item['agency'], 'admin/bpi', array('query' => _bpi_build_query('agency', $item['agency_id']))); ?> <br>
          <?php echo bpi_label_mapper('audience'); ?>:
          <?php echo l($item['audience'], 'admin/bpi', array('query' => _bpi_build_query('audience', $item['audience']))); ?>
        </td>
        <td align="center">
          <?php
            $variables = array();
            $photos_str = (count($item['assets'])>0) ? t('Photos available for content') : t('No photos available for content');
            $variables['path'] = drupal_get_path('module', 'bpi') . '/images/' . ((count($item['assets'])>0) ? 'photos' : 'no_photos') . '.png' ;
            $variables['alt'] = $photos_str;
            $variables['title'] = $photos_str;
            $variables['attributes'] = array();
            echo theme_image($variables);
          ?>
        </td>
        <td>
          <?php echo l(t('Preview'), 'admin/bpi/preview/nojs/' . $item['bpi_id'], array('attributes' => array('class' => 'use-ajax'))); ?>
          <?php echo l(t('Syndicate'), 'admin/bpi/syndicate/' . $item['bpi_id']); ?>
        </td>
      </tr>
    </tbody>
  </table>
</div>
