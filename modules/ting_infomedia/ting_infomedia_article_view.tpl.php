<?php

/**
 * @file
 * Teplate for rendering Infomedia articles.
 */
?>
<div  class="infomedia-article">
  <div class="infomedia-image">
    <?php print theme('image', array('path' => drupal_get_path('module', 'ting_infomedia') . '/images/ting_infomedia_logo.jpg')); ?>
  </div>
  <?php echo $variables['element']['#markup']; ?>
</div>
