<<<<<<< HEAD
<div class="<?php print $classes; ?>">
  <?php
  // We need to include the preface, or the openeing_hours module will trigger an
  // error in JavaScript.
  if (!empty($preface)):
    // print $preface;
  endif;
  ?>
=======
<?php
/**
 * @file
 * Template for rendering opening hours week.
 *
 * ddbasic specific variables:
 * - $table: Table of opening hours
 */
?>
<div class="opening-hours-week">
>>>>>>> Fixing TODO's from core team. Commit adds file descriptions, variable lists and function descriptions. Deletes unused files and code.
  <?php print render($table); ?>
</div>
