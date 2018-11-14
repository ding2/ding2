<?php

/**
 * @file
 * Template for "More links" block.
 */

?>
<div class="more-links">
  <ul>
    <?php foreach ($links as $link): ?>
      <li>
        <div class="more-link"><?php print $link; ?></div>
      </li>
    <?php
    endforeach;
    ?>
  </ul>
</div>
