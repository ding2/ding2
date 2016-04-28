<?php

/**
 * @file
 * A lazy pane "cache" mechanism implementation.
 */

$plugin = array(
  'title' => t('Lazy pane'),
  'cache get' => 'lazy_pane_lazy_cache_get',
  'cache set' => 'lazy_pane_lazy_cache_set',
  'cache clear' => 'lazy_pane_lazy_cache_clear',
  'settings form' => 'lazy_pane_lazy_cache_settings_form',
  'defaults' => array(
    'load_strategy' => 'page-loaded',
    'load_text' => '',
    'show_spinner' => FALSE,
  ),
);

/**
 * A mock cache retrieval function that prevents the pane from rendering and
 * stores its data, for later, on demand rendering.
 */
function lazy_pane_lazy_cache_get($conf, $display, $args, $contexts, $pane = NULL) {

  // Since we can't accurately predict when the cache is to be expired set it
  // permanent and overwrite as many times as necessary.
  $cache_expiry = CACHE_PERMANENT;

  // Generate a unique ID for this lazy pane.
  $lazy_pane_id = lazy_pane_lazy_id($display, $pane);

  // Save the arguments to the cache that will be used to generate the pane.
  $data = array(
    'conf' => $conf,
    'display' => $display,
    'args' => $args,
    'contexts' => $contexts,
    'pane' => $pane,
    'path' => current_path(),
  );

  cache_set($lazy_pane_id, $data, 'cache', $cache_expiry);

  // Add the required javascript libraries for placeholder replacement unless
  // we are already within a lazy pane request, in which case the libs and
  // are settings are already there.
  if (!lazy_pane_is_lazy_request()) {

    $module_path = drupal_get_path('module', 'lazy_pane');

    drupal_add_library('system', 'drupal.ajax');
    drupal_add_js($module_path . '/js/lazy-pane.js');
    drupal_add_css($module_path . '/css/lazy-pane.css');

    $settings = array(
      'lazy_pane' => array(
        'current_path' => current_path(),
      ),
    );

    drupal_add_js($settings, 'setting');
  }

  // Generate the placeholder and its attributes.
  $attr = array(
    'class' => 'lazy-pane-placeholder',
    'data-lazy-pane-id' => $lazy_pane_id,
    'data-lazy-pane-load-strategy' => $conf['load_strategy']
  );

  $placeholder_contents = '';

  if (!empty($conf['show_spinner'])) {
    $placeholder_contents .= '<span class="lazy-pane-spinner"></span>';
  }

  if (!empty($conf['load_text'])) {
    $placeholder_contents .= '<p class="lazy-pane-text">' . check_plain(ctools_context_keyword_substitute($conf['load_text'], array(), $contexts)) . '</p>';
  }
  
  $fake_content = new stdClass();
  $fake_content->type = empty($pane) ? '' : $pane->type;
  $fake_content->subtype = empty($pane) ? '' : $pane->subtype;
  $fake_content->content = '<div ' . drupal_attributes($attr) . '>' . $placeholder_contents . '</div>';

  $fake_cache = new lazy_pane_lazy_cache_object();
  $fake_cache->content = $fake_content;

  // If we are dealing with a display instead of a pane, panels expects a
  // content string and not a pane object.
  if (empty($pane)) {
    $fake_cache->content = $fake_content->content;
  }

  return $fake_cache;
}

/**
 * Lazy pane cache settings form.
 */
function lazy_pane_lazy_cache_settings_form($conf, $display, $pid) {
  $form = array();

  $form['load_strategy'] = array(
    '#title' => t('Load this pane when'),
    '#type' => 'select',
    '#options' => array(
      'page-loaded' => t('The page has loaded'),
      'pane-visible' => t('The pane becomes visible'),
    ),
    '#default_value' => $conf['load_strategy'],
    '#description' => t('The "Pane becomes visible" loading strategy may not work always, as it depends on external factors to the module such as CSS positioning/display rules on the theme.'),
  );

  $form['show_spinner'] = array(
    '#title' => t('Show Spinner'),
    '#type' => 'checkbox',
    '#default_value' => $conf['show_spinner'],
    '#description' => t('If set the placeholder will show a loading spinner.'),
  );

  $form['load_text'] = array(
    '#title' => t('Loading Text'),
    '#type' => 'textfield',
    '#default_value' => $conf['load_text'],
    '#description' => t('If set, the inserted text will be shown on the placeholder while loading. This text is localizable and supports replacement patterns.'),
    '#maxlength' => 256,
  );

  return $form;
}

/**
 * Not implemented.
 */
function lazy_pane_lazy_cache_set($conf, $content, $display, $args, $contexts, $pane = NULL) {
  // Left blank on purpose.
}

/**
 * Not implemented.
 */
function lazy_pane_lazy_cache_clear($display) {
  // Left blank on purpose.
}

/**
 * Generates a unique-id for a given pane/display instance.
 */
function lazy_pane_lazy_id($display, $pane) {
  $id = array('lazy_pane');

  // @todo Improve ID generation strategy.
  if (!empty($display->cache_key)) {
    $id[] = $display->cache_key;
  }
  else {
    $id[] = current_path();
  }

  if (!empty($pane)) {
    $id[] = $pane->type;
    $id[] = $pane->subtype;
    $id[] = $pane->pid;
    $id[] = empty($pane->did) ? '' : $pane->did;
  }

  return implode(':', $id);
}

/**
 * An implementation of panels_cache_object with a nullified restore method.
 */
class lazy_pane_lazy_cache_object extends panels_cache_object {

  function restore() {
    // Left blank on purpose.
  }

}
