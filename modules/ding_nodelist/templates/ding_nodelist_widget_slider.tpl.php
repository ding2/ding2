<?php

/**
 * @file
 * Slider list widget template.
 */
?>
<?php if ($items): ?>
    <div class="<?php print $conf['classes'] ?>">
      <?php if (!empty($links)): ?>
        <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
      <?php endif; ?>
        <ul class="ding_nodelist-items">
          <?php
          foreach ($items as $node) {
            print theme($node->item_template, ['item' => $node]);
          }
          ?>
        </ul>
        <div class="next-prev">
            <a class="prev" data-pane-id="<?php print $conf['unique_id']; ?>" href="#"><span>prev</span></a>
            <a class="next" data-pane-id="<?php print $conf['unique_id']; ?>" href="#"><span>next</span></a>
        </div>
    </div>
<?php endif; ?>
