<?php
/**
 * @file
 * Handle theme settings form for the theme.
 */

// We need functions.
require_once(drupal_get_path('theme', 'ddbasic') . '/inc/functions.inc');

/**
 * Implements form_system_theme_settings_alter().
 */
function ddbasic_form_system_theme_settings_alter(&$form, $form_state) {
  // CSS class and markup.
  $form['ddbasic-settings']['classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Classes & Markup'),
    '#description' => t('Modify the default classes and markup from Drupal.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -11,
  );

  $form['ddbasic-settings']['classes']['menu'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menus'),
    '#description' => t('Removes classes from the &lt;li&gt; tag in the menu.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_leaf'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove .leaf from the li '),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_leaf'),
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_has_children'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove .has-children from the li '),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_has_children'),
  );

  $form['ddbasic-settings']['classes']['menu']['ddbasic_classes_menu_items_mlid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove the menu-mlid-[mid] class'),
    '#default_value' => theme_get_setting('ddbasic_classes_menu_items_mlid'),
  );

  // Sticky menus.
  $form['ddbasic-settings']['sticky_menus'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sticky menus'),
    '#description' => t('<h3>Sticky menus</h3>Here you can choose which menus you want to be sticky.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -10,
  );

  // Main menu sticky.
  $form['ddbasic-settings']['sticky_menus']['main_menu_sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Main menu sticky'),
    '#description' => t('By checking this setting the main menu will be sticky (stick to the top of the page when scrolling).'),
    '#default_value' => theme_get_setting('main_menu_sticky'),
  );

  /*
   * Plugins
   */
  $form['ddbasic-settings']['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugins'),
    '#description' => t('<h3>Plugins</h3>Here you can enable plugins supplied with the core theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -10,
  );

  // Equalize.
  $form['ddbasic-settings']['plugins']['load_equalize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equalize'),
    '#description' => t('@link is a jQuery plugin for equalizing the height or width of elements.', array('@link' => l(t('Equalize'), 'https://github.com/tsvensen/equalize.js/'))),
    '#default_value' => theme_get_setting('load_equalize'),
  );

  // Collapse annoying forms.
  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['theme_settings']['#weight'] = 50;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['logo']['#weight'] = 50;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;
  $form['favicon']['#weight'] = 50;

  // iOS icon.
  $form['iosicon'] = array(
    '#type' => 'fieldset',
    '#title' => t('iOS icon settings'),
    '#description' => t("Your iOS icon, is displayed at the homescreen."),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['iosicon']['default_iosicon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the default iOS icon.'),
    '#default_value' => TRUE,
    '#description' => t('Check here if you want the theme to use the default iOS icon.'),
  );
  $form['iosicon']['settings'] = array(
    '#type' => 'container',
    '#states' => array(
      // Hide the favicon settings when using the default favicon.
      'invisible' => array(
        'input[name="default_iosicon"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['iosicon']['settings']['iosicon_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to custom iOS icon'),
    '#description' => t('The path to the image file you would like to use as your custom iOS icon.'),
  );
  $form['iosicon']['settings']['iosicon_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload iOS icon image'),
    '#description' => t("If you don't have direct file access to the server, use this field to upload your iOS icon."),
  );

  // Add css file to display:none on preview.
  drupal_add_css(drupal_get_path('theme', 'ddbasic') . "/color/disable.css");

  // Validate and submit logo, iOS logo and favicon.
  $form['#validate'][] = 'ding2_module_selection_form_validate';
  $form['#submit'][] = 'ding2_module_selection_form_submit';
}