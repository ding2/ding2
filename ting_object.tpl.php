<?php
// $Id$
/**
 * @file ting_object.tpl.php
 *
 * Template to render objects from the Ting database.
 *
 * Available variables:
 * - $object: The TingClientObject instance we're rendering.
 * - $content: Render array of content.
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php echo render($content['overview']); ?>
    <?php echo render($content['actions']); ?>
    <?php echo render($content['details']); ?>

    <?php echo render($content); ?>
</div>
