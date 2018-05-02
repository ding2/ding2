<?php

/**
 * @file
 * List template.
 */

?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!empty($title)): ?>
    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
<?php
endif;
?>

  <?php print render($content); ?>
</div>
