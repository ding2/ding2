<?php
/**
 * @file
 * Carousel list widget template.
 * Variables are:
 * $items - rendered items (HTML)
 * $conf - list configuration with:
 *  - classes - widget-specific CSS classes
 */
?>

<?php if ($items): ?>
  <div class="<?php print $conf['classes'] ?>">
    <?php if (!empty($conf['title'])): ?>
      <h2 class="ding_nodelist-title"><?php print $conf['title']; ?></h2>
    <?php endif; ?>
    <div class="ding_nodelist-items">
      <?php foreach($items as $item): ?>
        <?php print $item; ?>
      <?php endforeach; ?>
    </div>
    <div class="next-prev">
      <a class="prev" href="#"><span>prev</span></a>
      <a class="next" href="#"><span>next</span></a>
    </div>
    <div class="pagination"></div>
  </div>
<?php endif; ?>
