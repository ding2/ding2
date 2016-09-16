<?php
/**
 * @TODO Missing description
 */
?>
<div class="opening-hours-week">
  <?php
  // We need to include the preface, or the openeing_hours module will trigger an
  // error in JavaScript.
  if (!empty($preface)):
    // print $preface;
  endif;
  ?>
  <?php print render($table); ?>
</div>
