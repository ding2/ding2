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
    <h3 class="title"><?php print $title; ?></h3>
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
