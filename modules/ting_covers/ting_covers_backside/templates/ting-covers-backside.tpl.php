<?php
/**
 * @file
 *  Template for backside popup.
 */
?>

<div id="reveal-cover-back-<?php print $local_id ?>" class="reveal-modal reveal-cover-back" data-reveal="">
  <div class="reveal-cover-back-image">
    <object data="<?php print $backside_uri; ?>?page=1&amp;view=Fit" type="application/pdf" width="590" height="925">
      <p>It appears you don\'t have a PDF plugin for this browser.
        No biggie... you can <a href="<?php print $backside_uri; ?>">click here to download the PDF file.</a></p>
    </object>
  </div>
  <a class="reveal-cover close-reveal-modal">&#215;</a>
</div>
