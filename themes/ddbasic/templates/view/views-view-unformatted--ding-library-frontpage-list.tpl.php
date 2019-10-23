<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($view->result as $id => $result) : ?>
    <?php $background_image = file_create_url($result->file_managed_file_usage_uri); ?>
    <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
      <article class="node node-ding-library node-view-teaser"<?php print $attributes; ?>>
        <a href="<?php print url('node/' . $result->nid); ?>"  <?php if(!empty($background_image)){?>style="background-image: url(<?php print $background_image; ?>)"<?php
        } ?>>
          <div class="group-text">
            <h3 class="title">
              <?php print $result->node_title; ?>
            </h3>

            <?php print $result->field_field_ding_library_lead[0]['rendered']; //dump($result->field_field_ding_library_lead);die; ?>
          </div>
        </a>
      </article>
    </div>
<?php endforeach; ?>
