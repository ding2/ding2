<?php

$info = array(

  // Available colors and color labels used in theme.
  'fields' => array(
    'base' => t('Base color'),
    'text' => t('Text color'),
    'topbar_background_color' => t('Topbar background color'),
    'header_background_color' => t('Header background color'),
    'navigation_background_color' => t('Navigation background color'),
    'tabroll_background_color_mobile' => t('Tabroll background color - mobile'),
    'link' => t('Link color'),
    'link_hover' => t('Label color hover'),
    'labels_background_color' => t('Label background color'),
    'labels_background_color_hover' => t('Label background color hover'),
    'labels_text_color' => t('Label text color'),
    'labels_text_color_hover' => t('Label text color hover'),
    'content_background_color' => t('Content background color'),
    'list_background_color' => t('List background color'),
    'list_background_color_odd' => t('List item background color (odd)'),
    'list_background_color_even' => t('List item background color (even)'),
    'list_text_color' => t('List text color'),
    'footer_background_color' => t('Footer background color'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
        'base' => '#0072b9',
        'text' => '#494949',
        'topbar_background_color' => '#000001',
        'header_background_color' => '#00caff',
        'navigation_background_color' => '#fffffc',
        'tabroll_background_color_mobile' => '#a32e10',
        'link' => '#00b7e7',
        'link_hover' => '#006681',
        'labels_background_color' => '#00cafe',
        'labels_background_color_hover' => '#00a7d2',
        'labels_text_color' => '#fffffd',
        'labels_text_color_hover' => '#fafaf7',
        'content_background_color' => '#fffffe',
        'list_background_color' => '#ebebeb',
        'list_background_color_odd' => '#e8e8e8',
        'list_background_color_even' => '#f2f2f2',
        'list_text_color' => '#4c4c4c',
        'footer_background_color' => '#262626',
      ),
    ),
    'classic' => array(
      'title' => t('Classic'),
      'colors' => array(
        'base' => '#0072b9',
        'text' => '#494949',
        'topbar_background_color' => '#000000',
        'header_background_color' => '#00caff',
        'navigation_background_color' => '#ffffff',
        'tabroll_background_color_mobile' => '#a32e10',
        'link' => '#00b7e7',
        'link_hover' => '#006681',
        'labels_background_color' => '#00caff',
        'labels_background_color_hover' => '#00a7d2',
        'labels_text_color' => '#ffffff',
        'labels_text_color_hover' => '#fafaf7',
        'content_background_color_hover' => '#ffffff',
        'list_background_color' => '#ebebeb',
        'list_background_color_odd' => '#e8e8e8',
        'list_background_color_even' => '#f2f2f2',
        'list_text_color' => '#4c4c4c',
        'footer_background_color' => '#262626',
      ),
    ),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/ddbasic.styles.css',
  ),

  // Color areas to fill (x, y, width, height).
  /*'fill' => array(
    'base' => array(0, 0, 760, 568),
    'link' => array(107, 533, 41, 23),
  ),*/

  'fill' => array(),

  'copy' => array(),

  // Gradient definitions.
  'gradients' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  //'preview_image' => 'color/preview.png',
  'preview_css' => 'color/preview.css',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
