<div <?php if (!empty($css_id)) { print 'id="' . $css_id . '"'; } ?> class="<?php echo $classes; ?> ding-single-layout">
  <div class="content-wrapper">
    <div class="content-inner">
      <?php print render($content['content']); ?>
    </div>
  </div>
</div>
