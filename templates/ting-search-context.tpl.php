<?php
/**
 * @file
 * Default theme implementation for displaying related content.
 *
 * @see template_preprocess_ting_search_context()
 */
?>
<?php if ($columns) : ?>
  <div class="ting-search-context-blocks--wrapper">
    <div class="ting-search-context-blocks--inner  ting-search-context-blocks--four">
      <?php foreach ($columns as $columns_class => $column) : ?>
        <div class="<?php print $columns_class ?>">
          <a href="<?php print $column['url'] ?>">
          <?php print $column['image'] ?><h2 class="heading"><?php print $column['title'] ?></h2></a>
        </div>
    <?php endforeach; ?>
    </div></div>
  <?php endif; ?>





