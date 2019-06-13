<?php

/**
 * @file
 * Template file for consent banner customized with close button.
 *
 * When overriding this template it is important to note that jQuery will use
 * the following classes to assign actions to buttons:
 *
 * agree-button      - agree to setting cookies
 * find-more-button  - link to an information page
 *
 * Variables available:
 * - $message:  Contains the text that will be display within the pop-up
 * - $agree_button: Label for the primary/agree button. Note that this is the
 *   primary button. For backwards compatibility, the name remains agree_button.
 * - $disagree_button: Contains Cookie policy button title. (Note: for
 *   historical reasons, this label is called "disagree" even though it just
 *   displays the privacy policy.)
 * - $secondary_button_label: Contains the action button label. The current
 *   action depends on whether you're running the module in Opt-out or Opt-in
 *   mode.
 * - $primary_button_class: Contains class names for the primary button.
 * - $secondary_button_class: Contains class names for the secondary button
 *   (if visible).
 */

?>
<div>
  <div class="popup-content info">
    <div class="close"></div>
    <div id="popup-text">
      <?php print $message ?>
      <?php if ($disagree_button) : ?>
        <button type="button" class="find-more-button eu-cookie-compliance-more-button"><?php print $disagree_button; ?></button>
      <?php endif; ?>
    </div>
    <div id="popup-buttons">
      <button type="button" class="<?php print $primary_button_class; ?>"><?php print $agree_button; ?></button>
      <?php if ($secondary_button_label) : ?>
        <button type="button" class="<?php print $secondary_button_class; ?>" ><?php print $secondary_button_label; ?></button>
      <?php endif; ?>
    </div>
  </div>
</div>
