<?php
/**
 * @file
 * Template to render ting_releation content.
 */
if (is_array($content)) {
  foreach ($content as $ns => $relations) {
    if (!empty($relations) && $ns != 'dbcaddi:hasOnlineAccess') { ?>
    <a name="<?php echo $ns; ?>"></a>
    <div class="<?php print $classes . ' ting-relation-' . drupal_html_class($ns) . ' clearfix'; ?>">
      <h2><?php print $relations[0]['title']; ?></h2>
      <?php foreach ($relations as $relation) { ?>
        <div class="meta">
          <?php
          if (isset($relation['title'])) {
            print '<h3>' . $relation['title'] . '</h3>';
          }
          if (isset($relation['year'])) {
            print '<div>' . $relation['year'] . '</div>';
          }
          if (isset($relation['creator'])) {
            print '<div>' . $relation['creator'] . '</div>';
          }
          if (isset($relation['byline'])) {
            print '<div>' . $relation['byline'] . '</div>';
          }
          if (isset($relation['isPartOf'])) {
            print $relation['isPartOf'];
          }
          ?>
        </div>
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

        print '<div class="clearfix"></div>';
      }
      print '</div>';
    }
  }
}
