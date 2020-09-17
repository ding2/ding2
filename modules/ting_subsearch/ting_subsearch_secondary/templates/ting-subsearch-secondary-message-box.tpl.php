<?php

/**
 * @file
 * Default template for ting subsearch secondary message box.
 *
 * @var $items
 * @var $message
 * @var $secondary_link
 * @var $secondary_link_text
 * @var $position
 */

?>
<div class="ting-subsearch-seondary-message-box <?php print $position; ?>">
  <div class="ting-subsearch-seondary-message-box--title">
    <?php print $message; ?>
  </div>
  <div class="ting-subsearch-seondary-message-box--list-items">
    <?php print $items; ?>
  </div>
  <div class="ting-subsearch-seondary-message-box--external-search">
    <a href="<?php print $secondary_link; ?>" target="_blank">
      <?php print $secondary_link_text; ?>
    </a>
  </div>
</div>
