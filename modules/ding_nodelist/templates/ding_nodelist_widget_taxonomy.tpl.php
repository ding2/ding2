<?php

/**
 * @file
 * Slider list widget template.
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
    <div class="ding_nodelist-items">
      <?php
      $groups = array();
      foreach ($items as $key => $node) {
        if (!isset($groups[$node->date])) {
          $groups[$node->date] = array($node);
        }
        else {
          $groups[$node->date][] = $node;
        }
      }
      foreach ($groups as $group) {
        $group[0]->has_header = TRUE;
        foreach ($group as $k => $v) {
          print theme($group[$k]->item_template, array(
            'item' => $group[$k],
            'conf' => $conf,
          ));
        }
      }
      ?>
    </div>
    <?php if (!empty($links)): ?>
      <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
