<?php

/**
 * @file
 * Defoult carousel template.
 *
 * Available variables:
 * - $tabs: Individual carousels.
 * - $transition: Transition effect when switching tab.
 * - $slick_settings: Settings for the Slick library.
 */
?>
<div class="<?php print $classes; ?>"
  data-transition="<?php print $transition; ?>"
  data-settings="<?php print htmlentities(json_encode($slick_settings)); ?>"
  >
  <?php print render($tabs); ?>
</div>
