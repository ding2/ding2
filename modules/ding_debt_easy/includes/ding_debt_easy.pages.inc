<?php

/**
 * @file
 * Handle content pages generated by the module and in menu callbacks.
 */

/**
 * Page callback for terms and usage page.
 *
 * @return string
 *   The page content.
 */
function ding_debt_easy_terms_page() {
  // Check if page should be rendered of redirect to other static page.
  _ding_debt_easy_pages_redirect('terms');

  drupal_add_css(drupal_get_path('module', 'ding_debt_easy') . '/css/ding_debt_easy.css');

  $output = '<h1>' . t('Terms declaration', [], ['context' => 'ding_debt_easy']) . '</h1>';

  $config = variable_get('ding_debt_easy_terms', []);
  if (empty($config['text']['value'])) {
    $output .= 'Please configure the Nets Easy integration module. If you excepted content on this page.';
  }
  else {
    $output .= check_markup($config['text']['value'], $config['text']['format']);
  }

  return $output;
}

/**
 * Page callback for privacy and cookies page.
 *
 * @return string
 *   The page content.
 */
function ding_debt_easy_privacy_page() {
  // Check if page should be rendered of redirect to other static page.
  _ding_debt_easy_pages_redirect('privacy');

  drupal_add_css(drupal_get_path('module', 'ding_debt_easy') . '/css/ding_debt_easy.css');

  $output = '<h1>' . t('Privacy declaration', [], ['context' => 'ding_debt_easy']) . '</h1>';

  $config = variable_get('ding_debt_easy_privacy', []);
  if (empty($config['text']['value'])) {
    $output .= 'Please configure the Nets Easy integration module. If you excepted content on this page.';
  }
  else {
    $output .= check_markup($config['text']['value'], $config['text']['format']);
  }

  return $output;
}

/**
 * Redirect page if configuration is set to another static page.
 *
 * @param string $type
 *   The configuration type to check (privacy, terms).
 */
function _ding_debt_easy_pages_redirect($type) {
  $config = variable_get('ding_debt_easy_' . $type, []);

  // Redirect to page outside this module if given in configuration.
  if (!empty($config['url'])) {
    drupal_goto($config['url']);
  }
}
