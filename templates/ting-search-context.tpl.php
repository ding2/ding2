<?php
/**
 * @file
 * Default theme implementation for displaying ting new materials results.
 *
 */
?>
<?php if ($columns) : ?>
  <div class="ting-search-context">
    <div class="group-blocks--inner  group-blocks--four">
      <?php foreach ($columns as $columns_class => $column) : ?>
        <div class="<?php print $columns_class ?>">
          <a href="<?php print $column['url'] ?>"> 
            <?php print $column['image'] ?>
          <h2>  <?php print $column['title'] ?> </h2></a>
        </div>
    <?php endforeach; ?>
    </div></div>
  <?php endif; ?>

    



