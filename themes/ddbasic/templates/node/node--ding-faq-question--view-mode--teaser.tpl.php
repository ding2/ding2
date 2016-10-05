<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $node_url; ?>">
    <?php print render($content['field_ding_faq_list_image']); ?>
    <div class="text">
      <h3 class="title"><?php print $title; ?></h3>
      <?php print render($content['field_ding_faq_lead']); ?>
    </div>
    <div class="buttons">
      <div class="read-more"><?php print t('Read more'); ?></div>
    </div>
  </a>
</article>