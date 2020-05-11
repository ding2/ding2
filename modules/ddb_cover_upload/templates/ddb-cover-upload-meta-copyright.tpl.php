<?php
/**
 * @file
 * Template for showing meta copyright information.
 *
 * Available variables:
 *   - $copyright_text: HTML of copyright text as added from settings.
 */
?>
<div>
  <h3><?php print t('Copyright information');?></h3>
  <p>
    <?php print t('It is your responsibility to make sure that all rights for use of this image are upheld');?>
  </p>
  <p>
    <div><?php print t('See what rules apply'); ?>:</div>
    <a href="#" class="opener-modal" data-dialog="dialog-copyright"><?php print t('Conditions for use of cover service'); ?></a>
  </p>
</div>
<div tabindex="-1" role="dialog-copyright" style="display: none;">
  <div id="dialog-copyright" class="ui-dialog-content ui-widget-content" data-title="<?php print t('Conditions for use of cover service'); ?>">
    <?php print $copyright_text; ?>
  </div>
</div>
