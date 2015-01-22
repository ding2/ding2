<?php
/**
 * @file
 * Default template implementation of the individual items in the recommendation
 * list.
 *
 * Available variables:
 * - $creators: The creators of the recommendation as a comma separated list or
 *   FALSE if no creators where found.
 * - $link: Array with an uri and link title for the recommend Ting entity.
 * - $item: Ting entity with all information available about the recommended
 *   object.
 * - $zebra: The even/odd class.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 */
?>
<li class="<?php print $zebra; ?>">
  <a href="<?php print $link['uri']; ?>" title="<?php print $link['title']; ?>">
    <span class="title"><?php print $item->title; ?></span>
    <?php if ($creators) : ?>
      <span class="creators"><?php print $creators; ?></span>
    <?php endif; ?>
  </a>
</li>
