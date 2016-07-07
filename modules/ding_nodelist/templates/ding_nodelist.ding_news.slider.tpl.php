<?php
/**
 * @file
 * Ding news slider template.
 */

$category = field_view_field('node', $item, 'field_ding_news_category', 'teaser');
$lead = field_get_items('node', $item, 'field_ding_news_lead');
$teaser = field_get_items('node', $item, 'field_ding_news_body');
?>
<li class="item">
  <div class="category">
    <?php print drupal_render($category);?>
  </div>
  <h3 class="node-title"><a href="<?php print url('node/' . $item->nid);?>"><?php print $item->title;?></a></h3>
  <div class="node">
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
  </div>
  <div class="more"><?php print l(t('More'), 'node/' . $item->nid);?></div>
</li>
