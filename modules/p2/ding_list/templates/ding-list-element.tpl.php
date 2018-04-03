<?php

/**
 * @file
 * List element template.
 */

?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="ding-list-element__value">
    <?php print render($content['value']); ?>
  </div>
  <div class="ding-list-element__remove">
    <?php print render($content['remove']); ?>
  </div>
</div>
