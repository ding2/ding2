<?php

/**
 * @file
 * Views Exposed Form Widget template.
 */

$element_name = $element['#name'] . '[]';
$element_id = $element['#id'];
?>

<div class="views-exposed-form-widget" id="<?php print $element_id; ?>">
  <h2 class="sub-menu-title"><?php print $title; ?></h2>
  <ul class="sub-menu">
    <?php foreach ($items as $key => $item): ?>
      <li>
        <input type="checkbox" id="<?php print $element_id . '-' . $key; ?>" name="<?php print $element_name; ?>" value="<?php print $key; ?>">
        <label for="<?php print $element_id . '-' . $key; ?>" class="menu-item"><?php print $item; ?></label>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
