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
<div id="ting-subsearch-secondary" class="message-box search-field-in-content--message-tss">
  <div class="message-box--title">
    <?php print $message; ?>
  </div>
  <div class="message-box--list-items">
  <?php print $items; ?>
  </div>
  <div class="message-box--external-search">
    <a href="<?php print $secondary_link; ?>" target="_blank">
      <?php print $secondary_link_text; ?>
    </a>
  </div>
</div>
