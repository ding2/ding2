<?php
/**
 * @file
 */
?>
<div class="<?php print $classes; ?>"
  data-transition="<?php print $transition; ?>"
  data-settings="<?php print htmlentities(json_encode($settings)); ?>"
  >
  <?php foreach ($tabs as $tab): ?>
  <div class="carousel-tab <?php print $tab['classes']; ?>"
   data-title="<?php print $tab['title']; ?>"
   data-offset="<?php print $tab['offset']; ?>"
   data-path="<?php print $tab['path']; ?>"
  >
    <div class="description"><?php print $tab['description']; ?></div>
    <ul class="carousel"><?php print $tab['content']; ?></ul>
  </div>
  <?php endforeach; ?>
</div>
