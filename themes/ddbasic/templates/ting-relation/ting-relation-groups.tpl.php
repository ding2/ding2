<?php

/**
 * @file
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 *   - $title: The item title.
 *   - $label_hidden: Whether the label display is set to 'hidden'.
 *   - $classes: String of classes that can be used to style contextually
 *     through
 *   - $groups: The relations grouped together based on type.
 *
 * Other variables:
 *   - $element['#object']: The entity to which the field is attached.
 *   - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 *   - $element['#field_name']: The field name.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable
 */
?>
<?php foreach ($groups as $ns => $relations): ?>
  <div id="<?php print $ns ?>" class="ting-object-wrapper field-group-format field-group-div collapsible collapsed  speed-fast effect-none"<?php print $attributes; ?>>
    <?php print render($relations); ?>
  </div>
<?php endforeach; ?>
