<?php
/**
 * @file
 * Default implementation full text view.
 */
?>

<div class="ting-fulltext-wrap">
  <?php if (isset($variables['element']['#fields']['title'])) : ?>
    <h1 class="page-title"> <?php print $variables['element']['#fields']['title']; ?></h1>
  <?php endif; ?>

  <div class="author">
    <?php if(!empty($variables['element']['#fields']['firstname'])) : ?>
       <span class="label"><?php print t('Author'); ?>:</span>
       <?php print $variables['element']['#fields']['firstname'] . '&nbsp;' . $variables['element']['#fields']['surname']; ?>
    <?php endif; ?>
  </div>

  <?php if (isset($variables['element']['#fields']['subject'])) : ?>
    <div class="subjects">'
      <?php foreach ($variables['element']['#fields']['subject'] as $key => $subject) : ?>
       <span class="subject">'.$subject.'</div>';
      <?php endforeach; ?>
    </div>
  <?php endif; ?>

  <?php if (isset($variables['element']['#fields']['section'])) :?>
    <?php foreach ($variables['element']['#fields']['section'] as $key => $section) : ?>
      <section>
        <?php if (isset($section['title'])) : ?>
          <h4 class="title"><?php print $section['title']; ?></h4>
        <?php endif; ?>
        <?php if (isset($section['para'])) : ?>
          <?php foreach ($section['para'] as $para) : ?>
            <div class="paragraph"><?php print $para; ?></div>
          <?php endforeach; ?>
        <?php endif; ?>
      </section>
    <?php endforeach; ?>
  <?php endif; ?>
</div>
