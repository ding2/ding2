<?php
/**
 * @file
 * Ding event image and text template.
 * Avaialable fields are:
 * ding_content_tags
 * field_address
 * field_ding_body
 * field_list_image
 * field_main_image
 * field_materials
 * group_audience
 */
$edbase = field_view_field('node', $item, 'field_editorial_base_n', 'teaser');
$body = field_view_field('node', $item, 'field_ding_body', 'teaser');
?>

<div class="item">
  <span class="date-created">
    <?php print format_date($item->created, 'custom', 'd/m/Y');?>
  </span> -
  <span class="category">
    <?php print drupal_render($edbase);?>
  </span>
  <h3 class="node-title"><a href="<?php print url('node/' . $item->nid);?>"><?php	print $item->title;?></a></h3>
  <div class="node">
    <?php print drupal_render($body); ?>
  </div>
  <div class="more"><?php print l(t('More'), 'node/' . $item->nid);?></div>
</div>
