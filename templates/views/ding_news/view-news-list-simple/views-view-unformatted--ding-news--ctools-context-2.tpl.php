<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<ul class="list simple">
<?php foreach ($rows as $id => $row): ?>
  <li class="<?php print $classes_array[$id]; ?>">
    <?php print $row; ?>
  </li>
<?php endforeach; ?>
</ul>
