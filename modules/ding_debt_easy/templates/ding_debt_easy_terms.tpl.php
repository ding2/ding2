<?php
/**
 * @file
 *
 */
?>
<div id="terms-of-sale">
  <h3><?php print t('Terms and conditions of sale', ['context' => 'ding_debt_easy'])?></h3>
  <p>
    <?php if (!empty($terms)): ?>
      <?php print $terms; ?>
    <?php endif; ?>
    <?php if (!empty($url)): ?>
      <a href="<?php print $url; ?>" target="_blank"><?php print t('Read the Terms and conditions of sale at this page', ['context' => 'ding_debt_easy'])?></a>
    <?php endif; ?>
  </p>
</div>
