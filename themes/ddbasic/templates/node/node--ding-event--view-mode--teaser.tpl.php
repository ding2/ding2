<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <a href="<?php print $node_url; ?>">
    
    <div class="inner">
      <div class="background">
        <div class="button"><?php print t('Read more'); ?></div>
      </div>
      <div class="event-text">
        <div class="info-top">
          <div class="type"><?php print t('Event'); ?></div>
          <div class="info-dash">-</div>
          <?php print render($content['field_ding_event_category']); ?>
        </div>
        <div class="date"><?php print $event_date; ?></div>
        <div class="title-and-lead">
          <h3 class="title"><?php print $title; ?></h3>
          <?php print render($content['field_ding_event_lead']); ?>
        </div>
        <div class="info-bottom">
          <div class="library"><?php print render($content['og_group_ref']); ?></div>
          <div class="date-time"><?php print $event_time; ?></div>
          <div class="price"><?php print $event_price; ?></div>
        </div>
      </div>
    </div>
    <?php 
      if (!empty($event_background_image)) {
        print '<div class="event-list-image" style="background-image:url(' . $event_background_image . ');"' . $image_title . '></div>';
      }
    ?>
  </a>
</article>