<?php
/**
 * @file
 * Template to render the user status block.
 */

$link_attributes = array(
  'attributes' => array(
    'class' => 'menu-item',
  ),
  'html' => true,
);
?>
<ul class="system-user-menu">
  <li class="user-loans first">
    <?php
      $link_text_suffix = '&nbsp;<span class="user-amount">(' . $loan_count . ')</span>';
      print l(t('Loans') . $link_text_suffix, 'user/' . $user->uid . '/status', $link_attributes);
    ?>
  </li>
  <li class="user-reservations">
    <?php
      $link_text_suffix = '&nbsp;<span class="user-amount">(' . $reservation_count . ')</span>';
      print l(t('Reservations') . $link_text_suffix,'user/' . $user->uid . '/status/reservations', $link_attributes);
    ?>
  </li>
  <li class="user-debts">
    <?php
      $link_text_suffix = '&nbsp;<span class="user-amount">(' . $debt_count . ')</span>';
      print l(t('Debts') . $link_text_suffix, 'user/' . $user->uid . '/status/debts', $link_attributes);
    ?>
  </li>
  <li class="user-bookmarks last">
    <?php
      $link_text_suffix = '&nbsp;<span class="user-amount">(' . $bookmark_count . ')</span>';
      print l(t('Bookmarks') . $link_text_suffix, 'user/' . $user->uid . '/bookmarks', $link_attributes);
    ?>
  </li>
</ul>
