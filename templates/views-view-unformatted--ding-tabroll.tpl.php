<?php
/**
 * @file
 * This template defines the basic structure for the frontpage tabroll (with
 * support for responsive design.)
 *
 * @ingroup views_templates
 */
?>
<div class="ding-tabroll-wrapper">
  <div id="ding-tabroll" class="ding-tabroll">
    <ul class="ui-tabs-nav">
      <?php foreach ($view->result as $i => $result) : ?>
        <li class="ui-tabs-nav-item count-<?php print $i; ?>"><a href="#fragment-<?php print $i; ?>"><span><?php print $result->node_title; ?></span></a></li>
      <?php endforeach; ?>
    </ul>
  
    <?php foreach ($rows as $id => $row): ?>
      <div id="fragment-<?php print $id; ?>" class="ui-tabs-panel<?php if ($id >= "1") { print " ui-tabs-hide"; } ?>">
        <?php print $row; ?>
      </div>
    <?php endforeach; ?>
  </div>
  
  <!-- Used for responsive -->
  <select class="ding-tabroll-select-tabs">
    <?php foreach ($view->result as $id => $result) : ?>
      <option class="tabroll-tabs-item"><?php print $result->node_title ?></option>
    <?php endforeach; ?>
  </select>
</div>
