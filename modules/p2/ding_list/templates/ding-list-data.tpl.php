<?php

/**
 * @file
 * Ding List Data template.
 */
 
?>
<div class="ding-list-data__note">
  <?php print $note; ?>
</div>
<div class="ding-list-data__info">
  <div class="ding-list-info">
    <?php print render($info_items); ?>
  </div>
  <div class="ding-list-buttons">
    <?php print render($button_items); ?>
  </div>
</div>
