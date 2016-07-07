<?php
/**
 * @file
 *
 * Template file for taxonomy-like layout.
 */

$title = $item->title;
$image_field = 'field_' . $item->type . '_list_image';
$image = _ding_nodelist_get_dams_image_info($item, $image_field);
if (!empty($item->publish_on)) {
  $date = $item->publish_on;
}
else {
  $date = $item->created;
}
$date = format_date($date, 'date_combined');
$author = $item->name;
$lead = field_get_items('node', $item, 'field_ding_page_lead');
$teaser = field_get_items('node', $item, 'field_ding_page_body');

/**
 * Available variables:
 *
 * $title
 *   Node title.
 * $body
 *   Node body teaser.
 * $image
 *   Node list image html tag.
 * $date
 *   Node date, created or published if set.
 * $author
 *   Node author name.
 */
?>
<div class="item">
  <div class="item-list-image">
    <a href="<?php print url('node/' . $item->nid);?>"><?php print $image ? theme('image_style', array_merge($image, array('style_name' => $conf['image_style']))) : ''; ?></a>
  </div>
  <div class="item-details">
    <h2 class="item-title"><?php print l($title, 'node/' . $item->nid); ?></h2>
    <div class="item-body">
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
  </div>
</div>
