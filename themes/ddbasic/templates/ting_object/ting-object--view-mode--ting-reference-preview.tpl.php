<?php

/**
 * @file
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print render($content['ting_cover']); ?>
  <?php print render($content); ?>
  <div class="ting-object-new-in-list"><?php print t('New in list'); ?></div>
</div>
