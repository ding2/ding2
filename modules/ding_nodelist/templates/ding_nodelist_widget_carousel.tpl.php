<?php

/**
 * @file
 * Carousel list widget template.
 *
 * Variables are:
 * $items - rendered items (HTML)
 * $conf - list configuration with:
 *  - classes - widget-specific CSS classes.
 */

?>
<?php if ($items): ?>
  <div class="<?php print $conf['classes'] ?>">
    <div class="ding_nodelist-items">
      <?php
      foreach ($items as $node) {
        print theme($node->item_template, array(
          'item' => $node,
          'conf' => $conf,
        ));
      }
      ?>
    </div>
    <div class="next-prev">
      <a class="prev" href="#" aria-label="<?php print t('Previous page'); ?>"><span><?php print t('prev'); ?></span></a>
      <a class="next" href="#" aria-label="<?php print t('Next page'); ?>"><span><?php print t('next'); ?></span></a>
    </div>
    <div class="pagination"></div>
    <?php if (!empty($links)): ?>
      <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
