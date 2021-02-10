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
?>

<div class="section-groups"<?php print $attributes; ?>>
  <a href="<?php print url('taxonomy/term/' . $row->tid); ?>" aria-labelledby="<?php print 'link-id-' . $row->tid; ?>"<?php print drupal_attributes($link_attributes); ?>>
    <div class="group-text">
      <h3 id="<?php print 'link-id-' . $row->tid; ?>" class="title"><?php print $row->taxonomy_term_data_name; ?></h3>
      <?php if (!empty($row->taxonomy_term_data_description)) : ?>
      <div class="section-description">
        <?php print drupal_render($row->field_field_ding_sections_teaser[0]['rendered']); ?>
      </div>
      <?php endif; ?>
    </div>
  </a>
</div>
