<?php
/**
 * @file
 * Slider list widget template.
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
    <div class="legend">
      <?php if (!empty($conf['title'])): ?>
        <h2 class="ding_nodelist-title"><?php print $conf['title']; ?></h2>
      <?php endif; ?>
      <?php foreach ($links as $key => $bottom) : ?>
        <span>
          <?php print l(t($bottom['text']), $bottom['links']); ?>
        </span>
      <?php endforeach; ?>
    </div>
    <ul class="ding_nodelist-items">
      <?php
      foreach ($items as $node) {
        if ($conf['sorting']=='event_date') {
          print theme($template, array('item' => array_shift(array_values($node))));
        }
        else {
          print theme($template, array('item' => $node));
        }
      }
      ?>
    </ul>
    <div class="next-prev">
      <a class="prev" href="#"><span>prev</span></a>
      <a class="next" href="#"><span>next</span></a>
    </div>
  </div>
<?php endif; ?>
