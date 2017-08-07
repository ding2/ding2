<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */

// Check for well-formed html - position, phone og email may be null.
$name_title_wrapper = $contact_wrapper = FALSE;

foreach ($fields as $id => $field) {

  if (($id == 'field_ding_staff_surname' || $id == 'field_ding_staff_position') && !$name_title_wrapper) {
    print '<div class="staff-name-title">';
    $name_title_wrapper = TRUE;
  }

  if (($id == 'field_ding_staff_phone' || $id == 'field_ding_staff_email') && !$contact_wrapper) {
    if ($name_title_wrapper) {
      print "</div>";
    }
    print '<div class="staff-contact">';
    $contact_wrapper = TRUE;
  }

  if (!empty($field->separator)) {
    print $field->separator;
  }

  print $field->wrapper_prefix;
  print $field->label_html;
  print $field->content;
  print $field->wrapper_suffix;

}

if ($contact_wrapper) {
  print "</div>";
}

?>
