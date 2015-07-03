<?php
/**
 * @file
 * Default theme implementation to display nodes related to search context.
 *
 *
 * * Available variables:
 * - $node: A node that is related to the current search context.
 * - $image: The list-image of the node. Image style ting_search_context is used.
 * - $url: The node url.
 * - $title: The node title.
 *
 */
?>

<li class="rs-carousel-item">
  <a href="<?php print $url; ?>" class="rs-carousel-item-image"><?php print $image; ?></a>
  <a href="<?php print $url; ?>" class="rs-carousel-item-title"><?php print $title; ?></a>
</li>


