<?php
/**
 * @file
 * Displays holdings information
 *
 * Available variables:
 *  - $holdings: Html showing detailed holdings information.
 *  - $total_count: Total amount of copies.
 *  - $reserved_count: Amount of reservations.
 */

$total_text = format_plural($total_count, 'We have 1 copy.', 'We have @count copies.', array('@count' => $total_count));
$reserved_text = format_plural($reserved_count, 'There is 1 user in queue to loan the material.', 'There are @count users in queue to loan the material.');
?>
<p><?php print "$total_text $reserved_text"; ?></p>
<?php print render($holdings); ?>
