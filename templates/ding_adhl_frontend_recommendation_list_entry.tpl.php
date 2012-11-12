<?php
/**
 * @file
 *
 */
?>
<a href="<?php echo url($recommendation['url']); ?>" title="<?php print $recommendation['link_title']; ?>">
  <span class="title"><?php print $recommendation['title']; ?></span>
  <?php if (!empty($recommendation['creators_str'])) : ?>
    <span class="creators"><?php print $recommendation['creators_str']; ?></span>
  <?php endif; ?>
</a>