<?php

/**
 * @file
 * List element template.
 */

?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="ding-list-element__value">
    <?php
    hide($content['remove']);
    print render($content);
    ?>
  </div>
  <div class="ding-list-element__remove">
    <?php print render($content['remove']); ?>
  </div>
</div>
