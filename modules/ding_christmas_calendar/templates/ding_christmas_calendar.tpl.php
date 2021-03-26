<?php
/**
 * @file
 * Represents a template for displaying Christmas calendar.
 */
?>
<div class="calendar-summary">
  <?php print $summary; ?>
</div>
<div class="calendar-body">
  <?php print $body; ?>
</div>
<div id="ding-christmas-calendar-content" class="<?php print $classes;?>"
     style="background-image: url(<?php print $background;?>)">
  <?php print $content ?>

</div>
<div class="calendar-popup">
  <div class="future-day-popup">
    <strong><?php print t('Hov Hov') ?></strong>
    <div><?php print t('Do not cheat! You can not open the door yet') ?></div>
  </div>
</div>
