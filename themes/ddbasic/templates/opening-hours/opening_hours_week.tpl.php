<div class="<?php print $classes; ?>">
  <?php
  // We need to include the preface, or the openeing_hours module will trigger an
  // error in JavaScript.
  if (!empty($preface)):
    // print $preface;
  endif;
  ?>
  <?php print render($table); ?>
</div>
