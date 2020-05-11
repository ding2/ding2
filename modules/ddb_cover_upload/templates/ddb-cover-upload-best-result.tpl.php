<?php
/**
 * @file
 * Template for showing best result.
 */
?>

<div class="container border border-gray">
  <div class="row">
    <div class="col-12">
      <h2 class="center"><?php print t('Getting the best result')?></h2>
    </div>
  </div>
  <div class="row">
    <div class="col-3">
      <div class="media center">
        <div class="media-icon">
          <?php print file_get_contents($path . '/images/reflections.svg'); ?>
        </div>
        <div class="media-body">
          <h3><?php print t('Avoid reflections')?></h3>
          <p><?php print t('Avoid reflections by removing insertions from covers')?></p>
        </div>
      </div>
    </div>
    <div class="col-3">
      <div class="media center">
        <div class="media-icon">
          <?php print file_get_contents($path . '/images/crop.svg'); ?>
        </div>
        <div class="media-body">
          <h3><?php print t('Crop')?></h3>
          <p><?php print t('Crop the image to remove edges around the image')?></p>
        </div>
      </div>
    </div>
    <div class="col-3">
      <div class="media center">
        <div class="media-icon">
          <?php print file_get_contents($path . '/images/rotate.svg'); ?>
        </div>
        <div class="media-body">
          <h3><?php print t('Rotate')?></h3>
          <p><?php print t('Rotate the image to turn it the right way')?></p>
        </div>
      </div>
    </div>
    <div class="col-3">
      <div class="media center">
        <div class="media-icon">
          <?php print file_get_contents($path . '/images/size.svg'); ?>
        </div>
        <div class="media-body">
          <h3><?php print t('Size')?></h3>
          <p><?php print t('Images with a vertical resolution less than 1000px may appear gritty')?></p>
        </div>
      </div>
    </div>
  </div>
</div>
