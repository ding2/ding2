<?php
/**
 * @file
 * Preprocess and Process Functions.
 *
 * 1. Rename each function and instance of "adaptivetheme_subtheme" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the
 *    function name will be "footheme_preprocess_hook". Tip - you can
 *    search/replace on "adaptivetheme_subtheme".
 * 2. Uncomment the required function to use.
 * 3. Read carefully, especially within adaptivetheme_subtheme_preprocess_html()
 *    , there are extra goodies you might want to leverage such as a very simple
 *    way of adding stylesheets for Internet Explorer and a browser detection
 *    script to add body classes.
 *
 * @see http://drupal.org/node/254940#variables-processor
 */

global $theme_key, $path_to_ddbasic_core;
$theme_key = $GLOBALS['theme_key'];
$path_to_ddbasic_core = drupal_get_path('theme', 'ddbasic');

// Includes frequently used theme functions that gets theme info, css files etc.
include_once $path_to_ddbasic_core . '/inc/functions.inc';


/**
 * Implements hook_preprocess_html().
 */
function ddbasic_preprocess_html(&$vars) {
  global $theme_key, $language;
  $theme_name = $theme_key;

  // Setup iOS logo if it's set.
  $vars['ios_logo'] = theme_get_setting('iosicon_upload');

  // Set variable for the base path.
  $vars['base_path'] = base_path();

  // Clean up the lang attributes.
  $vars['html_attributes'] = 'lang="' . $language->language . '" dir="' . $language->dir . '"';

  // Build an array of poly-filling scripts.
  $vars['polyfills_array'] = '';
  $vars['polyfills_array'] = ddbasic_load_polyfills($theme_name, $vars);

  // Load ddbasic plugins.
  ddbasic_load_plugins();

  // Add conditional CSS for IE8.
  drupal_add_css(path_to_theme() . '/css/ddbasic.ie8.css', array(
    'group' => CSS_THEME,
    'browsers' => array(
      'IE' => 'lte IE 8',
      '!IE' => FALSE,
    ),
    'weight' => 999,
    'preprocess' => FALSE,
  ));

  // Add conditional CSS for IE9.
  drupal_add_css(path_to_theme() . '/css/ddbasic.ie9.css', array(
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
  // This code is copied from Adaptive Theme, at_core/inc/process.inc.
  // It wraps the required polyfills scripts into a conditional comment.
  if (!empty($vars['polyfills_array'])) {
    $vars['polyfills'] = drupal_static('ddbasic_process_html_polyfills');
    if (empty($vars['polyfills'])) {
      $polyfills = array();
      foreach ($vars['polyfills_array'] as $key => $value) {
        foreach ($value as $k => $v) {
          $polyfills[$k][] = implode("\n", $v);
        }
      }
      $polyfills_scripts = array();
      foreach ($polyfills as $kv => $kvp) {
        $polyfills_scripts[$kv] = implode("\n", $kvp);
      }
      $vars['polyfills'] = ddbasic_theme_conditional_scripts($polyfills_scripts);
    }
  }
  else {
    $vars['polyfills'] = '';
  }

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
      $form['search_block_form']['#title_attribute'] = array('label-search');

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

  // Suggestions on panel pane.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $vars['pane']->panel;
}


/**
 * Implements theme_menu_tree().
 *
 * Addes wrapper clases for the main menu and secondary menu.
 */

// Main menu
function ddbasic_menu_tree__menu_block__1($vars) {
  return '<ul class="main-menu">' . $vars['tree'] . '</ul>';
}

// Secondary menu
function ddbasic_menu_tree__menu_block__2($vars) {
  return '<ul class="secondary-menu">' . $vars['tree'] . '</ul>';
}

// Sub menu
function ddbasic_menu_tree__menu_block__3($vars) {
  return '<ul class="sub-menu">' . $vars['tree'] . '</ul>';
}

// Tabs menu
function ddbasic_menu_tree__menu_tabs_menu($vars) {
  return '<ul class="topbar-menu">' . $vars['tree'] . '</ul>';
}

// System user menu
function ddbasic_menu_tree__user_menu($vars) {
  return '<ul class="system-user-menu">' . $vars['tree'] . '</ul>';
}

// User provider menu (status, loans, etc.).
function ddbasic_menu_tree__ding_user_frontend__ding_user_menu($vars) {
  return '<ul class="sub-menu">' . $vars['tree'] . '</ul>';
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
  // Opening hours on library list. but not on the search page.
  $path = drupal_get_path_alias();
  if (!(strpos($path, 'search', 0) === 0)) {
    $hooks = theme_get_registry(FALSE);
    if (isset($hooks['opening_hours_week']) && $variables['type'] == 'ding_library') {
      $variables['opening_hours'] = theme('opening_hours_week', array('node' => $variables['node']));
    }
  }

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
      $variables['ddbasic_event_location'] = $variables['content']['og_group_ref'];
    }

    // Add event date to variables. A render array is created based on the date
    // format "date_only".
    $event_date_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', array('label' => 'hidden', 'type' => 'date_default', 'settings' => array('format_type' => 'date_only', 'fromto' => 'both')));
    $variables['ddbasic_event_date'] = $event_date_ra[0]['#markup'];

    // Add event time to variables. A render array is created based on the date
    // format "time_only".
    $event_time_ra = field_view_field('node', $variables['node'], 'field_ding_event_date', array('label' => 'hidden', 'type' => 'date_default', 'settings' => array('format_type' => 'time_only', 'fromto' => 'both')));
    $variables['ddbasic_event_time'] = $event_time_ra[0]['#markup'];
  }

  // Add tpl suggestions for node view modes.
  if (isset($variables['view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'node__view_mode__' . $variables['view_mode'];
  }

  // Add "read more" links to event and news in search result view mode.
  if ($variables['view_mode'] == 'search_result') {
    switch ($variables['node']->type) {
      case 'ding_event':
        $more_link = array(
          '#theme' => 'link',
          '#text' => '<i class="icon-chevron-right"></i>',
          '#path' => 'node/' . $variables['nid'],
          '#options' => array(
            'attributes' => array(
              'title' => $variables['title'],
            ),
            'html' => TRUE,
          ),
          '#prefix' => '<div class="event-arrow-link">',
          '#surfix' => '</div>',
          '#weight' => 6,
        );

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;

      case 'ding_news':
        $more_link = array(
          '#theme' => 'link',
          '#text' => t('Read more'),
          '#path' => 'node/' . $variables['nid'],
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

//        <span class="news-link"><span><a href="/nyheder/anbefalinger/test-nyhed">Læs mere</a></span></span>

        $variables['content']['group_right_col_search']['more_link'] = $more_link;
        break;
    }
  }

  // For search result view mode move title into left col. group.
  if (isset($variables['content']['group_right_col_search'])) {
    $variables['content']['group_right_col_search']['title'] = array(
      '#theme' => 'link',
      '#text' => $variables['title'],
      '#path' => 'node/' . $variables['nid'],
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
      $vars['element']['#formatter'] == 'ding_availability_types') {
    $vars['theme_hook_suggestions'][] = 'field__' . $vars['element']['#field_type'] . '__' . 'search_result';
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
    // Add classes label and label-info.
    if (!isset($variables['options']['attributes']['class'])) {
      $variables['options']['attributes']['class'] = array();
    }
    $variables['options']['attributes']['class'][] = 'label';
    $variables['options']['attributes']['class'][] = 'label-info';
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
 * Implements theme_menu_link().
 */
function ddbasic_menu_link($vars) {
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
  $element['#localized_options']['html'] = true;

  $output = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
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

    case 'user':
      $title_prefix = '<i class="icon-user"></i>';
      // If a user is logged in, we change the menu item title.
      // @todo: change this to two menu items with access rules to hide them.
      if (user_is_logged_in()) {
        $element['#title'] = t('My Account');
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
  global $path_to_ddbasic_core;

  // If sticky menus is enabled in the theme load it.
  if (theme_get_setting('main_menu_sticky')) {

    // Add variable to js so we can check if it is set.
    drupal_add_js(array('ddbasic' => array('main_menu_sticky' => theme_get_setting('main_menu_sticky'))), 'setting');
  }

  // If equalize is enabled in the theme load it.
  if (theme_get_setting('load_equalize')) {

    // Add the script.
    drupal_add_js($path_to_ddbasic_core . '/scripts/equalize.min.js');

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
 * Return themed scripts in Conditional Comments.
 *
 * Since Drupal 7 does not (yet) support the 'browser' option in drupal_add_js()
 * Adaptivetheme provides a way to load scripts inside conditional comments.
 * This function will return a string for printing into a template, its
 * akin to a real theme_function but its not.
 *
 * @param array $ie_scripts
 *   An array of themed scripts.
 *
 * @return string
 *   Themed scripts.
 */
function ddbasic_theme_conditional_scripts($ie_scripts) {
  $themed_scripts = drupal_static(__FUNCTION__, array());
  if (empty($themed_scripts)) {
    $cc_scripts = array();

    foreach ($ie_scripts as $conditional_comment => $conditional_scripts) {
      $cc_scripts[] = '<!--[if ' . $conditional_comment . ']>' . "\n" . $conditional_scripts . "\n" . '<![endif]-->' . "\n";
    }
    $themed_scripts = implode("\n", $cc_scripts);
  }

  return $themed_scripts;
}


/**
 * Polyfill is used to enable HTML5 on browsers who doesn't natively support it.
 * Polyfill adds the missing functionality by 'filling' in scripts that add the
 * HTML5 functionality the browser doesn't offer.
 *
 * Return an array of filenames (scripts) to include.
 *
 * @param string $theme_name  :   Name of the theme.
 */
function ddbasic_load_polyfills($theme_name) {
  global $path_to_ddbasic_core;

  // Get the info file data.
  $info = ddbasic_get_info($theme_name);

  // Build an array of polyfilling scripts.
  $polyfills_array = drupal_static('ddbasic_preprocess_html_polyfills_array');
  if (empty($polyfills_array)) {
    // Info file loaded conditional scripts.
    $theme_path = drupal_get_path('theme', $theme_name);
    if (array_key_exists('ie_scripts', $info)) {
      foreach ($info['ie_scripts'] as $condition => $ie_scripts_path) {
        foreach ($ie_scripts_path as $key => $value) {
          $filepath = $theme_path . '/' . $value;
          $polyfills_array['info'][$condition][] = ddbasic_theme_script($filepath);
        }
      }
    }

    // Ddbasic Core Polyfills.
    $polly = '';
    $polly_settings_array = array(
      'load_html5js',
      'load_selectivizr',
      // loaded directly by polly_wants_a_cracker(), its never returned.
      'load_scalefixjs',
    );
    foreach ($polly_settings_array as $polly_setting) {
      $polly[$polly_setting] = theme_get_setting($polly_setting, $theme_name);
    }
    $backed_crackers = ddbasic_polly_wants_a_cracker($polly);
    foreach ($backed_crackers as $cupboard => $flavors) {
      foreach ($flavors as $key => $value) {
        $filepath = $path_to_ddbasic_core . '/' . $value;
        $polyfills_array['ddbasic'][$cupboard][] = ddbasic_theme_script($filepath);
      }
    }
  }

  return $polyfills_array;
}


/**
 * Polyfills.
 *
 * This function does two seperate operations. First it attaches a condition
 * to each Polyfill which can be either an IE conditional comment or 'all'.
 * Polyfills with 'all' are loaded immediatly via drupal_add_js(), those with
 * an IE CC are returned for further processing. This function is hard coded
 * to support only those scripts supplied by the core theme, if you need to load
 * a script for IE use the info file feature.
 *
 * @param array $polly
 *   Array of ?.
 */
function ddbasic_polly_wants_a_cracker($polly) {
  global $path_to_ddbasic_core;

  $baked_crackers = drupal_static(__FUNCTION__, array());
  if (empty($baked_crackers)) {
    if (in_array(1, $polly)) {

      $crackers = array();

      // HTML5 Shiv.
      if ($polly['load_html5js'] === 1) {
        $crackers['all'][] = 'scripts/html5shiv.js';
      }
      // Selectivizr.
      if ($polly['load_selectivizr'] === 1) {
        $crackers['all'][] = 'scripts/selectivizr-min.js';
      }
      // Scalefix.js.
      if ($polly['load_scalefixjs'] === 1) {
        $crackers['all'][] = 'scripts/scalefix.js';
      }

      // Load Polyfills.
      if (!empty($crackers)) {
        // "all" - no conditional comment needed, use drupal_add_js().
        if (isset($crackers['all'])) {
          foreach ($crackers['all'] as $script) {
            drupal_add_js($path_to_ddbasic_core . '/' . $script, array(
              'type' => 'file',
              'scope' => 'header',
              'group' => JS_THEME,
              'preprocess' => TRUE,
              'cache' => TRUE,
              )
            );
          }
        }
      }
    }
  }

  return $baked_crackers;
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
