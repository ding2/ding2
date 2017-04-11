<?php

/**
 * @file
 * Displays holdings information.
 *
 * Available variables:
 *  - $holdings: Html showing detailed holdings information.
 *  - $total_count: Total amount of copies.
 *  - $reserved_count: Amount of reservations.
 *  - $ordered_count: Amount in acquisition.
 *  - $total_plus_ordered_count: Sum of total + amount in acquisition.
 *  - $reserved_text: Text description of amount of reservations.
 *  - $acquisition_text: Text Description of amount in acquisition.
 *  - $total_text: Text description of total + amount in acquisition.
 */
?>
<p><?php print "$total_text $reserved_text $acquisition_text"; ?></p>

<?php if (!empty($closest_loan)): ?>
  <p><?php print $closest_loan; ?></p>
<?php endif; ?>

<?php print render($holdings); ?>
