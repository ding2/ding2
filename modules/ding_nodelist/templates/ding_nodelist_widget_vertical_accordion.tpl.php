<?php
/**
 * @file
 * Simple list widget template.
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
    <?php if (!empty($conf['title'])): ?>
      <h2 class="ding_nodelist-title"><?php print $conf['title']; ?></h2>
    <?php endif; ?>
    <div class="ding_nodelist-items va-wrapper">
      <?php
      foreach ($items as $node) {
        print theme($template, array('item' => $node, 'conf' => $conf));
      }
      ?>
    </div>
  </div>
<?php endif; ?>
