<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $node_url; ?>" <?php if(!empty($background_image)){?>style="background-image: url(<?php print $background_image; ?>)"<?php } ?>>
    <div class="group-text">
      <h3 class="title"><?php print $title; ?></h3>
      <?php print render($content['field_ding_group_lead']); ?>
    </div>
  </a>
</article>