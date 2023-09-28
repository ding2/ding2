<?php
/**
 * @file
 * Ding blog node blocks template.
 * @var string $item
 * @var string $column
 */
$image_field = 'field_ding_blog_list_image';
$image = _ding_nodelist_get_dams_image_info($item, $image_field);
if (!empty($conf['image_field'])) {
  if ($conf['image_field'] == 'staff_image') {
    $user = user_load($item->uid);
    $staff_data = profile2_load_by_user($user);
    if (!empty($staff_data)) {
      $image['path'] = $staff_data['ding_staff_profile']->field_ding_staff_image['und'][0]['uri'];
    }
  }
}
$img_url = FALSE;
if (!empty($image['path'])) {
  $img_url = image_style_url($conf['image_style'], $image['path']);
}
$category = field_view_field('node', $item, 'field_ding_blog_category', [
  'label' => 'hidden',
  'type' => 'taxonomy_term_reference_plain',
]);
$lead = field_view_field('node', $item, 'field_blog_body', [
  'label' => 'hidden',
  'type' => 'text_trimmed',
  'settings' => ['trim_length' => 120],
]);
$blog_date = date('d.m.y', $item->created);
if ($item->created < $item->changed) {
  $blog_date = date('d.m.y', $item->changed);
}
?>

<article data-row="<?php print $row; ?>" data-column="<?php print $column; ?>" class="item <?php print (!empty($image)) ? 'has-image' : ''; ?>">
  <a href="<?php print url('node/' . $item->nid); ?>">
    <div class="inner">
      <div class="ding-blog-image background-image-styling-16-9" style="background-image:url(<?php print $img_url; ?>)"></div>
      <div class="blog-text">
        <h3 class="title"><?php print $item->title; ?></h3>
        <div class="category-and-submitted">
          <?php print drupal_render($category); ?>
          <div class="submitted"><?php print $blog_date; ?></div>
        </div>
        <?php print drupal_render($lead); ?>
      </div>
    </div>
  </a>
</article>
