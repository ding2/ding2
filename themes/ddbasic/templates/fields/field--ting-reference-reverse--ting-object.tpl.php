<?php

/**
 * @file field--ting-reference-reverse--ting-object.tpl.php
 * Changes the ting reference reverse field on the ting object to match search
 * result layout.
 *
 * @see field.tpl.php
 * @see template_preprocess_field()
 * @see theme_field()
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>

  <div class="ting-reference-reverse-list">
    <div class="search-results">
      <ul class="list floated">
        <?php foreach ($items as $delta => $item): ?>
          <li class="list-item search-result"><?php print render($item); ?></li>
        <?php endforeach; ?>
      </ul>
    </div>
  </div>
</div>
