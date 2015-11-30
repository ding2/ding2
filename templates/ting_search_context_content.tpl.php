<?php
/**
 * @file
 * Default theme implementation to display nodes related to search context.
 *
 * * Available variables:
 * - $node: A node that is related to the current search context.
 * - $image: If an
 *   The list-image of the node. Image style ting_search_context is used.
 * - $url: The node url.
 * - $title: The node title.
 */
?>

<li class="rs-carousel-item">
  <a href="<?php print $url; ?>">
    <div>
      <?php if(isset($image)): ?>
        <?php print render($image); ?>
      <?php endif; ?>
    </div>
    <h2><?php print render($title); ?></h2>
  </a>
</li>
