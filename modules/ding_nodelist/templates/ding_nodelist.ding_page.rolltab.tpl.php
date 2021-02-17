<?php

/**
 * @file
 * Template file for rolltab page layout.
 *
 * Notice: This file is also used by
 * - ding_nodelist.ding_news.rolltab.tpl.php
 * - ding_nodelist.ding_event.rolltab.tpl.php
 */

// We need to make sure that the content is wrapped in a <p> tag,
// however sometimes the content already comes with <p> tag, so we'll check for
// that, to avoid any W3C errors by having multiple p tags.
$body = $item->teaser_lead;
$p_body_wrapper = TRUE;

if (!empty($body) && substr($body, 0, 2) === '<p') {
  $p_body_wrapper = FALSE;
}

?>
<div class="ui-tabs-panel"<?php print $attributes; ?>>
  <div class="image">
    <?php if (!$item->image): ?>
      <span class="no-image"></span>
    <?php else: ?>
      <?php print $item->image_link; ?>
    <?php endif; ?>
  </div>
  <div class="info">
    <h3><?php print l($item->title, 'node/' . $item->nid); ?></h3>
     <?php if ($p_body_wrapper): ?>
      <p>
     <?php endif; ?>
     <?php print $body; ?>
     <?php if ($p_body_wrapper): ?>
      </p>
    <?php endif; ?>
  </div>
</div>
