<?php $close_button = drupal_render($elements['#close_button']); ?>

<div id="work-cover-<?php print $elements['#id'] ?>" class="work-cover"<?php 
  if (isset($elements['#no_image_style']))
  print $elements['#no_image_style'] 
?>>
  <div class="work-cover-image">
    <div class="<?php print( implode(' ', $elements['#classes'])); ?>">
      <?php print drupal_render($elements['#image']) ?>
    </div>
  </div>
  <div class="work-cover-selector clearfix">
    <?php print drupal_render($elements['#front_cover_large_link']) ?>
    <?php print drupal_render($elements['#back_cover_large_link']) ?>
  </div>
</div>

<div id="reveal-cover-large-<?php print $elements['#id'] ?>" class="reveal-modal reveal-cover-large" data-reveal="">
  <div class="reveal-cover-large-image"><?php print drupal_render($elements['#front_cover_large_image']) ?></div>
  <?php print $close_button ?>
</div>

<div id="reveal-cover-back-<?php print $elements['#id'] ?>" class="reveal-modal reveal-cover-back" data-reveal="">
  <div class="reveal-cover-back-image"><?php print drupal_render($elements['#back_cover_large_pdf']) ?></div>
  <?php print $close_button ?>
</div>
