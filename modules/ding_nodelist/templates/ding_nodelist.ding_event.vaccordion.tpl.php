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

$items = $variables['item'];
$item = new stdClass();
if ($variables['conf']['sorting'] == 'event_date') {
  // Get the object from the array in the case we are sorting by date.
  foreach ($items as $k => $v) {
    $item = $v;
  }
}
$image_field = 'field_' . $item->type . '_list_image';
$image = _ding_nodelist_get_dams_image_info($item, $image_field);
$event_date = _ding_nodelist_get_event_date($item);
$event_date_formatted = _ding_nodelist_formated_ding_event_date($item, 'short');
$library = field_view_field('node', $item, 'og_group_ref', 'default');
$category = field_view_field('node', $item, 'field_ding_event_category', 'default');
$background_image_style = $image ? ' style="background-image: url(\'' . image_style_url($conf['image_style'], $image['path']) . '\')" title="' . $image['title'] . '"' : '';
?>
<div class="item event va-slice"<?php print $background_image_style; ?>>
  <div class="va-title">
    <div class="event-time">
      <div class="event-day"><?php print t(date('D', $event_date));?></div>
      <div class="event-date"><?php print format_date($event_date, 'day_only'); ?></div>
      <div class="event-month"><?php print format_date($event_date, 'short_month_only'); ?></div>
    </div>
  </div>
  <div class="va-content" data-destination="<?php print url('node/' . $item->nid) ?>">
    <div class="inner-wrapper">
      <div class="caption">
        <h3 class="node-title">
          <?php print l($item->title, 'node/' . $item->nid);?>
        </h3>
      </div>
      <div class="data">
        <div class="event-timestamp">
          <span><?php print $event_date_formatted; ?></span>
        </div>
        <div class="event-details">
          <span class="event-library">
            <?php print drupal_render($library); ?>
          </span>
          <span class="event-fee">
            <?php
              $fee_field = field_get_items('node', $item, 'field_ding_event_price');
              if (is_array($fee_field)) {
                $fee = current($fee_field);
                print '&mdash; ' . $fee['value'] . ' ' . t('kr.');
              }
              else {
                print '&mdash; ' . t('Free');
              }
            ?>
          </span>
        </div>
      </div>
    </div>
  </div>
</div>
