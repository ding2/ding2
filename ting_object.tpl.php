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
<div id="ting-item-<?php print $object->localId; ?>" class="ting-item ting-item-full">
  <?php echo render($content['overview']); ?>

  <?php echo render($content['details']); ?>

  <?php echo render($content); ?>
</div>
