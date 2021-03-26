<?php

/**
 * @file
 * Minimal display list widget template.
 *
 * Variables are:
 * $items - node items (objects)
 * $conf - list configuration with:
 *  - classes - widget-specific CSS classes
 *  - title - list title
 * $links - list of links (array)
 */
?>
<?php if ($items): ?>
  <div class="<?php print $conf['classes'] ?>">
    <div class="ding_nodelist-minimal-items">
      <?php
      $index = 0;
      foreach ($items as $k => $node) {
        $index++;
        $row_classes = ($index % 2 == 0 ? 'even' : 'odd');
        print theme($node->item_template, array(
          'item' => $node,
          'conf' => $conf,
          'class' => $row_classes,
        ));
      }
      ?> 
    </div>
    <?php if (!empty($links)): ?>
      <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
