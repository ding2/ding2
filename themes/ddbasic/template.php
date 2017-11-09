<?php

/**
 * @file
 * Preprocessors.
 */

require_once __DIR__ . '/utils.inc';

require_once __DIR__ . '/template.node.php';
require_once __DIR__ . '/template.field.php';

/**
 * Implements hook_preprocess_html().
 */
function ddbasic_preprocess_html(&$vars) {
  global $language;

  // Setup iOS logo if it's set.
  $vars['ios_logo'] = theme_get_setting('iosicon_upload');

  // Set variable for the base path.
  $vars['base_path'] = base_path();

  // Clean up the lang attributes.
  $vars['html_attributes'] = 'lang="' . $language->language . '" dir="' . $language->dir . '"';

  // Add additional body classes.
  $vars['classes_array'] = array_merge($vars['classes_array'], ddbasic_body_class());

  // Search form style.
  switch (variable_get('ting_search_form_style', TING_SEARCH_FORM_STYLE_NORMAL)) {
    case TING_SEARCH_FORM_STYLE_EXTENDED:
      $vars['classes_array'][] = 'search-form-extended';
      $vars['classes_array'][] = 'show-secondary-menu';

      if (menu_get_item()['path'] === 'search/ting/%') {
        $vars['classes_array'][] = 'extended-search-is-open';
      }
      break;
  }

  switch (variable_get('ting_field_search_search_style')) {
    case 'extended_with_profiles':
      $vars['classes_array'][] = 'search-form-extended-with-profiles';
      break;
  }

  // If dynamic background.
  $image_conf = dynamic_background_load_image_configuration($vars);

  if (!empty($image_conf)) {
    $vars['classes_array'][] = 'has-dynamic-background';
  }

  // Detect if current page is a panel page and set class accordingly
  $panel_page = page_manager_get_current_page();

  if (!empty($panel_page)) {
    $vars['classes_array'][] = 'page-panels';
  }
  else {
    $vars['classes_array'][] = 'page-no-panels';
  }

  // Include the libraries.
  libraries_load('jquery.imagesloaded');
  libraries_load('html5shiv');
  libraries_load('masonry');

}

/**
 * Implements hook_process_html().
 *
 * Process variables for html.tpl.php.
 */
function ddbasic_process_html(&$vars) {

  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Implements hook_preprocess_panels_pane().
 */
function ddbasic_preprocess_panels_pane(&$vars) {
  // If using lazy pane caching method, and lazy pane is returniing the rendered
  // content, set the lazy_pane_render variable, so the template can take action
  // accordingly.
  $vars['is_lazy_pane_render'] = !empty($vars['pane']->cache['method'])
    && $vars['pane']->cache['method'] === 'lazy'
    && !empty($vars['display']->skip_cache);
  if ($vars['is_lazy_pane_render']) {
    $vars['theme_hook_suggestions'][] = 'panels_pane__lazy_pane_render';
  }

  // Suggestions base on sub-type.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . str_replace('-', '__', $vars['pane']->subtype);
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $vars['pane']->panel . '__' . str_replace('-', '__', $vars['pane']->subtype);

  if (isset($vars['content'])) {
    if (isset($vars['content']['profile_ding_staff_profile']['#title']) && $vars['content']['profile_ding_staff_profile']['#title'] == 'Staff') {
      $vars['theme_hook_suggestions'][] = 'panels_pane__user_profile_staff';
    }
  }

  // Suggestions on panel pane.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $vars['pane']->panel;

  // Suggestion for mobile user menu in the header.
  if ($vars['pane']->panel == 'header' && $vars['pane']->subtype == 'user_menu') {
    $vars['theme_hook_suggestions'] = array('panels_pane__sub_menu__mobile');
  }

  // Suggestions on menus panes.
  if ($vars['pane']->subtype == 'og_menu-og_single_menu_block' || $vars['pane']->subtype == 'menu_block-3') {
    $vars['theme_hook_suggestions'][] = 'panels_pane__sub_menu';
    $vars['classes_array'][] = 'sub-menu-wrapper';

    // Change the theme wrapper for both menu-block and OG menu.
    if (isset($vars['content']['#content'])) {
      // Menu-block.
      $vars['content']['#content']['#theme_wrappers'] = array('menu_tree__sub_menu');
    }
    else {
      // OG menu.
      $vars['content']['#theme_wrappers'] = array('menu_tree__sub_menu');
    }
  }

  if ($vars['pane']->subtype == 'menu_block-main_menu_second_level') {
    ddbasic_body_class('has-second-level-menu');
  }
}

/**
 * Render callback.
 *
 * Remove panels div separator.
 */
function ddbasic_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode('', $vars['panes']);

  return $output;
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__menu_block__1($vars) {
  return '<ul class="main-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__menu_block__main_menu_second_level($vars) {
  return '<ul class="main-menu-second-level">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__sub_menu($vars) {
  return '<ul class="main-menu-third-level">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__menu_block__2($vars) {
  return '<ul class="secondary-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__menu_tabs_menu($vars) {
  return '<ul class="topbar-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__user_menu($vars) {
  return '<ul class="system-user-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements hook_preprocess_views_view_field().
 */
function ddbasic_preprocess_views_view_field(&$vars) {
  $view = $vars['view'];

  switch ($view->name . ' ' . $view->current_display . ' ' . $vars['field']->field) {
    case 'tags_list ding_content_tags type':
      $taxonomy_term = taxonomy_term_load($view->args[0]);

      switch ($vars['row']->node_type) {
        case 'ding_news':
          $type = t('News', array(), array('context' => 'pluralis'));
          break;

        case 'ding_event':
          $type = t('Events');
          break;

        default:
          $type = $vars['output'];
          break;
      }

      $vars['output'] = t('@type in the category @term', array(
        '@type' => $type,
        '@term' => $taxonomy_term->name,
      ));
      break;
  }
}

/**
 * Implements hook_preprocess_views_view_unformatted().
 *
 * Overwrite views row classes.
 */
function ddbasic_preprocess_views_view(&$vars) {
  switch ($vars['name']) {
    case 'ding_event':
      switch ($vars['view']->current_display) {
        case 'ding_event_library_list':
        case 'ding_event_groups_list':
          // Add max-two-rows class.
          $vars['classes_array'][] = 'max-two-rows';
          $vars['classes_array'][] = 'not-frontpage-view';

          break;

        case 'ding_event_list_frontpage':
          // Add max-two-rows class.
          $vars['classes_array'][] = 'max-two-rows';
          $vars['classes_array'][] = 'frontpage-view';

          // Add event count setting as js variable.
          $count = variable_get('ding_event_frontpage_items_per_page', 6);
          drupal_add_js(array('number_of_events' => $count), 'setting');

          break;
      }
      break;

    case 'ding_news':
      switch ($vars['view']->current_display) {
        case 'ding_news_groups_list':
          // Add slide-on-mobile class.
          $vars['classes_array'][] = 'slide-on-mobile';
          break;

        case 'ding_news_frontpage_list':
          // Add slide-on-mobile class.
          $vars['classes_array'][] = 'slide-on-mobile';
          // Add first-child-large class.
          $vars['classes_array'][] = 'first-child-large';
          break;
      }
      break;

    case 'ding_groups':
      switch ($vars['view']->current_display) {
        case 'panel_pane_frontpage':
          // Add slide-on-mobile class.
          $vars['classes_array'][] = 'slide-on-mobile';
          break;
      }
      break;
  }
}

/**
 * Implements hook_preprocess_views_view_unformatted().
 *
 * Overwrite views row classes.
 */
function ddbasic_preprocess_views_view_unformatted(&$vars) {
  // Add type class to tags_list view.
  if ($vars['view']->name == 'tags_list') {
    $nodes = array_values($vars['view']->style_plugin->row_plugin->nodes);
    reset($vars['rows']);
    $first_key = key($vars['rows']);
    $first_node = $nodes[$first_key];
    $vars['type_class'] = drupal_html_class($first_node->type);
  }

  // Set no-masonry to true for frontpage event view
  if ($vars['view']->name == 'ding_event' && $vars['view']->current_display == 'ding_event_list_frontpage') {
    $vars['no_masonry'] = TRUE;
  }

  // Class names for overwriting.
  $row_first = "first";
  $row_last = "last";

  $view = $vars['view'];
  $rows = $vars['rows'];

  // Set arrays.
  $vars['classes_array'] = array();
  $vars['classes'] = array();

  // Variables.
  $count = 0;
  $max = count($rows);

  // Loop through the rows and overwrite the classes, its important that the
  // $row variable is here, as it's the $id that we need.
  foreach ($rows as $id => $row) {
    $count++;

    $vars['classes'][$id][] = $count % 2 ? 'odd' : 'even';
    $vars['classes'][$id][] = 'views-row';

    if ($count == 1) {
      $vars['classes'][$id][] = $row_first;
    }
    if ($count == $max) {
      $vars['classes'][$id][] = $row_last;
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $vars['classes'][$id][] = $row_class;
    }

    if ($vars['classes'] && $vars['classes'][$id]) {
      $vars['classes_array'][$id] = implode(' ', $vars['classes'][$id]);
    }
    else {
      $vars['classes_array'][$id] = '';
    }
  }
}

/**
 * Implements theme_link().
 *
 * Adds a class "label" to all link in taxonomies.
 *
 * @see theme_link()
 */
function ddbasic_link($variables) {
  if (isset($variables['options']['entity_type']) && $variables['options']['entity_type'] == 'taxonomy_term') {
    if (!isset($variables['options']['no_label'])) {
      // Add classes label and label-info.
      if (!isset($variables['options']['attributes']['class'])) {
        $variables['options']['attributes']['class'] = array();
      }
      $variables['options']['attributes']['class'][] = 'label';
      $variables['options']['attributes']['class'][] = 'label-info';
    }
  }

  return '<a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a>';
}

/**
 * Implements template_preprocess_user_profile().
 */
function ddbasic_preprocess_user_profile(&$variables) {
  $variables['user_profile']['summary']['member_for']['#access'] = FALSE;
}

/**
 * Implements template_preprocess_entity().
 *
 * Runs an entity specific preprocess function, if it exists.
 */
function ddbasic_preprocess_entity(&$variables, $hook) {
  $function = __FUNCTION__ . '_' . $variables['entity_type'];
  if (function_exists($function)) {
    $function($variables, $hook);
  }
}

/**
 * Profile2 specific implementation of template_preprocess_entity().
 */
function ddbasic_preprocess_entity_profile2(&$variables) {
  // Add staff position as a renderable field without label for subheader.
  if ($variables['profile2']->type == 'ding_staff_profile') {
    if (isset($variables['content']['group_contactinfo']['field_ding_staff_position'])) {
      $staff_position = $variables['content']['group_contactinfo']['field_ding_staff_position'];
      $staff_position['#label_display'] = 'hidden';
      $variables['position_no_label'] = $staff_position;
    }
    else {
      $variables['position_no_label'] = FALSE;
    }
  }
}

/**
 * Implements template_preprocess_menu_links().
 */
function ddbasic_preprocess_menu_link(&$variables) {
  if ($variables['theme_hook_original'] === 'menu_link__user_menu') {
    $path = explode('/', $variables['element']['#href']);

    switch (end($path)) {
      case 'status-loans':
        $loans = ddbasic_account_count_loans() - ddbasic_account_count_overdue_loans();
        if (!empty($loans)) {
          $variables['element']['#title'] .= ' <span class="menu-item-count">' . $loans . '</span>';
        }
        break;

      case 'status-loans-overdue':
        $loans = ddbasic_account_count_overdue_loans();
        if (!empty($loans)) {
          $variables['element']['#title'] .= ' <span class="menu-item-count">' . $loans . '</span>';
        }
        break;

      case 'status-reservations':
        $reservations = ddbasic_account_count_reservation_not_ready();
        if (!empty($reservations)) {
          $variables['element']['#title'] .= ' <span class="menu-item-count">' . $reservations . '</span>';
        }
        break;

      case 'status-reservations-ready':
        $reservations = ddbasic_account_count_reservation_ready();
        if (!empty($reservations)) {
          $variables['element']['#title'] .= ' <span class="menu-item-count menu-item-count-success">' . $reservations . '</span>';
        }
        break;

      case 'status-debts':
        $debts = ddbasic_account_count_debts();
        if (!empty($debts)) {
          $variables['element']['#title'] .= ' <span class="menu-item-count menu-item-count-warning">' . $debts . '</span>';
        }
        break;

      case 'view':
        if ($path[0] === 'user') {
          $notifications = ding_message_get_message_count();
          if (!empty($notifications)) {
            $variables['element']['#title'] .= ' <span class="menu-item-count">' . $notifications . '</span>';
          }
        }
        break;
    }
  }
}

/**
 * Implements theme_menu_link().
 */
function ddbasic_menu_link($vars) {
  $element = $vars['element'];

  // Render any sub-links/menus.
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Add default class to a tag.
  $element['#localized_options']['attributes']['class'] = array(
    'menu-item',
  );

  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $link = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $link . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_link().
 *
 * Add specific markup for top-bar menu exposed as menu_block_4.
 */
function ddbasic_menu_link__menu_tabs_menu($vars) {
  global $user;

  // Check if the class array is empty.
  if (empty($vars['element']['#attributes']['class'])) {
    unset($vars['element']['#attributes']['class']);
  }

  $element = $vars['element'];

  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Add default class to a tag.
  $element['#localized_options']['attributes']['class'] = array(
    'menu-item',
  );

  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $element['#localized_options']['attributes']['class'][] = 'js-topbar-link';

  // Some links are not translated properly, this makes sure these links are
  // run through the t function.
  if ($element['#original_link']['title'] == $element['#original_link']['link_title']) {
    $element['#title'] = t($element['#title']);
  }

  // Add some icons to our top-bar menu. We use system paths to check against.
  switch ($element['#href']) {
    case 'search':
      $title_prefix = '<i class="icon-search"></i>';
      $element['#localized_options']['attributes']['class'][] = 'topbar-link-search';
      $element['#attributes']['class'][] = 'topbar-link-search';
      break;

    case 'node':
      // Special placeholder for mobile user menu. Fall through to next case.
      $element['#localized_options']['attributes']['class'][] = 'default-override';

    case 'user':
      $title_prefix = '<i class="icon-user"></i>';
      $title_suffix = '<i class="icon-arrow-down"></i>';
      // If a user is logged in we change the menu item title.
      if (user_is_logged_in()) {
        $element['#href'] = 'user/me/view';
        $element['#title'] = t('My Account');
        $element['#attributes']['class'][] = 'topbar-link-user-account';
        $element['#localized_options']['attributes']['class'][] = 'topbar-link-user-account';

        if (ding_user_is_provider_user($user)) {
          // Fill the notification icon, in following priority.
          // Debts, overdue, ready reservations, notifications.
          $notification = array();
          $debts = ddbasic_account_count_debts();
          if (!empty($debts)) {
            $notification = array(
              'count' => $debts,
              'type' => 'debts',
            );
          }

          if (empty($notification)) {
            $overdues = ddbasic_account_count_overdue_loans();
            if (!empty($overdues)) {
              $notification = array(
                'count' => $overdues,
                'type' => 'overdue',
              );
            }
          }

          if (empty($notification)) {
            $ready = ddbasic_account_count_reservation_ready();
            if (!empty($ready)) {
              $notification = array(
                'count' => $ready,
                'type' => 'ready',
              );
            }
          }

          if (!empty($notification)) {
            $element['#title'] .= '<div class="notification-count notification-count-type-' . $notification['type'] . '">' . $notification['count'] . '</div>';
          }
        }
      }
      else {
        $element['#attributes']['class'][] = 'topbar-link-user';
        $element['#localized_options']['attributes']['class'][] = 'topbar-link-user';
      }
      break;

    case 'user/logout':
      $title_prefix = '<i class="icon-signout"></i>';
      $element['#localized_options']['attributes']['class'][] = 'topbar-link-signout';
      $element['#attributes']['class'][] = 'topbar-link-signout';

      break;

    case 'libraries':
      $title_prefix = '<i class="icon-clock"></i>';
      $element['#localized_options']['attributes']['class'][] = 'topbar-link-opening-hours';
      $element['#attributes']['class'][] = 'topbar-link-opening-hours';
      break;

    default:
      $title_prefix = '<i class="icon-align-justify"></i>';
      $element['#localized_options']['attributes']['class'][] = 'topbar-link-menu';
      $element['#attributes']['class'][] = 'topbar-link-menu';
      break;
  }

  $output = l($title_prefix . '<span>' . $element['#title'] . '</span>' . $title_suffix, $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_theme_script().
 *
 * Since Drupal 7 does not (yet) support the 'browser' option in drupal_add_js()
 * ddbasic provides a way to load scripts inside conditional comments.
 * This function wraps a file in script elements and returns a string.
 */
function ddbasic_theme_script($filepath) {
  $script = '';

  // We need the default query string for cache control finger printing.
  $query_string = variable_get('css_js_query_string', '0');

  if (file_exists($filepath)) {
    $file = file_create_url($filepath);
    $script = '<script src="' . $file . '?' . $query_string . '"></script>';
  }

  return $script;
}

/**
 * Return the info file array for a particular theme, usually the active theme.
 *
 * Simple wrapper function for list_themes().
 *
 * @param string $theme_name
 *   Name of the current theme.
 */
function ddbasic_get_info($theme_name) {
  $info = &drupal_static(__FUNCTION__, array());
  if (empty($info)) {
    $themes = list_themes();
    foreach ($themes as $key => $value) {
      if ($theme_name == $key) {
        $info = $themes[$theme_name]->info;
      }
    }
  }

  return $info;
}

/**
 * Implements theme_item_list().
 *
 * This is the default theme function. With the wrapper div removed.
 */
function ddbasic_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];
  $output = '';

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array(
          'items' => $children,
          'title' => NULL,
          'type' => $type,
          'attributes' => $attributes,
        ));
      }
      if ($i == 0) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

/**
 * Implements hook_process_page().
 */
function ddbasic_process_page(&$vars) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Preprocess function for ting_object theme function.
 */
function ddbasic_preprocess_ting_object(&$vars) {

  switch ($vars['elements']['#entity_type']) {
    case 'ting_object':

      switch ($vars['elements']['#view_mode']) {
        // Teaser.
        case 'teaser':

          // Check if overlay is disabled and set class.
          if (theme_get_setting('ting_object_disable_overlay') == TRUE) {
            $vars['classes_array'][] = 'no-overlay';
          }
          break;
      }
      break;
  }
}

/**
 * Implements hook_process_ting_object().
 *
 * Adds wrapper classes to the different groups on the ting object.
 */
function ddbasic_process_ting_object(&$vars) {
  //
  // Add tpl suggestions for node view modes.
  if (isset($vars['elements']['#view_mode'])) {
    $vars['theme_hook_suggestions'][] = $vars['elements']['#bundle'] . '__view_mode__' . $vars['elements']['#view_mode'];
  }

  switch ($vars['elements']['#entity_type']) {
    case 'ting_collection':
      // Add a reference to the ting_object if it's included in a
      // ting_collection.
      foreach ($vars['object']->entities as &$ting_entity) {
        $ting_entity->in_collection = $vars['object'];
      }
      break;

    case 'ting_object':

      $uri_collection = entity_uri('ting_collection', $vars['object']);
      $vars['ting_object_url_collection'] = url($uri_collection['path']);

      $uri_object = entity_uri('ting_object', $vars['object']);
      $vars['ting_object_url_object'] = url($uri_object['path']);

      switch ($vars['elements']['#view_mode']) {

        // Teaser.
        case 'teaser':
          $vars['content']['group_text']['read_more_button'] = array(
            array(
              '#theme' => 'link',
              '#text' => t('Read more'),
              '#path' => $uri_object['path'],
              '#options' => array(
                'attributes' => array(
                  'class' => array(
                    'action-button',
                    'read-more-button',
                  ),
                ),
                'html' => FALSE,
              ),
            ),
            '#weight' => 9998,
          );

          if ($vars['object']->is('reservable')) {
            $vars['content']['group_text']['reserve_button'] = ding_reservation_ding_entity_buttons(
              'ding_entity',
              $vars['object'],
              'ajax'
            );
          }
          if ($vars['object']->online_url) {
            // Slice the output, so it only usese the online link button.
            $vars['content']['group_text']['online_link'] = array_slice(ting_ding_entity_buttons(
              'ding_entity',
              $vars['object']
            ), 0, 1);
          }

          // Check if teaser has rating function and remove abstract.
          if (!empty($vars['content']['group_text']['group_rating']['ding_entity_rating_action'])) {
            unset($vars['content']['group_text']['ting_abstract']);
          }

          break;

        // Reference teaser.
        case 'reference_teaser':
          $vars['content']['buttons'] = array(
            '#prefix' => '<div class="buttons">',
            '#suffix' => '</div>',
            '#weight' => 9999,
          );
          $vars['content']['buttons']['read_more_button'] = array(
            array(
              '#theme' => 'link',
              '#text' => t('Read more'),
              '#path' => $uri_object['path'],
              '#options' => array(
                'attributes' => array(
                  'class' => array(
                    'action-button',
                    'read-more-button',
                  ),
                ),
                'html' => FALSE,
              ),
            ),
          );

          if ($vars['object']->is('reservable')) {
            $vars['content']['buttons']['reserve_button'] = ding_reservation_ding_entity_buttons(
              'ding_entity',
              $vars['object'],
              'ajax'
            );
          }
          if ($vars['object']->online_url) {
            // Slice the output, so it only usese the online link button.
            $vars['content']['buttons']['online_link'] = array_slice(ting_ding_entity_buttons(
              'ding_entity',
              $vars['object']
            ), 0, 1);
          }

          break;

      }
      break;
  }

  // Inject the availability from the collection into the actual ting object.
  // Notice it's only done on the "search_result" view mode.
  if ($vars['elements']['#entity_type'] == 'ting_object' && isset($vars['object']->in_collection)
      && isset($vars['elements']['#view_mode'])
      && in_array($vars['elements']['#view_mode'], array('search_result'))) {
    $availability = field_view_field(
      'ting_collection',
      $vars['object']->in_collection,
      'ting_collection_types',
      array(
        'type' => 'ding_availability_with_labels',
        'weight' => 9999,
      )
    );
    $availability['#title'] = t('Borrowing options');

    if (isset($vars['content']['group_ting_right_col_search'])) {
      if (isset($vars['content']['group_ting_right_col_search']['group_info']['group_rating']['#weight'])) {
        $availability['#weight'] = $vars['content']['group_ting_right_col_search']['group_info']['group_rating']['#weight'] - 0.5;
      }
      $vars['content']['group_ting_right_col_search']['group_info']['availability'] = $availability;
    }
    else {
      $vars['content']['group_ting_right_col_collection']['availability'] = $availability;
    }
  }

  if (isset($vars['elements']['#view_mode']) && $vars['elements']['#view_mode'] == 'full') {
    switch ($vars['elements']['#entity_type']) {
      case 'ting_object':
        $content = $vars['content'];
        $vars['content'] = array();

        if (isset($content['group_ting_object_left_column']) && $content['group_ting_object_left_column']) {
          $vars['content']['ting-object'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'left_column' => $content['group_ting_object_left_column'],
              'right_column' => $content['group_ting_object_right_column'],
            ),
          );

          unset($content['group_ting_object_left_column']);
          unset($content['group_ting_object_right_column']);
        }

        if (isset($content['group_material_details']) && $content['group_material_details']) {
          $vars['content']['material-details'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'details' => $content['group_material_details'],
            ),
          );
          unset($content['group_material_details']);
        }

        if (isset($content['content']['ding_availability_holdings'])) {

          $vars['content']['holdings-available'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'details' => $content['group_holdings_available'],
            ),
          );
          unset($content['content']['ding_availability_holdings']);
        }

        if (isset($content['group_periodical_issues']) && $content['group_periodical_issues']) {
          $vars['content']['periodical-issues'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'details' => $content['group_periodical_issues'],
            ),
          );
          unset($content['group_periodical_issues']);
        }

        if (isset($content['group_on_this_site']) && $content['group_on_this_site']) {
          $vars['content']['on_this_site'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div id="ting_reference" class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'details' => $content['group_on_this_site'],
            ),
          );
          unset($content['group_on_this_site']);
        }

        if (isset($content['ting_relations']) && $content['ting_relations']) {
          $vars['content']['ting-relations'] = array(
            'content' => array(
              'details' => $content['ting_relations'],
            ),
          );
          unset($content['ting_relations']);
        }

        // Move the rest over if any have been defined in the UI.
        if (!empty($content)) {
          // Move the remaining content one level down in the array structure.
        }

        break;
    }
  }
}

/**
 * Preprocess function for material_item theme function.
 */
function ddbasic_preprocess_material_item(&$variables) {

  // Add label for styling to checkbox.
  $element = $variables['element'];

  $element[$element['#id']]['#title'] = ".";

  // Render the checkbox.
  $variables['checkbox'] = drupal_render($element[$element['#id']]);

  if (!empty($variables['information']['expiry'])) {
    $variables['information']['expiry']['#weight'] = 1;
  }
}

/**
 * Preprocess function form element.
 */
function ddbasic_preprocess_form_element(&$variables) {
  // Remove label to profile date field.
  if ($variables['element']['#id'] == 'edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2') {
    $variables['element']['#title'] = '';
  }
  // Change label for date picker.
  if ($variables['element']['#id'] == 'edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2-datepicker-popup-0') {
    $variables['element']['#title'] = 'Til dato:';
  }
  // Change label for date picker.
  if ($variables['element']['#id'] == 'edit-profile-provider-alma-field-alma-reservation-pause-und-0-value-datepicker-popup-0') {
    $variables['element']['#title'] = 'Fra dato:';
  }

}

/**
 * Preprocess ding_carousel.
 */
function ddbasic_preprocess_ding_carousel(&$variables) {
  // Add ajax to make reserve links work.
  drupal_add_library('system', 'drupal.ajax');
  drupal_add_library('system', 'ui.widget');

  // The ding carousel's do not use the standard Drupal ajax API so it doesn't
  // automatically include availability, covers and rating handling.
  drupal_add_js(drupal_get_path('module', 'ding_availability') . '/js/ding_availability.js');
  drupal_add_js(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js');
  drupal_add_js(drupal_get_path('module', 'ding_entity_rating') . '/js/ding_entity_rating.js');
}

/**
 * Override theme_date_display_range().
 */
function ddbasic_date_display_range($variables) {
  $date1 = $variables['date1'];
  $date2 = $variables['date2'];
  $timezone = $variables['timezone'];
  $attributes_start = $variables['attributes_start'];
  $attributes_end = $variables['attributes_end'];

  $start_date = '<span class="date-display-start"' . drupal_attributes($attributes_start) . '>' . $date1 . '</span>';
  $end_date = '<span class="date-display-end"' . drupal_attributes($attributes_end) . '>' . $date2 . $timezone . '</span>';

  // If microdata attributes for the start date property have been passed in,
  // add the microdata in meta tags.
  if (!empty($variables['add_microdata'])) {
    $start_date .= '<meta' . drupal_attributes($variables['microdata']['value']['#attributes']) . '/>';
    $end_date .= '<meta' . drupal_attributes($variables['microdata']['value2']['#attributes']) . '/>';
  }

  // Wrap the result with the attributes.
  return t('!start-date - !end-date', array(
    '!start-date' => $start_date,
    '!end-date' => $end_date,
  ));
}

/**
 * Ting search pager.
 */
function ddbasic_ting_search_pager($variables) {
  if (!empty($_GET['size'])) {
    $results_per_page = $_GET['size'];
  }
  else {
    $results_per_page = variable_get('ting_search_results_per_page', 10);
  }

  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = 3;
  $hide_list = isset($variables['hide_list']) ? $variables['hide_list'] : FALSE;
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re quantity).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re quantity).
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  $li_previous = theme('pager_previous', array(
    'text' => isset($tags[1]) ? $tags[1] : t('‹ previous'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));

  if (empty($li_previous)) {
    $li_previous = "&nbsp;";
  }

  $li_first = theme('pager_first', array(
    'text' => isset($tags[0]) ? $tags[0] : t('« first'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if (empty($li_first)) {
    $li_first = "&nbsp;";
  }

  $li_next = theme('pager_next', array(
    'text' => isset($tags[3]) ? $tags[3] : t('next ›'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  if (empty($li_next)) {
    $li_next = "&nbsp;";
  }

  $li_last = theme('pager_last', array(
    'text' => isset($tags[4]) ? $tags[4] : t('last »'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if (empty($li_last)) {
    $li_last = "&nbsp;";
  }

  if ($pager_total[$element] > 1) {
    if ($pager_current > 2) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }

    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous,
    );

    // When there is more than one page, create the pager list.
    if (!$hide_list && $i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array(
              'text' => $i * $results_per_page - $results_per_page + 1 . '-' . $i * $results_per_page,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => $i * $results_per_page - $results_per_page + 1 . '-' . $i * $results_per_page,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array(
              'text' => $i * $results_per_page - $results_per_page + 1 . '-' . $i * $results_per_page,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-ellipsis'),
            'data' => '…',
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    else {
      $items[] = array(
        'class' => array('pager-current'),
        'data' => $pager_current,
      );
    }

    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );
    if ($pager_current + 1 < $pager_max && $li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    return theme('item_list', array(
      'items' => $items,
      'type' => 'ul',
      'attributes' => array(
        'class' => array('pager'),
      ),
    ));
  }
}

/**
 * Overrides theme_select().
 *
 * Adds wrapper div to all select form elements, for better styling in FF.
 */
function ddbasic_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  if (isset($variables['element']['#attributes']['multiple']) && $variables['element']['#attributes']['multiple'] == 'multiple') {
    return '<div class="select-wrapper select-wrapper-multiple"><select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select></div>';
  } else {
    return '<div class="select-wrapper"><select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select></div>';
  }

}

/**
 * Implements hook_libraries_info().
 */
function ddbasic_libraries_info() {
  return array(
    'html5shiv' => array(
      'name' => 'HTML5 Shiv',
      'vendor url' => 'https://github.com/aFarkas/html5shiv',
      'download url' => 'https://github.com/aFarkas/html5shiv/archive/3.7.3.zip',
      'version arguments' => array(
        'file' => 'dist/html5shiv.min.js',
        'pattern' => '/\*.*HTML5 Shiv ([0-9a-zA-Z\.-]+)/',
      ),
      'files' => array(
        'js' => array('dist/html5shiv.min.js'),
      ),
    ),
    'masonry' => array(
      'name' => 'Masonry',
      'vendor url' => 'https://github.com/desandro/masonry',
      'download url' => 'https://github.com/desandro/masonry/archive/v4.1.1.zip',
      'version arguments' => array(
        'file' => 'dist/masonry.pkgd.min.js',
        'pattern' => '/\*.*Masonry PACKAGED v([0-9a-zA-Z\.-]+)/',
      ),
      'files' => array(
        'js' => array('dist/masonry.pkgd.min.js'),
      ),
    ),
  );
}
