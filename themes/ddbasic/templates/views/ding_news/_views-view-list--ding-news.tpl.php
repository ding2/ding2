<?php
/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */

print $wrapper_prefix;
  if (!empty($title)):
    print '<h3>' . $title . '</h3>';
  endif;
  print $list_type_prefix;
    foreach ($rows as $id => $row):
      print '<li class="news-list-item">' . $row . '</li>';
    endforeach;
  print $list_type_suffix;
print $wrapper_suffix;

