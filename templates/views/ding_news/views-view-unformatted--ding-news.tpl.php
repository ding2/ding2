<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<?php foreach ($rows as $id => $row): ?>
  <li class="<?php echo $classes_array[$id]; ?>">
    <?php echo $row; ?>
  </li>
<?php endforeach; ?>
