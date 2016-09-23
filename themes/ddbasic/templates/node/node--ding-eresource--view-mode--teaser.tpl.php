<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $node_url; ?>">

    <?php print render($content['field_ding_eresource_list_image']); ?>

    <div class="text">
      <h3 class="title"><?php print $title; ?></h3>
      <?php print render($content['field_ding_eresource_lead']); ?>
    </div>
  </a>
  <div class="buttons">
    <?php print l(t('Read more'), $node_url, array('attributes' => array('class' => array('read-more')))); ?>
    <?php if (!empty($link_url)) { ?>
      <a href="<?php print $link_url; ?>" class="log-on" target="_blank"><?php print t('Log on'); ?></a>
    <?php } ?>
  </div>

</article>