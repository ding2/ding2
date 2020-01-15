<?php
/**
 * @file
 *
 * @var $content
 * @var $message
 * @var $bibdk_url
 * @var $bibdk_url_text
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
    <a href="<?php print $bibdk_url; ?>" target="_blank">
      <?php print $bibdk_url_text; ?>
    </a>
  </div>
</div>
