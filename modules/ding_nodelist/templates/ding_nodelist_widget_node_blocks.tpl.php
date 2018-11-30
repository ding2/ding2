<?php

/**
 * @file
 * Node blocks list widget template.
 */

?>
<?php if ($items): ?>
  <?php if (!empty($conf['title'])): ?>
    <h2 class="pane-title"><?php print $conf['title']; ?></h2>
  <?php endif; ?>
  <div class="<?php print $conf['classes'] ?>">
    <div class="ding_nodelist-items">
      <?php
      $i = 0;
      foreach ($items as $k => $node) {
        print theme($node->item_template, array(
          'item' => $node,
          'conf' => $conf,
          'row' => (int) ($i / 3),
          'column' => $i % 3,
        ));
        $i++;
      }
      ?>
    </div>
    <?php if (!empty($links)): ?>
      <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
