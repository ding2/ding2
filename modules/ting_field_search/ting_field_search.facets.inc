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
  $profile = ting_field_search_get_active_profile();
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

    // Number of visible facets by default. Need to keep count to enforce this.
    $count = 1;
    $facet_count = $profile->config['facets']['facet_count'];
    // Keep a record of the facets we've added.
    $profile_facets = array();
    foreach ($profile->facets as $profile_facet) {
      $name = $profile_facet['name'];
      $profile_facets[$name] = $profile_facet;
      $facet = isset($facets[$name]) ? $facets[$name] : FALSE;

      // No need to do anything if the profile facet wasn't returned.
      if ($facet && count($facet->terms)) {
        // Get the element name - i.e. the part of the facet name after the '.'
        $element_name = explode('.', $name);
        $element_name = end($element_name);
        $facet_class = ($count > $facet_count) ? 'js-hidden' : 'js-visible';

        $form[$name] = array(
          '#type' => 'fieldset',
          '#title' => check_plain($profile_facet['title']),
          '#weight' => $profile_facet['weight'],
          '#collapsible' => TRUE,
          '#collapsed' => $count > $facet_count,
          '#attributes'  => array(
            'id' => str_replace('.', '-', $name),
            'data' => array($name),
            'count' => count($facet->terms),
            'class' => array($facet_class),
          ),
        );

        ding_facetbrowser_sort_terms($facet->terms, $profile_facet['sorting']);

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
          $term_title = ding_facetbrowser_format_term_name($term_name, $term_count);
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
