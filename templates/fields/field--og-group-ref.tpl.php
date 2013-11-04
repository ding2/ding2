<?php
/**
 * @file field.tpl.php
 */
?>
<?php if (!$label_hidden): ?>
  <strong><?php print $label ?>:</strong>
<?php endif; ?>
<?php foreach ($items as $delta => $item): ?>
  <span class="label label-info"><?php print render($item); ?></span>
<?php endforeach; ?>
