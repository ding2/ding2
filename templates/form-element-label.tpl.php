<?php

/*
 * @file
 * DDBasic's theme implementation to display form element labels.
 *
 * See includes/form.inc for the theme function this template overrides.
 *
 * Returns HTML for a form element label and required marker.
 *
 * Form element labels include the #title and a #required marker. The label is
 * associated with the element itself by the element #id. Labels may appear
 * before or after elements, depending on theme_form_element() and
 * #title_display.
 *
 * Variables:
 * - element: An associative array containing the properties of the element.
 *   Properties used: #required, #title, #id, #value, #description.
*/

// If title and required marker are both empty, output no label.
if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
  return '';
}

// If the element is required, a required marker is appended to the label. A required marker will not be added on edit-name and edit-pass fields
$required = (!empty($element['#required']) && $element['#id'] != 'edit-name' && $element['#id'] != 'edit-pass') ? theme('form_required_marker', array('element' => $element)) : '';

$title = filter_xss_admin($element['#title']);

$attributes = array('class' => array());

// Style the label as class option to display inline with the element.
if ($element['#title_display'] == 'after') {
  $attributes['class'][] = 'option';
}
// Show label only to screen readers to avoid disruption in visual flows.
elseif ($element['#title_display'] == 'invisible') {
  $attributes['class'][] = 'element-invisible';
}
elseif (isset($element['#title_attribute']) && is_array($element['#title_attribute'])) {
  $attributes['class'][] = implode(' ', $element['#title_attribute']);
}

if (!empty($element['#id'])) {
  $attributes['for'] = $element['#id'];

  // Add ddbasic-specific classes
  if ($element['#id'] == 'edit-name') {
    $attributes['class'][] = 'label-user';
  } elseif ($element['#id'] == 'edit-pass') {
    $attributes['class'][] = 'label-password';
  }
}
?>
<?php print ' <label' . drupal_attributes($attributes) . '>' . t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n"; ?>