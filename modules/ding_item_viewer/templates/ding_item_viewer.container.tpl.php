<?php
/**
 * @file
 * Template file for viewer container.
 *
 * Variables:
 *   $url - URL to AJAX handler.
 *   $preload_image - Image tag for "loading.." spinner.
 */
?>
<div id="ding-item-viewer-<?php echo $hash; ?>" class="ding-item-viewer" data-hash="<?php echo $hash; ?>">
  <span class="ding-item-viewer-queries"></span>
  <div class="ding-item-viewer-preloader">
    <?php echo $preload_image; ?>
  </div>
</div>
