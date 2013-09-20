<?php

/**
 * @file field.tpl.php
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
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $title ?>:</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($groups as $ns => $relations): ?>
      <div class="field-item"><?php print render($relations); ?></div>
    <?php endforeach; ?>
  </div>
</div>
