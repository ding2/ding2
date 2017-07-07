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
    <?php echo render($content); ?>
</div>
