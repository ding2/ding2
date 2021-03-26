<?php

/**
 * @file
 * Ding event image and text template.
 *
 * Available fields are:
 * ding_content_tags
 * field_address
 * field_ding_body
 * field_list_image
 * field_main_image
 * field_materials
 * group_audience.
 */
$edbase = field_view_field('node', $item, 'field_ding_section', 'teaser');
?>
<div class="item">
  <span class="date-created">
    <?php print format_date($item->created, 'custom', 'd/m/Y');?>
  </span> -
  <span class="category">
    <?php print drupal_render($edbase);?>
  </span>
  <h3 class="node-title"><?php print l($item->title, 'node/' . $item->nid); ?></h3>
  <div class="node">
    <?php
      $body = field_view_field('node', $item, 'field_ding_body', 'teaser');
      print drupal_render($body);
    ?>
  </div>
  <div class="more"><?php print l(t('More'), 'node/' . $item->nid);?></div>
</div>
