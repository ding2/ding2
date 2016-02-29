<?php
/**
 * @file
 * Ding news image and text template.
 */

$image_field = 'field_' . $item->type . '_list_image';
$image = _ding_nodelist_get_dams_image_info($item, $image_field);
$category = field_view_field('node', $item, 'field_ding_news_category', 'teaser');
$lead = field_get_items('node', $item, 'field_ding_news_lead');
$teaser = field_get_items('node', $item, 'field_ding_news_body');
?>
<div class="item">
  <div class="article_image">
    <a href="<?php print url('node/' . $item->nid);?>"><?php print $image ? theme('image_style', array_merge($image, array('style_name' => $conf['image_style']))) : ''; ?></a>
  </div>
  <div class="article-info">
    <div class="label-wrapper"><?php print drupal_render($category);?></div>
    <div class="node">
      <h3 class="node-title"><a href="<?php print url('node/' . $item->nid);?>"><?php print $item->title;?></a></h3>
      <p>
        <?php
          if (isset($lead[0]['safe_value'])) {
            print strip_tags($lead[0]['safe_value']);
          }
          elseif (isset($teaser[0]['safe_value'])) {
            print strip_tags($teaser[0]['safe_value']);
          }
          else {
            print '';
          }
        ?>
      </p>
      <div class="more">
        <?php print l(t('More'), 'node/' . $item->nid);?>
      </div>
    </div>
  </div>
</div>
