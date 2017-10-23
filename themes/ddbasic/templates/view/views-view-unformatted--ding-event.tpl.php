<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * Variables available:
 * - $title: The view title
 * - $rows: Array of view rows
 * - $classes_array: Array of classes for the rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <div class="group-separator">
    <div class="separator-title">
      <?php print $title; ?>
    </div>
<?php endif; ?>
  <div class="view-elements<?php if (isset($no_masonry) && !$no_masonry == TRUE): ?> js-masonry-view masonry-view<?php endif; ?>">
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
<?php if (!empty($title)): ?>
  </div>
<?php endif; ?>
