<?php
/**
 * @file
 * Terms and usage template.
 *
 * Available variables:
 *  - $terms: The terms as written.
 *  - $url: No terms this URL my link to a terms page.
 */
?>
<div id="terms-of-sale">
  <h3><?php print t('Terms and conditions of sale', ['context' => 'ding_debt_easy'])?></h3>
  <p>
    <?php if (!empty($terms) && empty($url)): ?>
      <?php print $terms; ?>
    <?php endif; ?>
    <?php if (!empty($url)): ?>
      <a href="<?php print url($url); ?>" target="_blank"><?php print t('Read the Terms and conditions of sale at this page', ['context' => 'ding_debt_easy'])?></a>
    <?php endif; ?>
  </p>
</div>
