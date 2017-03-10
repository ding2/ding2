<?php
/**
 * @file
 * Content type plugin for social links.
 */

/**
 * Array describing the plugin to CTools/Panels.
 */
$plugin = array(
  'title' => t('Social links'),
  'description' => t('Show social links'),
  'single' => TRUE,
  'content_types' => array('list'),
  'category' => t('Ding!'),
);

/**
 * Render the block.
 */
function ding_social_links_social_links_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $empty = TRUE;

  $block->content = '';
  $social_links = array(
    array('Facebook', 'ding_social_links_facebook'),
    array('Twitter', 'ding_social_links_twitter'),
    array('Instagram', 'ding_social_links_instagram'),
  );

  foreach ($social_links as $social_link) {
    $link = variable_get($social_link[1]);
    $text = $social_link[0];
    $class = drupal_html_class($text);
    if (!empty($link)) {
      $empty = FALSE;
      $block->content .= '<a href="' . $link . '" class="icon ' . $class . '" target="_blank"><span>' . $text . '</span></a><br />';
    }
  }

  if ($empty == FALSE) {
    $block->title = t('Follow us');
  }

  return $block;
}
