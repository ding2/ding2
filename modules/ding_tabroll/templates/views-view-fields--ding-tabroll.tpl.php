<?php
/**
 * @file
 * Defines the individual roll tab content layout.
 *
 * @ingroup views_templates
 */

// We need to make sure that the content is wrapped in a <p> tag,
// however sometimes the content already comes with <p> tag, so we'll check for
// that, to avoid any W3C errors by having multiple p tags.
$body = $fields['field_ding_tabroll_lead']->content;
$p_body_wrapper = TRUE;

if (!empty($body) && substr($body, 0, 2) === '<p') {
  $p_body_wrapper = FALSE;
}

?>
<div class="image">
  <?php print l($fields['field_ding_tabroll_image']->content, $url, array('html' => TRUE)); ?>
</div>

<div class="info">
  <h3><?php print l($fields['title']->raw, $url); ?></h3>

  <?php if ($p_body_wrapper): ?>
    <p>
  <?php endif; ?>

  <?php print $body; ?>

  <?php if ($p_body_wrapper): ?>
    </p>
  <?php endif; ?>
</div>
