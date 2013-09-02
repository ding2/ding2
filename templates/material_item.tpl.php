<?php
/**
 * @file
 *
 */
?>
<div class="material_item">
  <div class="right">
    <?php print $checkbox; ?>
    <?php print $cover; ?>
  </div>
  <div class="left">
    <strong><?php print $title; ?></strong>
    <ul class="information">
      <?php foreach ($information as $info) : ?>
        <li class="<?php print $info['class']; ?>">
          <span class="label"><?php print $info['label']?></span>:
          <?php print $info['data']; ?>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
