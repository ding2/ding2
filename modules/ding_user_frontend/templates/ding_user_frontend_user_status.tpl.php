<?php
/**
 * @file
 * Template to render the user status block.
 */
?>
<a class="user-status <?php print $status['class']; ?>" href="<?php print $status['link']; ?>">
    <span class="user-status-amount"><?php print $status['count']; ?></span>
    <span class="user-status-label"><?php print $status['label']; ?></span>
</a>
