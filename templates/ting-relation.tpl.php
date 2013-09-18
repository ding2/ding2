<?php
/**
 * @file
 * Template to render ting_releation content.
 */
?>
<div class="meta">
  <h4><?php print $title ?></h4>
  <?php if (isset($abstract)) :?>
    <div class="abstract"><?php print $abstract; ?></div>
  <?php endif; ?>
  <?php if (isset($online)) :?>
    <a class="online_url" target='_blank' href="<?php print $online['url'] ?>"><?php print $online['title']; ?></a>
  <?php endif; ?>
</div>
