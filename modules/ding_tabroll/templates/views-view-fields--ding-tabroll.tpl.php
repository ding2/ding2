<?php
/**
 * @file
 * Defines the individual roll tab content layout.
 *
 * @ingroup views_templates
 */
?>
<div class="image">
  <?php print l($fields['field_ding_tabroll_image']->content, $fields['field_ding_tabroll_link']->raw ? 'node/' . $fields['field_ding_tabroll_link']->raw : $fields['field_ding_tabroll_ext']->content, array('html' => TRUE)); ?>
</div>

<div class="info">
  <h3><?php print l($fields['title']->content, $fields['field_ding_tabroll_link']->raw ? 'node/' . $fields['field_ding_tabroll_link']->raw : $fields['field_ding_tabroll_ext']->content); ?></h3>
  <p><?php print $fields['field_ding_tabroll_lead']->content; ?></p>
</div>
