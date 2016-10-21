<?php

/**
 * @file
 * This file contains theming functions for ding_serendipity
 */

/**
 * Preprocess function for ding_serendipity_info.
 */
function ding_serendipity_preprocess_ding_serendipity_info(&$variables) {
  if (!isset($variables['classes_array']) || !is_array($variables['classes_array'])) {
    $variables['classes_array'] = array();
  }

  $variables['classes_array'] += array('field', 'field-name-ding-serendipity-info');
  if ($variables['label_display'] == 'hidden') {
    $variables['classes_array'][] = 'field-label-hidden';
  }
  elseif ($variables['label_display'] == 'inline') {
    $variables['classes_array'][] = 'field-label-inline';
  }
}

/**
 * Preprocess function for ding_serendipity_source.
 */
function ding_serendipity_preprocess_ding_serendipity_source(&$variables) {
  if (!isset($variables['classes_array']) || !is_array($variables['classes_array'])) {
    $variables['classes_array'] = array();
  }
  $variables['classes_array'] += array('ding-serendipity-source', 'element-hidden');
}

/**
 * Theme function for ding_serendipity_info.
 */
function theme_ding_serendipity_info($variables) {
  $output = '<div class="' . implode(' ', $variables['classes_array']) . '">';
  $output .= '<label class="field-label">' . $variables['title'] . '</label>';
  $output .= '<div class="field-item">' . $variables['information'] . '</div>';
  $output .= '</div>';
  return $output;
}

/**
 * Theme function for ding_serendipity_source.
 */
function theme_ding_serendipity_source($variables) {
  return '<div class="' . implode(' ', $variables['classes_array']) . '">' . $variables['source'] . '</div>';
}
