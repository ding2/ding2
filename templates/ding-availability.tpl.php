<?php
/**
 * @file
 * Displays holdings information
 *
 * Available variables:
 * - $status: Human readable status text (available, on loan, not reservable, unavailable).
 * - $reservable: Boolean.
 * - $available: Boolean.
 * - $holdings: Html showing detailed holdings information.
 * - $total_count: Total amount of copies.
 * - $reservable_count: Amount of copies that are reservable.
 * - $reserved_count: Amount of reservations.
 *
 */

$total_text = format_plural($total_count, 'We have 1 copy (@reservable_count reservable).', 'We have @count copies (@reservable_count reservable).', array('@reservable_count' => $reservable_count));
$reserved_text = format_plural($reserved_count, 'There is 1 user in queue to loan the material', 'There are @count users in queue to loan the material');
?>
<h2><?php print t('Holdings'); ?> </h2>
<p><?php print "$total_text $reserved_text"; ?></p>
<?php print $holdings; ?>
