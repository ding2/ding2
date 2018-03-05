<?php
/**
 * @file
 * Default template for grid image campaign item.
 *
 * Variables:
 *  $image
 *  $title
 *  $description
 *  $link
 *  $options.
 */
?>
<div class="ding-campaign-grid-item">
  <div class="media"></div>
  <div class="media">
    <a href="<?php print $link; ?>" <?php print (!empty($options)) ? 'target="_blank"' : ''; ?>>
      <?php print $image; ?>
      <div class="media__body">
        <?php if (!empty($description)): ?>
          <div class="ding-campaign-grid-description"><?php print $description; ?></div>
        <?php endif; ?>
      </div>
    </a>
  </div>
  <h2 class="ding-campaign-grid-title"><?php print l($title, $link, $options); ?></h2>
</div>
