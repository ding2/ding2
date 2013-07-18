<?php
/**
 * @file
 * Template to render ting_releation content.
 */
if (is_array($content)) {
  foreach ($content as $ns => $relations) {
    if (!empty($relations) && $ns != 'dbcaddi:hasOnlineAccess') { ?>
      <div class="<?php print $classes . ' ' . drupal_html_class(str_replace(':', ' ', $ns)) . ' clearfix'; ?>">
        <h2><?php print $relations[0]['type']; ?></h2>
        <?php foreach ($relations as $relation) { ?>
          <div class="meta">
            <?php
            if (isset($relation['abstract'])) {
              print '<div>' . $relation['abstract'] . '</div>';
            }

            if (isset($relation['text'])) {
              print '<div>' . $relation['text'] . '</div>';
            }

            if (!empty($relation['online_url'])) {
              print '<div class="field-type-ting-relation">';
              print '<div class="field-items rounded-corners">';
              $online_url = $relation['online_url'];
              print render($online_url);
              print '</div></div>';
            }

            if (!empty($relation['docbook_link'])) {
              $docbok_link = $relation['docbook_link'];
              print render($docbok_link);
            }
            ?>
          </div>
        <?php } ?>
      </div>
    <?php
    }
  }
}
?>
