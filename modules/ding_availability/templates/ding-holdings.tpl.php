<?php
/**
 * @file
 * Displays holdings information
 *
 * Available variables:
 *  - $holdings: Html showing detailed holdings information.
 *  - $total_count: Total amount of copies.
 *  - $reserved_count: Amount of reservations.
 *  - $ordered_count: Amount in acquisition.
 *  - $total_plus_ordered_count: Sum of Total + Amount in acquisition
 */

$reserved_text = format_plural($reserved_count, 'There is 1 user in queue to loan the material.', 'There are @count users in queue to loan the material.');
$acquisition_text = '';
if ($ordered_count) {
  $acquisition_text = format_plural($ordered_count, '1 copy in acquisition.', '@count copies are in acquisition.', array('@count' => $ordered_count));
}
$total_text = format_plural($total_plus_ordered_count, 'We have 1 copy.', 'We have @count copies.', array('@count' => $total_plus_ordered_count));
?>
<p><?php print "$total_text $reserved_text $acquisition_text"; ?></p>

<?php if (!empty($closest_loan)): ?>
  <p><?php print $closest_loan; ?></p>
<?php endif; ?>

<?php print render($holdings); ?>
