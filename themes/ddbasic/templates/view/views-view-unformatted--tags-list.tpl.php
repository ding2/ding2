<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * Ddbasic specific variables:
 * - $type_class: Content type class.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <div class="group-separator <?php print $type_class; ?>">
    <div class="group-inner">
      <div class="separator-title">
        <?php print $title; ?>
      </div>
<?php endif; ?>
      <div class="view-elements js-masonry-view">
        <div class="view-elements-inner">
          <?php foreach ($rows as $id => $row): ?>
            <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
              <?php print $row; ?>
            </div>
          <?php endforeach; ?>
        </div>
        <div class="grid-sizer"></div>
        <div class="grid-gutter"></div>
      </div>
    </div>
  <?php if (!empty($title)): ?>
  </div>
  <?php endif; ?>
