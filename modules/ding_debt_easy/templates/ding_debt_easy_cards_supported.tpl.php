<?php
/**
 * @file
 * Template to render the supported cards information.
 *
 * Available variables:
 *  - $cards: The cards supported index by name and values are links to images of the cards.
 */
?>
<div id="cards-supported" class="clearfix">
  <h3><?php print t('Cards supported', ['context' => 'ding_debt_easy']); ?></h3>
  <?php foreach ($cards as $name => $image_url): ?>
    <p class="card">
      <img class="card-logo" alt="<?php print $name; ?>" src="<?php print $image_url; ?>" />
      <span class="card-name"><?php print $name; ?></span>
    </p>
  <?php endforeach; ?>
</div>
