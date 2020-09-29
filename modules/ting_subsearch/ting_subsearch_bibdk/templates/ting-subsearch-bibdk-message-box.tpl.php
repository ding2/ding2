<?php

/**
 * @file
 * Default template for ting subsearch bibdk message box.
 *
 * Available variables:
 *   - $items: ting_subsearch_bibdk message box list items.
 *   - $message: The suggestion message to show in the message box.
 *   - $bibdk_link: The search link to bibliotek.dk.
 *   - $bibdk_link_text: The link text for bibliotek.dk search link.
 *   - $position: The position of the message box. Possible values: 'before' or
 *     'after' the search result.
 */
?>
<div class="ting-subsearch-bibdk-message-box <?php print $position; ?>">
  <div class="ting-subsearch-bibdk-message-box--title">
    <?php print $message; ?>
  </div>
  <div class="ting-subsearch-bibdk-message-box--list-items">
    <?php print render($items); ?>
  </div>
  <div class="ting-subsearch-bibdk-message-box--external-search">
    <a href="<?php print $bibdk_link; ?>" target="_blank">
      <?php print $bibdk_link_text; ?>
    </a>
  </div>
</div>
