<?php

/**
 * @file
 * Secondary search item.
 *
 * @var $items
 * @var $message
 * @var $secondary_link
 * @var $secondary_link_text
 */
?>
<div id="ting-subsearch-secondary" class="ting-subsearch-seondary-message-box">
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
