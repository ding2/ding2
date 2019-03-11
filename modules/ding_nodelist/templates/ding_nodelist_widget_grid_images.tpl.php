<?php

/**
 * @file
 * Node blocks list widget template.
 */
?>
<?php if ($items): ?>
    <div class="<?php print $conf['classes'] ?>">
        <div class="ding_nodelist-items">
          <?php
          $items = array_slice($items, 0, count($items));
          foreach ($items as $k => $node) {
            print theme($node->item_template, [
              'item' => $node,
              'conf' => $conf,
            ]);
          }
          ?>
        </div>
      <?php if (!empty($links)): ?>
        <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
      <?php endif; ?>
    </div>
<?php endif; ?>
