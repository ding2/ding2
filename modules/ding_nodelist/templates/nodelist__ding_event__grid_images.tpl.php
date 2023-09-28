<?php

/**
 * @file
 * Ding event node blocks template.
 */
?>

<div class="grid-images-event-item nodelist-item"<?php print $attributes; ?>>
    <a href="<?php print url('node/' . $item->nid); ?>">
        <div class="grid-images-item-image background-image-styling-16-9"
             style="background-image: url(<?php print $item->image; ?>)"></div>
        <div class="grid-images-item-text">
            <h2 class="grid-images-item-title">
              <?php print $item->title; ?>
            </h2>
          <?php print render($item->lead); ?>
        </div>
    </a>
</div>
