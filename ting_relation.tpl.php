<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
   <h2><?php print($type_title); ?></h2>
   <h3><?php print($title); ?></h3>
   <div><?php print($content); ?></div>
   <?php if ($online_url): ?>
   <div><?php print($online_url); ?></div>
   <?php endif; ?>
</div>
