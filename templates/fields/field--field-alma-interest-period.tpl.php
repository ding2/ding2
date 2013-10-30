<?php

/**
 * @file field.tpl.php
 *
 * Ensure that the field value it translated. It should be but it's not.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
      <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print t(render($item)); ?></div>
    <?php endforeach; ?>
  </div>
</div>
