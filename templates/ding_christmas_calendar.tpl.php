<?php
/**
 * @file
 * Represents a template for displaying Christmas calendar.
 */
$a = 1;
?>
<div class="calendar-summary">
  <?php print $summary; ?>
</div>
<div class="calendar-body">
  <?php print $body; ?>
</div>
<div id="ding-christmas-calendar-content" style="background-image: url(<?php print $background;?>)">
  <?php print $table ?>
</div>
