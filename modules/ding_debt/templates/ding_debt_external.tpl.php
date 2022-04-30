<?php
/**
 * @file
 * Default template for external debts.
 */
?>
<div id="ding-debt-debts-form">
  <?php if ($has_internal && !empty($title)): ?>
  <h2><?php print $title ?></h2>
  <?php endif; ?>
  <?php
    print render($debts)
  ?>
  <div class="total-amount">
    <div id="edit-external-total" class="form-item form-type-item">
      <?php print t('Total') ?>: <span class="amount"><?php print number_format($total, 2, ',', ' ') ?> <?php print t('Kr') ?></span>
    </div>
  </div>

  <?php if (!empty($extra_information['value'])): ?>
  <div class="debt-body">
    <?php print check_markup($extra_information['value'], $extra_information['format']) ?>
  </div>
  <?php endif; ?>

  <?php if ($button['enabled']): ?>
  <div class="pay-buttons form-wrapper" id="edit-external-buttons">
    <?php print l($button['text'], $button['url'], $options = array(
      'attributes' => [
        'role' => 'button',
        'class' => 'external-payment',
        'target' => '_blank',
      ],
    )) ?>
  </div>
  <?php endif; ?>
</div>

