<?php
/**
 * @file
 * Template to render the user status block.
 */
?>
<ul class="menu">
  <li class="user-loans"><?php print l(t('Loans'), 'user/' . $user->uid . '/status'); ?><span class="user-amount">(<?php print $loan_count; ?>)</span></li>
  <li class="user-reservations"><?php print l(t('Reservations'),'user/' . $user->uid . '/status/reservations'); ?><span class="user-amount">(<?php print $reservation_count; ?>)</span></li>
  <li class="user-debts"><?php print l(t('Debts'), 'user/' . $user->uid . '/status/debts'); ?><span class="user-amount">(<?php print $debt_count; ?>)</span></li>
  <li class="user-bookmarks"><?php print l(t('Bookmarks'), 'user/' . $user->uid . '/bookmarks'); ?><span class="user-amount">(<?php print $bookmark_count; ?>)</span></li>
</ul>
