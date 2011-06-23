<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
   <h2><?php print render($type_title); ?></h2>
   <h3><?php print render($title); ?></h3>
   <div><?php print render($content); ?></div>
   <?php if ($online_url): ?>
     <div><?php print render($online_url); ?></div>
   <?php endif; ?>
</div>
