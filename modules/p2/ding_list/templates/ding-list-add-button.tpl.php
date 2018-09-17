<?php

/**
 * @file
 * Ding List Add Button template.
 */
?>
<?php if (!empty($buttons['#links'])) : ?>
  <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
    <?php if (empty($single_link)): ?>
      <?php print render($title_prefix); ?>
      <a href="#" class="trigger"><?php print $title; ?></a>
      <?php print render($title_suffix); ?>

      <div class="content"<?php print $content_attributes; ?>>
        <div class="wrapper">
          <div class="inner">
            <h2><?php print t('Your lists'); ?></h2>
            <div class="close"><?php print t('Close'); ?></div>
            <?php print render($buttons); ?>
          </div>
        </div>
      </div>

    <?php else : ?>
      <?php print render($buttons); ?>
    <?php endif; ?>
  </div>
<?php endif; ?>
