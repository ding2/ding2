<?php

/**
 * @file
 * Default template for wayfinding marker popup.
 */
?>
<div class="map-info-wrapper">
  <div class="map-popover">
    <button id="toggleDetailsBtn" class="map-popover__toggle-information">
      <svg width="12" height="auto" viewBox="0 0 320 512" aria-hidden="true" data-prefix="fas" data-icon="angle-down" class="svg-inline--fa fa-angle-down fa-w-10" xmlns="http://www.w3.org/2000/svg"><path fill="currentColor" d="M143 352.3L7 216.3c-9.4-9.4-9.4-24.6 0-33.9l22.6-22.6c9.4-9.4 24.6-9.4 33.9 0l96.4 96.4 96.4-96.4c9.4-9.4 24.6-9.4 33.9 0l22.6 22.6c9.4 9.4 9.4 24.6 0 33.9l-136 136c-9.2 9.4-24.4 9.4-33.8 0z"/></svg>
    </button>
    <div id="mapPopoverDetails" class="map-popover__top">
      <div class="map-popover__left">
        <div class="map-popover__image">
          <img src="<?php print $cover_url ?>" alt="Placehold image">
        </div>
      </div>
      <div class="map-popover__right">
        <h1 class="map-popover__title"><?php print $title ?></h1>
        <p class="map-popover__author"><?php print $author ?></p>
        <?php if ($route): ?>
        <button class="map-popover__btn"><?php print t('Route') ?></button>
        <?php endif; ?>
      </div>
    </div>
    <div class="map-popover__bottom">
      <div class="map-popover__path">
        <p><?php print $placement ?></p>
      </div>
    </div>
  </div>
</div>
