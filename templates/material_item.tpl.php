<?php
/**
 * @file
 *
 */
?>
<div class="material-item <?php print $zebra; ?>">
  <div class="left-column">
    <div class="item-checkbox"><?php print $checkbox; ?></div>
    <?php print $cover; ?>
  </div>
  <div class="right-column">
    <h3 id="<?php print $availability_id; ?>" class="item-title"><?php print $title; ?></h3>
    <?php if (isset($material_message)) : ?>
    <div class="<?php print $material_message['class']; ?>"><?php print $material_message['message']; ?></div>
    <?php endif; ?>
    <ul class="item-information-list">
      <?php foreach ($information as $info) : ?>
        <li class="item-information <?php isset($info['class']) ? print $info['class'] : print ''; ?>">
          <?php if (isset($info['label'])) : ?>
            <div class="item-information-label"><?php print $info['label']; ?>:</div>
          <?php endif; ?>
          <div class="item-information-data"><?php print $info['data']; ?></div>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
