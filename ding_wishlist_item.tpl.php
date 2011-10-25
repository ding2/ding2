<?php
/**
 * @file ding_wishlist_item.tpl.php
 *
 * Available variables:
 * - $content: Render array of content.
 *   -ting_cover
 *   -ting_author
 *   -ting_abstract
 *   -ting_subjects
 *   -ting_type - This field is hidden by default. Enable it through UI
 */
?>
<div class="wishlist-item">
  <div class="image">
    <?php print render($content['ting_cover']); ?>
  </div>
  <div class="data">
    <?php print render($content['ting_title']); ?>
    <?php print render($content['ting_type']); ?>
    <?php print render($content['ting_author']); ?>
  </div>
</div>
