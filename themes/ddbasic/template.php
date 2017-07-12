<?php
/**
 * @file
 * Preprocess and Process Functions.
 */

// Includes frequently used theme functions that gets theme info, css files etc.
include_once drupal_get_path('theme', 'ddbasic') . '/inc/functions.inc';

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

  // Load ddbasic plugins.
  ddbasic_load_plugins();

  // Add conditional CSS for IE8.
  drupal_add_css(path_to_theme() . '/css/ddbasic.ie8.min.css', array(
    'group' => CSS_THEME,
    'browsers' => array(
      'IE' => 'lte IE 8',
      '!IE' => FALSE,
    ),
    'weight' => 999,
    'preprocess' => FALSE,
  ));

  // Add conditional CSS for IE9.
  drupal_add_css(path_to_theme() . '/css/ddbasic.ie9.min.css', array(
    'group' => CSS_THEME,
    'browsers' => array(
      'IE' => 'lte IE 9',
      '!IE' => FALSE,
    ),
    'weight' => 999,
    'preprocess' => FALSE,
  ));
}

/**
 * Implements hook_process_html().
 *
 * Process variables for html.tpl.php
 */
function ddbasic_process_html(&$vars) {
  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  if (!$vars['is_front']) {
    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);
    // Add unique class for each website section.
    $section = explode('/', $path);
    $section = array_shift($section);
    $arg = explode('/', $_GET['q']);
    if ($arg[0] == 'node' && isset($arg[1])) {
      if ($arg[1] == 'add') {
        $section = 'node-add';
      }
      elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
        $section = 'node-' . $arg[2];
      }
    }
    $vars['classes_array'][] = drupal_html_class('section-' . $section);
  }
  // Store the menu item since it has some useful information.
  $vars['menu_item'] = menu_get_item();
  if ($vars['menu_item']) {
    switch ($vars['menu_item']['page_callback']) {
      case 'views_page':
        // Is this a Views page?
        $vars['classes_array'][] = 'page-views';
        break;

      case 'page_manager_page_execute':
      case 'page_manager_node_view':
      case 'page_manager_contact_site':
        // Is this a Panels page?
        $vars['classes_array'][] = 'page-panels';
        break;
    }
  }

  // Color module.
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Implements hook_form_alter().
 */
function ddbasic_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'search_block_form':
      $form['search_block_form']['#attributes']['placeholder'] = t('Search the library');
      $form['search_block_form']['#field_prefix'] = '<i class="icon-search"></i>';
      $form['search_block_form']['#title'] = t('Search the library database and the website');

      // Remove element-invisible
      unset($form['search_block_form']['#title_display']);
      break;

    case 'user_login_block':
      $form['name']['#title'] = t('Loan or social security number');
      $form['name']['#field_prefix'] = '<i class="icon-user"></i>';
      $form['name']['#attributes']['placeholder'] = t('The number is 10 digits');
      $form['name']['#type'] = 'password';

      $form['pass']['#title'] = t('Pincode');
      $form['pass']['#field_prefix'] = '<i class="icon-lock"></i>';
      $form['pass']['#attributes']['placeholder'] = t('Pincode is 4 digits');

      // Add JavaScript that will place focus in the login box, when the Login
      // is clicked.
      drupal_add_js(drupal_get_path('theme', 'ddbasic') . '/scripts/ddbasic.login.js', 'file');

      unset($form['links']);

      // Temporary hack to get rid of open id links.
      unset($form['openid_links']);
      unset($form['#attached']['js']);
      break;
  }
}


/**
 * Implements hook_preprocess_panels_pane().
 */
function ddbasic_preprocess_panels_pane(&$vars) {
  // Suggestions base on sub-type.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . str_replace('-', '__', $vars['pane']->subtype);
  $vars['theme_hook_suggestions'][] = 'panels_pane__'  . $vars['pane']->panel . '__' . str_replace('-', '__', $vars['pane']->subtype);

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
function ddbasic_menu_tree__menu_block__2($vars) {
  return '<ul class="secondary-menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function ddbasic_menu_tree__sub_menu($vars) {
  return '<ul class="sub-menu">' . $vars['tree'] . '</ul>';
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
 * Implements hook_preprocess_views_view_unformatted().
 *
 * Overwrite views row classes
 */
function ddbasic_preprocess_views_view_unformatted(&$vars) {
  // Class names for overwriting.
  $row_first = "first";
  $row_last  = "last";

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
 * Implements hook_preprocess_views_view_field().
 */
function ddbasic_preprocess_views_view_field(&$vars) {
  $field = $vars['field'];

  if (isset($field->field_info) && $field->field_info['field_name'] == 'field_ding_event_price') {
    $ding_event_price = intval($vars['output']);
    // Show "Free" text if ding_event_price is empty or zero.
    if (empty($ding_event_price)) {
      $vars['output'] = t('Free');
    }
  }
}

/**
 * Implements hook_preprocess_user_picture().
 *
 * Override or insert variables into template user_picture.tpl.php
 *
 * @TODO: Is there an render array for this, str replacement is not cheap.
 * @TODO: Why do we replace and insert span2 thumbnail classes? Aren't they
 *        bootstrap specific?
 */
function ddbasic_preprocess_user_picture(&$variables) {
  // Inject the class we need into the A tag of user_picture.
  $variables['user_picture'] = str_replace('<a ', '<a class="span2 thumbnail" ', $variables['user_picture']);

  // Inject the class we need into the IMG tag of user_picture.
  $variables['user_picture'] = str_replace('<img ', '<img class="pull-left" ', $variables['user_picture']);
}

/**
 * Implements hook_preprocess_node().
 *
 * Override or insert variables into the node templates.
 */
function ddbasic_preprocess_node(&$variables, $hook) {
  // Add ddbasic_byline to variables.
  $variables['ddbasic_byline'] = t('By: ');

  // Add event node specific ddbasic variables.
  if (isset($variables['content']['#bundle']) && $variables['content']['#bundle'] == 'ding_event') {

    // Add event location variables.
    if (!empty($variables['content']['field_ding_event_location'][0]['#address']['name_line'])) {
      $variables['ddbasic_event_location'] = $variables['content']['field_ding_event_location'][0]['#address']['name_line'] . '<br/>' . $variables['content']['field_ding_event_location'][0]['#address']['thoroughfare'] . ', ' . $variables['content']['field_ding_event_location'][0]['#address']['locality'];
    }
    else {
      // User OG group ref to link back to library.
      if (isset($variables['content']['og_group_ref'])) {
        $variables['ddbasic_event_location'] = $variables['content']['og_group_ref'];
      }
    }

    // Add event date to variables. A render array is created based on the date
    // format "date_only".
    $event_date_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', array(
      'label' => 'hidden',
      'type' => 'date_default',
      'settings' => array(
        'format_type' => 'ding_date_only',
        'fromto' => 'both',
      ),
    ));
    $variables['ddbasic_event_date'] = $event_date_ra[0]['#markup'];

    // Add event time to variables. A render array is created based on the date
    // format "time_only".
    $event_time_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', array(
      'label' => 'hidden',
      'type' => 'date_default',
      'settings' => array(
        'format_type' => 'ding_time_only',
        'fromto' => 'both',
      ),
    ));
    $variables['ddbasic_event_time'] = $event_time_ra[0]['#markup'];

    // Show "Free" text if ding_event_price is empty or zero. Unfortunately we
    // can't use the field template for this, since it's not called when the
    // price field is empty. This means we also need to handle this en the views
    // field preprocess.
    if (empty($variables['content']['field_ding_event_price']['#items'][0]['value'])) {
      $variables['content']['field_ding_event_price'][0]['#markup'] = t('Free');
    }
  }

  // Add tpl suggestions for node view modes.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__view_mode__' . $variables['view_mode'];
  }

  // Add "read more" links to event, news and e-resource in search result view
  // mode.
  if ($variables['view_mode'] == 'search_result') {
    switch ($variables['node']->type) {
      case 'ding_event':
        $more_link = array(
          '#type' => 'link',
          '#title' => t('Read more'),
          '#href' => 'node/' . $variables['nid'],
          '#options' => array(
            'attributes' => array(
              'title' => $variables['title'],
            ),
            'html' => FALSE,
          ),
          '#prefix' => '<span class="event-link">',
          '#surfix' => '</div>',
          '#weight' => 6,
        );

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;

      case 'ding_news':
        $more_link = array(
          '#type' => 'link',
          '#title' => t('Read more'),
          '#href' => 'node/' . $variables['nid'],
          '#options' => array(
            'attributes' => array(
              'title' => $variables['title'],
            ),
            'html' => FALSE,
          ),
          '#prefix' => '<span class="news-link">',
          '#surfix' => '</span>',
          '#weight' => 6,
        );

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;

      case 'ding_eresource':
        $more_link = array(
          '#type' => 'link',
          '#title' => t('Read more'),
          '#href' => 'node/' . $variables['nid'],
          '#options' => array(
            'attributes' => array(
              'title' => $variables['title'],
            ),
            'html' => FALSE,
          ),
          '#prefix' => '<span class="eresource-link">',
          '#surfix' => '</span>',
          '#weight' => 6,
        );

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;

      case 'ding_page':
        $more_link = array(
          '#type' => 'link',
          '#title' => t('Read more'),
          '#href' => 'node/' . $variables['nid'],
          '#options' => array(
            'attributes' => array(
              'title' => $variables['title'],
            ),
            'html' => FALSE,
          ),
          '#prefix' => '<span class="page-link">',
          '#surfix' => '</span>',
          '#weight' => 6,
        );

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;
    }
  }

  // For search result view mode move title into left col. group.
  if (isset($variables['content']['group_right_col_search'])) {
    $variables['content']['group_right_col_search']['title'] = array(
      '#type' => 'link',
      '#title' => decode_entities($variables['title']),
      '#href' => 'node/' . $variables['nid'],
      '#options' => array(
        'attributes' => array(
          'title' => $variables['title'],
        ),
        'html' => FALSE,
      ),
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',
    );
  }

  // Add updated to variables.
  $variables['ddbasic_updated'] = t('!datetime', array(
    '!datetime' => format_date(
      $variables['node']->changed,
      $type = 'long',
      $format = '',
      $timezone = NULL,
      $langcode = NULL
    ))
  );

  // Modified submitted variable.
  if ($variables['display_submitted']) {
    $variables['submitted'] = t('!datetime', array(
      '!datetime' => format_date(
        $variables['created'],
        $type = 'long',
        $format = '',
        $timezone = NULL,
        $langcode = NULL
      ))
    );
  }
}

/**
 * Implements template_preprocess_field().
 */
function ddbasic_preprocess_field(&$vars, $hook) {
  // Get current view mode (teaser).
  $view_mode = $vars['element']['#view_mode'];
  $field_name = $vars['element']['#field_name'];

  // Add suggestion for ddbasic specific field.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic';

  // Add suggestion for ddbasic field with specific name.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic_' . $field_name;

  // Add suggestion for ddbasic field in specific view mode.
  $vars['theme_hook_suggestions'][] = 'field__ddbasic_' . $view_mode;

  // Stream line tags in view modes using the same tpl.
  if ($vars['element']['#field_type'] == 'taxonomy_term_reference') {
    $vars['theme_hook_suggestions'][] = 'field__ddbasic_tags__' . $view_mode;
  }

  // Ensure that all OG group ref field are the same.
  if ($field_name == 'ding_event_groups_ref' || $field_name == 'ding_news_groups_ref' || $field_name == 'og_group_ref') {
    $vars['theme_hook_suggestions'][] = 'field__og_group_ref';

    // Add classes to get label correctly formatted.
    foreach ($vars['items'] as $id => $item) {
      $vars['items'][$id]['#options'] = array(
        'attributes' => array(
          'class' => array(
            'label',
            'label_info',
          ),
        ),
      );
    }
  }

  // Clean up fields in search result view mode aka. search result page.
  if ($view_mode == 'search_result') {
    // Add suggestion that only hits the search result page.
    $vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . $view_mode;

    switch ($vars['element']['#field_name']) {
      case 'ting_author':
      case 'ting_abstract':
      case 'ting_subjects':
        $vars['classes_array'] = array('content');
        break;

      case 'ting_title':
        $vars['classes_array'] = array('heading');
        break;
    }
  }

  // Make suggestion for the availability on the search result page.
  if ($vars['element']['#field_type'] == 'ting_collection_types' &&
      $vars['element']['#formatter'] == 'ding_availability_with_labels') {
    $vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . 'search_result';
  }

  // Add class to library OG ref on staff profiles only.
  if ($vars['element']['#bundle'] == 'ding_staff_profile') {
    $staff_fields = array(
      'og_group_ref',
      'field_ding_staff_department',
      'field_ding_staff_email',
      'field_ding_staff_phone',
      'field_ding_staff_work_areas',
    );

    if (in_array($field_name, $staff_fields)) {
      $vars['theme_hook_suggestions'][] = 'field__ding_staff__content_field';

      // Ensure that department is not add label info.
      if ($field_name == 'field_ding_staff_department' || $field_name == 'og_group_ref') {
        foreach ($vars['items'] as $id => $item) {
          // This as little hack to make the user interface look better.
          $vars['items'][$id]['#options']['no_label'] = TRUE;
        }
      }
    }

    if ($field_name == 'og_group_ref') {
      $vars['classes_array'][] = 'field-name-ding-library-name';
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
 * Implements template_preprocess_user_profile().
 */
function ddbasic_preprocess_user_profile(&$variables) {
  $variables['user_profile']['summary']['member_for']['#access'] = FALSE;
  unset($variables['user_profile']['og_user_node']);
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

  // Filter classes.
  $element['#attributes']['class'] = ddbasic_remove_default_link_classes($element['#attributes']['class']);

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
  // Run classes array through our custom stripper.
  $vars['element']['#attributes']['class'] = ddbasic_remove_default_link_classes($vars['element']['#attributes']['class']);

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
      // If a user is logged in we change the menu item title.
      if (user_is_logged_in()) {
        $element['#title'] = 'My Account';
        $element['#attributes']['class'][] = 'topbar-link-user-account';
        $element['#localized_options']['attributes']['class'][] = 'topbar-link-user-account';
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

    default:
      $title_prefix = '<i class="icon-align-justify"></i>';
      $element['#localized_options']['attributes']['class'][] = 'topbar-link-menu';
      $element['#attributes']['class'][] = 'topbar-link-menu';
      break;
  }

   // For some unknown issue translation fails.
  $element['#title'] = t($element['#title']);

  $output = l($title_prefix . '<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Used to strip default class names from menu links.
 *
 * @param array $classes
 *   An array of class attributes.
 *
 * @return array
 *   Classes that are left.
 */
function ddbasic_remove_default_link_classes($classes) {
  if (!isset($classes)) {
    return FALSE;
  }

  // Remove classes.
  $remove = array();

  // Remove .leaf.
  if (theme_get_setting('ddbasic_classes_menu_leaf')) {
    $remove[] .= "leaf";
  }

  // Remove .has-children.
  if (theme_get_setting('ddbasic_classes_menu_has_children')) {
    $remove[] .= "has-children";
  }

  // Remove .collapsed, .expanded and expandable.
  if (theme_get_setting('ddbasic_classes_menu_collapsed')) {
    $remove[] .= "collapsed";
    $remove[] .= "expanded";
    $remove[] .= "expandable";
  }

  // Remove the classes.
  if ($remove) {
    $classes = array_diff($classes, $remove);
  }

  // Remove menu-mlid-[NUMBER].
  if (theme_get_setting('ddbasic_classes_menu_items_mlid')) {
    $classes = preg_grep('/^menu-mlid-/', $classes, PREG_GREP_INVERT);
  }

  return $classes;
}

/**
 * Allows us to add script plugins to the theme via theme settings.
 *
 * Ex. add a javascript depending on the settings in the theme.
 */
function ddbasic_load_plugins() {
  $theme_path = drupal_get_path('theme', 'ddbasic');

  // If sticky menus is enabled in the theme load it.
  if (theme_get_setting('main_menu_sticky')) {

    // Add variable to js so we can check if it is set.
    drupal_add_js(array('ddbasic' => array('main_menu_sticky' => theme_get_setting('main_menu_sticky'))), 'setting');
  }

  // If equalize is enabled in the theme load it.
  if (theme_get_setting('load_equalize')) {

    // Add the script.
    drupal_add_js($theme_path . '/scripts/equalize.min.js');

    // Add variable to js so we can check if it is set.
    drupal_add_js(array('ddbasic' => array('load_equalize' => theme_get_setting('load_equalize'))), 'setting');
  }
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
  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Implements hook_preprocess_ting_object().
 *
 * Adds wrapper classes to the different groups on the ting object.
 */
function ddbasic_process_ting_object(&$vars) {
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

        if (isset($content['group_holdings_available']) && $content['group_holdings_available']) {
          $vars['content']['holdings-available'] = array(
            '#prefix' => '<div class="ting-object-wrapper">',
            '#suffix' => '</div>',
            'content' => array(
              '#prefix' => '<div class="ting-object-inner-wrapper">',
              '#suffix' => '</div>',
              'details' => $content['group_holdings_available'],
            ),
          );
          unset($content['group_holdings_available']);
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
          // The reason for this is that drupal_render passes it to
          // element_children, which will sort the array by #weight if any
          // element has the key, or keep the array order if they doesn't. This
          // will seriously mess up the display, as the groups above doesn't
          // have a weight and can sink to the bottom, depending on the #weights
          // defined.
          $vars['content'] += array(
            'content' => $content,
          );
        }
        break;

      case 'ting_collection':
        // Assumes that field only has one value.
        foreach ($vars['content']['ting_entities'][0] as &$type) {
          $type['#prefix'] = '<div class="ting-collection-wrapper"><div class="ting-collection-inner-wrapper">' . $type['#prefix'];
          $type['#suffix'] = '</div></div>';
        }
        break;
    }
  }
}
