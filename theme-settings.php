<?php

// We need functions
require_once(drupal_get_path('theme', 'ddbasic') . '/inc/functions.inc');

/*
 * Implements form_system_theme_settings_alter().
 */
function ddbasic_form_system_theme_settings_alter(&$form, $form_state) {
  $path_to_at_core = drupal_get_path('theme', 'ddbasic');

  /*
   * CSS class and markup
   */
  $form['ddbasic-settings']['classes'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Classes & Markup'),
    '#description'   => t('Modify the default classes and markup from Drupal.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight'=> -11
  );

  $form['ddbasic-settings']['classes']['menu'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Menus'),
    '#description'   => t('Removes classes from the &lt;li&gt; tag in the menu.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_leaf'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Remove .leaf from the li '),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_leaf')
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_has_children'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Remove .has-children from the li '),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_has_children')
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_items_mlid'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Remove the menu-mlid-[mid] class'),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_items_mlid')
  );

  /*
   * Sticky menus
   */
  $form['ddbasic-settings']['sticky_menus'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sticky menus'),
    '#description' => t('<h3>Sticky menus</h3><p>Here you can choose which menus you want to be sticky.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight'=> -10,
  );
  
  // Main menu sticky
  $form['ddbasic-settings']['sticky_menus']['main_menu_sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Main menu sticky'),
    '#description' => t('By checking this setting the main menu will be sticky (stick to the top of the page when scrolling).'),
    '#default_value' => theme_get_setting('main_menu_sticky'),
  );  

  /*
   * Polyfill settings
   */
  $form['ddbasic-settings']['polyfills'] = array(
    '#type' => 'fieldset',
    '#title' => t('Polyfills'),
    '#description' => t('<h3>Polyfills</h3><p>Here you can enable commonly used Polyfills supplied with the core theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight'=> -10,
  );

  $form['ddbasic-settings']['polyfills']['fills'] = array(
    '#type' => 'fieldset',
    '#title' => t('Polyfills'),
  );

  // HTML5 shiv
  $form['ddbasic-settings']['polyfills']['fills']['load_html5js'] = array(
    '#type' => 'checkbox',
    '#title' => t('HTML5 support in IE'),
    '#description' => t('By checking this setting the site will load the <a href="!link" target="_blank">html5shiv</a>. Turning this off will be bad news for IE6-8.', array('!link' => '//github.com/aFarkas/html5shiv')),
    '#default_value' => theme_get_setting('load_html5js'),
  );

  // Selectivizr
  $form['ddbasic-settings']['polyfills']['fills']['load_selectivizr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Selectivizr'),
    '#description' => t('<a href="!link" target="_blank">Selectivizr</a> is a JavaScript utility that emulates CSS3 pseudo-classes and attribute selectors in Internet Explorer 6-8.', array('!link' => 'http://selectivizr.com')),
    '#default_value' => theme_get_setting('load_selectivizr'),
  );

  // Scalefix
  $form['ddbasic-settings']['polyfills']['fills']['load_scalefixjs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scalefix for iOS'),
    '#description' => t('Fixes the iOS Orientationchange zoom bug.'),
    '#default_value' => theme_get_setting('load_scalefixjs'),
    '#states' => array(
      'invisible' => array('input[name="disable_responsive_styles"]' => array('checked' => TRUE)),
    ),
  );


  /*
   * Plugins
   */
  $form['ddbasic-settings']['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugins'),
    '#description' => t('<h3>Plugins</h3><p>Here you can enable plugins supplied with the core theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight'=> -10,
  );

  // Equalize
  $form['ddbasic-settings']['plugins']['load_equalize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equalize'),
    '#description' => t('<a href="!link" target="_blank">Equalize</a> is a jQuery plugin for equalizing the height or width of elements.', array('!link' => 'https://github.com/tsvensen/equalize.js/')),
    '#default_value' => theme_get_setting('load_equalize'),
  );

  // Collapse annoying forms
  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['theme_settings']['#weight'] = 50;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['logo']['#weight'] = 50;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;
  $form['favicon']['#weight'] = 50;
}
