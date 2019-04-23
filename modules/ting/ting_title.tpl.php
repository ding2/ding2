<?php
/**
 * @file
 * Template to render a title from a Ting collection.
 *
 * Available variables:
 * - $collection: The Ting collection
 * - $title: The collection title
 * - $type: The material type of the collection
 * - $prefix_type: Whether to prefix the title with the material type
 * - $language: The language of the collection
 * - $show_language: Whether to show the collection language or not
 * - $uri: Data when rendering the title as a link
 */
?>
<?php if ($prefix_type) : ?>
  <span class="search-result--heading-type js-toggle-info-container"><?php print $type ?></span>
<?php endif ?>
<h2>
    <?php print $title ?>
    <?php if ($show_language): ?>
      (<?php print $language ?>)
    <?php endif; ?>
</h2>
