<?php
/**
 * @file
 * Content type plugin for all opening hours.
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
 * Render the block
 */
function ding_ddbasic_social_links_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $empty = TRUE;
  
  $block->content = '';
  $social_links = array(array('Facebook', 'social_link_facebook'), array('Twitter', 'social_link_twitter'), array('Instagram', 'social_link_instagram'));
  
  foreach ($social_links as $social_link) {
    $link = ddbasic_theme_setting($social_link[1]);
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