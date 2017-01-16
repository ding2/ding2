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
</div>
