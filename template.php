<?php

/**
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "adaptivetheme_subtheme" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "adaptivetheme_subtheme".
 * 2. Uncomment the required function to use.
 * 3. Read carefully, especially within adaptivetheme_subtheme_preprocess_html(), there
 *    are extra goodies you might want to leverage such as a very simple way of adding
 *    stylesheets for Internet Explorer and a browser detection script to add body classes.
 */

global $theme_key, $path_to_ddbasic_core;
$theme_key = $GLOBALS['theme_key'];
$path_to_ddbasic_core = drupal_get_path('theme', 'ddbasic');


/**
 * Preprocess variables for html.tpl.php
 */
function ddbasic_preprocess_html(&$vars) {
  global $theme_key, $language;
  $theme_name = $theme_key;

  // Set variable for the base path
  $vars['base_path'] = base_path();

  // Clean up the lang attributes.
  $vars['html_attributes'] = 'lang="' . $language->language . '" dir="' . $language->dir . '"';

}

/**
 * alters forms.
 */
function ddbasic_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case 'user_login_block':
      unset($form['name']['#title']);
      $form['name']['#field_prefix'] = '<i class="icon-user"></i>';
      $form['name']['#attributes']['placeholder'] = t('Cpr- eller kortnummer:');
      $form['name']['#type'] = 'password';
      $form['pass']['#field_prefix'] = '<i class="icon-lock"></i>';
      $form['pass']['#attributes']['placeholder'] = t('Adgangskode:');
      unset($form['pass']['#title']);
      unset($form['links']);
      //Temporary hack to get rid of open id links
      unset($form['openid_links']);
      unset($form['#attached']['js']);
      break;
  }
}

/**
 * Implements hook_preprocess_panels_pane().
 *
 */
function ddbasic_preprocess_panels_pane(&$vars) {
  // Suggestions base on sub-type.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . str_replace('-', '__', $vars['pane']->subtype);

  // Suggestions on panel pane
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $vars['pane']->panel;
}


/**
 * Implements hook_preprocess_views_view_unformatted().
 *
 * Overwrite views row classes
 */
function ddbasic_preprocess_views_view_unformatted(&$vars) {

  // Class names for overwriting
  $row_first = "first";
  $row_last  = "last";

  $view = $vars['view'];
  $rows = $vars['rows'];

  // Set arrays
  $vars['classes_array'] = array();
  $vars['classes'] = array();

  // Variables
  $count = 0;
  $max = count($rows);

  // Loop through the rows and overwrite the classes, its importent that the
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

    if ( $vars['classes']  && $vars['classes'][$id] ){
      $vars['classes_array'][$id] = implode(' ', $vars['classes'][$id]);
    } else {
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
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ddbasic_preprocess_user_picture(&$variables) {
  // inject the class we need into the A tag of user_picture
  $variables['user_picture'] = str_replace('<a ', '<a class="span2 thumbnail" ', $variables['user_picture']);
  // inject the class we need into the IMG tag of user_picture
  $variables['user_picture'] = str_replace('<img ', '<img class="pull-left" ', $variables['user_picture']);
}

/**
 * Implements hook_preprocess_node().
 *
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function ddbasic_preprocess_node(&$variables, $hook) {
  // Add ddbasic_byline to variables
  $variables['ddbasic_byline'] = t('By: ');

  // Add ddbasic_event_location and ddbasic_place2book_tickets to variables (only for ding_event node template)
  if (isset($variables['content']['#bundle']) && $variables['content']['#bundle'] == 'ding_event') {
    $event_location = 'location';
    if (!empty($variables['content']['field_ding_event_location'][0]['#address']['name_line'])) {
      $event_location = $variables['content']['field_ding_event_location'][0]['#address']['name_line'] . '<br/>' . $variables['content']['field_ding_event_location'][0]['#address']['thoroughfare'] . ', ' . $variables['content']['field_ding_event_location'][0]['#address']['locality'];
    }
    else {
      /**
       *  @TODO: the full address wil have to be retrieved from the database
       */
      $event_location = render($variables['content']['field_ding_event_library'][0]);
    }
    $variables['ddbasic_event_location'] = $event_location;

    // Set a flag for existence of field_place2book_tickets
    $variables['ddbasic_place2book_tickets'] = (isset($variables['content']['field_place2book_tickets'])) ? 1: 0;
  }

  $tags_fields = array(
    'event',
    'news',
    'page',
  );
  foreach ($tags_fields as $tag_field) {
    // Add ddbasic_ding_xxx_tags  to variables.
    $variables['ddbasic_ding_' . $tags_field . '_tags'] = '';
    if (isset($variables['content']['field_ding_' . $tags_field . '_tags'])) {
      $ddbasic_tags = '';
      $items = $variables['content']['field_ding_' . $tags_field . '_tags']['#items'];
      if (count($items) > 0) {
        foreach ($items as $delta => $item) {
          $ddbasic_tags .= render($variables['content']['field_ding_' . $tags_field . '_tags'][$delta]);
        }
        $variables['ddbasic_ding_' . $tags_field . '_tags'] = $ddbasic_tags;
      }
    }
  }

  /**
   * @TODO Use date-formats defined in the backend, do not hardcode formats...
   *       ever
   */
  // Add updated to variables.
  $variables['ddbasic_updated'] = t('Updated: !datetime', array('!datetime' => format_date($variables['node']->changed, 'custom', 'l j. F Y')));

  // Modified submitted variable
  if ($variables['display_submitted']) {
    $variables['submitted'] = t('Submitted: !datetime', array('!datetime' => format_date($variables['created'], 'custom', 'l j. F Y')));
  }
}

/**
 * Implementing the ticketsinfo theme function (support for ding_place2book module)
 *
 * @TODO: Markup should not be hardcode into theme function as it makes it very
 *        hard to override.
 *
 */
function ddbasic_place2book_ticketsinfo($variables) {
  $output = '';
  $url = $variables['url'];
  $type = $variables['type'];

  switch ($type) {
    case 'event-over':
      $output = '<button class="btn btn-warning btn-large">' . t('The event has already taken place') . '</button>';
      break;
    case 'closed-admission':
      $output = '<button class="btn btn-warning btn-large">' . t('Not open for ticket sale') . '</button>';
      break;
    case 'no-tickets-left':
      $output = '<button class="btn btn-warning btn-large">' . t('Sold out') . '</button>';
      break;
    case 'order-link':
      $output = l(t('Book a ticket'), $url, array('attributes' => array('class' => array('btn', 'btn-primary', 'btn-large'))));
      break;
    default:
      $output = '';
      break;
  }

  return $output;
}

/**
 * Implements template_preprocess_field().
 */
function ddbasic_preprocess_field(&$vars, $hook) {
  // Get current view mode (teaser)
  $view_mode  =  $vars['element']['#view_mode'];
  $field_name =  $vars['element']['#field_name'];

  // Add suggestion for ddbasic specific field.
  $vars['theme_hook_suggestions'][] = 'field__' . 'ddbasic';

  // Add suggestion for ddbasic field with specific name.
  $vars['theme_hook_suggestions'][] = 'field__' . 'ddbasic_' . $field_name;

  // Add suggestion for ddbasic field in specific view mode.
  $vars['theme_hook_suggestions'][] = 'field__' . 'ddbasic_' . $view_mode;

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

    // Add class to availability list.

  }
}

/**
 * Implements ding_footer_preprocess().
 *
 * Find the right grid classes to add to the different footer columns.
 */
function ddbasic_preprocess_ding_footer_blocks(&$vars) {
  $number_of_blocks = count($vars['blocks']);
  switch ($number_of_blocks) {
    case 1:
      $classes = array('grid-full');
      break;

    case 2:
      $classes = array(
        'grid-8-left',
        'grid-8-right'
      );
      break;

    case 3:
      $classes = array(
        'grid-4-left',
        'grid-8-center',
        'grid-4-right'
      );
      break;
    case 4:
      $classes = array(
        'grid-4-left',
        'grid-4-center-left',
        'grid-4-center-right',
        'grid-4-right'
      );
      break;

    default:
      $classes = array('grid-full');
      break;
  }

  $vars['grid_classes'] = $classes;
}


/**
 *   OLD FUNCTION FROM LATTO MOVED HERE
 * 
 *  * Implements theme_form_alter().
 *
 * Adds two bootstrap classes to the default Drupal search form submit button.
 * Adds the default-value to the search field.
 *
 * @param type $vars
 *
function latto_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == "search_block_form") {
    $form['search_block_form']['#attributes']['title'] = t('Søg efter materialer fra biblioteket..');
    // Add a specify class to the search form to tell JavaScript this should
    // have the example functionallyty functionality.
    $form['search_block_form']['#attributes']['class'][] = 'has-example';
    
    $form['actions']['submit']['#attributes']['class'][] = 'btn';
    $form['actions']['submit']['#attributes']['class'][] = 'btn-large';
    $form['actions']['submit']['#attributes']['class'][] = 'btn-info';
  }
}

 * /**
 * Implement theme_breadcrumb().
 * 
 * Implemented for the purpose of changing >> to > in the default breadcrumb.
 *
function latto_breadcrumb ($variables) {
  $breadcrumb = $variables['breadcrumb'];
  
  if(!empty($breadcrumb)) {
    return '<div class="breadcrumb">' . implode(' > ', $breadcrumb) . '</div>';
  }
} 
 
 * /**
 * Implements hook_preprocess_user_picture().
 *
 * Override or insert variables into template user_picture.tpl.php
 *
 * @TODO: Is there an render array for this, str replacement is not cheap.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 *
function latto_preprocess_user_picture(&$variables) {
  // inject the class we need into the A tag of user_picture
  $variables['user_picture'] = str_replace('<a ', '<a class="span2 thumbnail" ', $variables['user_picture']);
  // inject the class we need into the IMG tag of user_picture
  $variables['user_picture'] = str_replace('<img ', '<img class="pull-left" ', $variables['user_picture']);
}
 * 
 * /**
 * Implements hook_preprocess_node().
 *
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 *
function latto_preprocess_node(&$variables, $hook) {
  // Add latto_byline to variables
  $variables['latto_byline'] = t('By: ');

  // Add latto_event_location and latto_place2book_tickets to variables (only for ding_event node template)
  if (isset($variables['content']['#bundle']) && $variables['content']['#bundle'] == 'ding_event') {
    $event_location = 'location';
    if (!empty($variables['content']['field_address'][0]['#address']['name_line'])) {
      $event_location = $variables['content']['field_address'][0]['#address']['name_line'] . '<br/>' . $variables['content']['field_address'][0]['#address']['thoroughfare'] . ', ' . $variables['content']['field_address'][0]['#address']['locality'];
    }
    else {
      // @TODO: the full address wil have to be retrieved from the database
      $event_location = render($variables['content']['group_audience'][0]);
    }
    $variables['latto_event_location'] = $event_location;

    // Set a flag for existence of field_place2book_tickets
    $variables['latto_place2book_tickets'] = (isset($variables['content']['field_place2book_tickets'])) ? 1: 0;
  }

  // Add latto_ding_content_tags  to variables.
  $variables['latto_ding_content_tags'] = '';
  if (isset($variables['content']['ding_content_tags'])) {
    $latto_ding_content_tags = '';
    $items = $variables['content']['ding_content_tags']['#items'];
    if (count($items) > 0) {
      foreach ($items as $delta => $item) {
        $latto_ding_content_tags .= render($variables['content']['ding_content_tags'][$delta]);
        if ($delta != count($items)-1) {
          $latto_ding_content_tags .=  ',&nbsp;';
        }
      }
      $variables['latto_ding_content_tags'] = t('Tags: ') . $latto_ding_content_tags;
    }
  }

  /**
   * @TODO Use date-formats defined in the backend, do not hardcode formats...
   *       ever
   *
  // Add updated to variables.
  $variables['latto_updated'] = t('Updated: !datetime', array('!datetime' => format_date($variables['node']->changed, 'custom', 'l j. F Y')));

  // Modified submitted variable
  if ($variables['display_submitted']) {
    $variables['submitted'] = t('Submitted: !datetime', array('!datetime' => format_date($variables['created'], 'custom', 'l j. F Y')));
  }
}
 * 

/**
 * Implementing the ticketsinfo theme function (support for ding_place2book module)
 *
 * @TODO: Markup should not be hardcode into theme function as it makes it very
 *        hard to override.
 
 *
function latto_place2book_ticketsinfo($variables) {
  $output = '';
  $url = $variables['url'];
  $type = $variables['type'];

  switch ($type) {
    case 'event-over':
      $output = '<button class="btn btn-warning btn-large">' . t('The event has already taken place') . '</button>';
      break;
    case 'closed-admission':
      $output = '<button class="btn btn-warning btn-large">' . t('Not open for ticket sale') . '</button>';
      break;
    case 'no-tickets-left':
      $output = '<button class="btn btn-warning btn-large">' . t('Sold out') . '</button>';
      break;
    case 'order-link':
      $output = l(t('Book a ticket'), $url, array('attributes' => array('class' => array('btn', 'btn-primary', 'btn-large'))));
      break;
    default:
      $output = '';
      break;
  }

  return $output;
}
 function hook_preprocess_field($vars){
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

    // Add class to availability list.

  }
 }
 */
