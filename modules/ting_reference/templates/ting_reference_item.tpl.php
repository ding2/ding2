<?php

/**
 * @file
 * Default ting reference item template.
 *
 * Available variables:
 *  - $content: Item content.
 *  - $entity_id: The id of the entity referenced.
 *  - $view_mode: The view mode for the reference.
 */
?>
<span class="<?php print $classes; ?>" data-entity-id="<?php print $entity_id; ?>" data-view-mode="<?php print $view_mode; ?>">
  <div class="placeholder">
    <span class="icon-spinner"></span>
  </div>
</span>
