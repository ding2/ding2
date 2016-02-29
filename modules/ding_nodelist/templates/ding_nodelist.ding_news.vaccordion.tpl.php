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
$image_field = 'field_' . $item->type . '_list_image';
$image = _ding_nodelist_get_dams_image_info($item, $image_field);
$background_image_style = $image ? ' style="background-image: url(\'' . image_style_url($conf['image_style'], $image['path']) . '\')" title="' . $image['title'] . '"' : '';
?>
<div class="item news va-slice"<?php print $background_image_style; ?>>
  <div class="va-content" data-destination="<?php print url('node/' . $item->nid);?>">
    <div class="inner-wrapper">
      <div class="caption">
        <h3>
          <?php print l($item->title, 'node/' . $item->nid);?>
        </h3>
        <div class="category">
          <?php
            $category = field_view_field('node', $item, 'field_ding_news_category', 'teaser');
            print drupal_render($category);
          ?>
        </div>
      </div>
    </div>
  </div>
</div>
