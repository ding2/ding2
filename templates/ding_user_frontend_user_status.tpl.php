<?php
/**
 * @file
 * Template to render the user status block.
 */
?>
<div id="ding-user-loan-amount"><div class="content">
  <span class="label"><?php print l(t('Loans:'), 'user/' . $user->uid . '/status'); ?></span>
  <span class="amount">(<?php print $loan_count; ?>)</span>
</div></div>

<div id="ding-user-reservation-amount"><div class="content">
  <span class="label"><?php print l(t('Reservations:'),'user/' . $user->uid . '/status/reservations'); ?></span>
  <span class="amount">(<?php print $reservation_count; ?>)</span>
</div></div>

<div id="ding-user-debt-amount"><div class="content">
  <span class="label"><?php print l(t('Debts:'), 'user/' . $user->uid . '/status/debts'); ?></span>
  <span class="amount">(<?php print $debt_count; ?>)</span>
</div></div>

