<?php

/**
 * @file
 * Rolltab widget template.
 *
 * This template defines the basic structure for the rolltab widget (with
 * support for responsive design.)
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
      <div class="ding_nodelist-rolltab-wrapper ding-tabroll-wrapper">
        <div class="ding_nodelist-rolltab ding-tabroll">
          <ul class="ui-tabs-nav">
            <?php foreach ($items as $i => $result) : ?>
              <li class="ui-tabs-nav-item count-<?php print $i; ?>">
                <a href="#fragment-<?php print $i; ?>">
                  <span
                    datasrc="<?php print url('node/' . $result->nid, array('absolute' => TRUE)); ?>">
                    <?php print $result->title; ?>
                  </span>
                </a>
              </li>
            <?php endforeach; ?>
          </ul>

          <?php foreach ($items as $id => $row): ?>
            <div id="fragment-<?php print $id; ?>" class="ui-tabs-panel
            <?php
            if ($id >= "1") {
              print " ui-tabs-hide";
            };
            ?>
            ">
              <?php print theme($row->item_template, array(
                'item' => $row,
                'conf' => $conf,
              )); ?>
            </div>
          <?php endforeach; ?>
        </div>

        <!-- Used for responsive -->
        <select class="ding_nodelist-rolltab-select-tabs ding-tabroll-select-tabs">
          <?php foreach ($items as $id => $result) : ?>
            <option class="nodelist-tabs-item">
              <?php print $result->title; ?>
            </option>
          <?php endforeach; ?>
        </select>
      </div>
    </div>
    <?php if (!empty($links)): ?>
      <?php print theme('ding_nodelist_more_links', array('links' => $links)); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
