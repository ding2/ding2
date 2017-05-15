<?php

/**
 * @file
 * Color.
 */

$info = array(

  // Available colors and color labels used in theme.
  'fields' => array(
    'base' => t('Base'),
    'link' => t('Link'),

    'primary' => t('Primary'),
    'secondary' => t('Secondary'),
    'text' => t('Text'),
    'text_on_primary' => t('Text on primary'),
    'text_on_secondary' => t('Text on secondary'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Default'),
      'colors' => array(
        'base' => '#ffffff',
        'link' => '#ffffff',

        'primary' => '#4d898e',
        'secondary' => '#f66d70',
        'text' => '#01ff01',
        'text_on_primary' => '#02ff02',
        'text_on_secondary' => '#03ff03',
      ),
    ),
  ),

  // Images to copy over.
  'copy' => array(),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(),

  // Gradient definitions.
  'gradients' => array(),

  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_css' => 'color/preview.css',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
