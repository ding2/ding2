<?php

/**
 * @file
 * Default template for ting subsearch secondary message box.
 *
 * Available variables:
 *   - $items: An array of ting_subsearch_secondary message box list items.
 *   - $message: The suggestion message to show in the message box.
 *   - $secondary_link: The search link to bibliotek.dk.
 *   - $secondary_link_text: The link text for bibliotek.dk search link.
 *   - $position: The position of the message box. Possible values: 'before' or
 *     'after' the search result.
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
