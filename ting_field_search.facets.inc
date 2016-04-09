<?php

/**
 * @file
 *
 * Contains hooks and function that modifies the Ding facetbrowser based on the
 * active profile.
 */

/**
 * Helper function to determine if facets should be altered.
 */
function _ting_field_search_alter_facets() {
  $profile = ting_field_search_profile_is_active();
  if ($profile && $profile->config['facets']['use_facets']) {
    return $profile;
  }
  return FALSE;
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_field_search_form_ding_facetbrowser_form_alter(&$form, &$form_state) {
  if ($profile = _ting_field_search_alter_facets()) {
    // Get the facets returned from the datawell.
    $search_result = drupal_static('ting_search_results');
    if (empty($search_result->facets)) {
      return;
    }
    $facets = $search_result->facets;

    // Build a base URI for all the facet terms including any existing facet
    // parameters added manually. We would like to use 'facets[]' as key for
    // all the facets, but Drupal functions output 'facets[0], facets[1], ..'
    global $base_url;
    $base_term_uri = $base_url . '/' . request_path();
    $facet_parameters = array();
    $parameters = array();
    $parameters = drupal_get_query_parameters(NULL, array('q', 'page'));
    // We'll just pass the parameters array through the helper to ensure all
    // parameters are added to the query.
    ting_field_search_append_query($parameters, $profile);
    if (!empty($parameters['facets'])) {
      $facet_parameters = $parameters['facets'];
      foreach ($facet_parameters as $key => $facet) {
        $facet_parameters[$key] = 'facets[]=' . rawurlencode($facet);
      }
      $base_term_uri .= '?' . implode('&', $facet_parameters);

      // Reset facet parameters and remove it from general parameters, so the
      // variables can be used later.
      $facet_parameters = $parameters['facets'];
      unset($parameters['facets']);
    }

    // Profile facet settings
    $profile_facets = ting_field_search_facets_load($profile->pid);
    $count = 1;
    $facet_count = $profile->config['facets']['facet_count'];

    foreach ($profile_facets as $name => $profile_facet) {
      $facet = isset($facets[$name]) ? $facets[$name] : FALSE;

      // No need to do anything if the profile facet wasn't returned.
      if ($facet && count($facet->terms)) {
        // Get the element name - i.e. the part of the facet name after the '.'
        $element_name = explode('.', $name);
        $element_name = end($element_name);
        $facet_class = ($count > $facet_count) ? 'js-hidden' : 'js-visible';

        $form[$name] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($profile_facet->title),
          '#weight' => $profile_facet->weight,
          '#attributes'  => array(
            'id' => str_replace('.', '-', $name),
            'data' => array($name),
            'count' => count($facet->terms),
            'class' => array($facet_class),
          ),
        );

        _ting_field_search_sort_terms($facet->terms, $profile_facet->sorting);

        $selected = array();
        $not_selected = array();
        $default_values = array();

        foreach ($facet->terms as $term_name => $term_count) {
          $facets_string = $name . ':' . $term_name;
          $is_selected = FALSE;

          // If the facet is already selected, we mark if for deletion and add
          // it to default values for this facet checkboxes element.
          if (in_array($facets_string, $facet_parameters)) {
            $is_selected = TRUE;
            $default_values[] = $term_name;
            $facets_string = '-' . $facets_string;
          }

          $term_parameters = $parameters;
          $term_parameters['facets'] = array('' => $facets_string);
          $options = array(
            'html' => TRUE,
            'query' => $term_parameters,
            'attributes' => array('title' => $term_name),
          );
          $term_title = _ting_field_search_format_term_name($term_name, $term_count);
          $term_title .= '<span class="count">(' . $term_count . ')</span>';
          if ($is_selected) {
            $selected[$term_name] = l($term_title, $base_term_uri, $options);
          }
          else {
            $not_selected[$term_name] = l($term_title, $base_term_uri, $options);
          }
        }

        $form[$name][$element_name] = array(
          '#type' => 'checkboxes',
          '#options' => $selected + $not_selected,
          '#default_value' => $default_values,
        );
      }

      $count++;
    }

    // Lastly, remove any facets added to the form in Ding facetbrowser module,
    // but not configured on the active profile.
    foreach (variable_get('ding_facetbrowser_facets', array()) as $default_facet) {
      $name = $default_facet['name'];
      if (!isset($profile_facets[$name]) && isset($form[$name])) {
        unset($form[$name]);
      }
    }

    // Pass the profile's term count to ding_facetbrowser JS.
    $form['#attached']['js'][] = array(
      'data' => array(
        'ding_facetbrowser' => array(
          'number_of_terms' => $profile->config['facets']['term_count'],
        ),
      ),
      'type' => 'setting',
    );
  }
}

/**
 * Helper function to format term name title, if it's too long to display in
 * the facetbrowser window.
 *
 * Note: This code is copied from the form builder in Ding facetbrowser, and it
 * tries to estimate the length of the string while accounting for 'short'
 * letters such as 'l' and 'i'. It seems to do an OK job, and we use it here to
 * be consistent with the default look. Otherwise, a solution with CSS would
 * probably be preferred.
 * See: ding_facetbrowser_form()
 */
function _ting_field_search_format_term_name($term_name, $term_count) {
  $substr_length = 22
    + substr_count(drupal_substr($term_name, 0, 20), 'l')
    + substr_count(drupal_substr($term_name, 0, 20), 'i')
    - drupal_strlen((string)$term_count);
  if (drupal_strlen($term_name) > $substr_length) {
    return drupal_substr($term_name, 0, $substr_length) . '...';
  }
  return $term_name;
}

/**
 * Helper function to sort facet terms based on profile sorting setting.
 * Code copied from Ding facetbrowser module.
 */
function _ting_field_search_sort_terms(&$terms, $sorting) {
  switch ($sorting) {
    case 'default':
      // Uses the default ranking sorting from the well.
      break;
    case 'alphabetical':
      ksort($terms);
      break;
    case 'alphabetical_reverse':
      krsort($terms);
      break;
    case 'numeric':
      ksort($terms, SORT_NUMERIC);
      break;
    case 'numeric_reverse':
      krsort($terms, SORT_NUMERIC);
  }
}
