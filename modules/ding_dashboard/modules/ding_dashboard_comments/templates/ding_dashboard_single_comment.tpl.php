<?php
/**
 * @file
 *
 * Generic template file for editorial comments block.
 */
?>

<div class="editorial-comment">
  <p class="info">
    <span class="by"><?php print t('By') . ' ' . $user;?></span>
    <span class="when"> <?php print t('at') . ' ' . $date;?></span>
  </p>
  <p class="comment">
    <?php print $comment; ?>
  </p>
  <?php if ($comment_l2) { ?>
  <p class="comment">
    <?php print $comment_l2; ?>
  </p>
  <?php } ?>
</div>
