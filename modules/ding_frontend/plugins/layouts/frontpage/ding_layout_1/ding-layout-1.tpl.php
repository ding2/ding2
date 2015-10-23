<?php
/**
 * @file
 * ddbasic implementation to present a Panels layout.
 *
 * Available variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 * - $css_id: unique id if present.
 */
?>
<div <?php if (!empty($css_id)) { print ' id="$css_id"'; } ?> class="frontpage-layout">

  <?php if (!empty($content['primary'])): ?>
    <div class="primary-content">
      <?php print $content['primary']; ?>
    </div>
  <?php endif ?>

  <div class="layout-wrapper">
    <?php if (!empty($content['secondary'])): ?>
      <div class="secondary-content">
        <?php print $content['secondary']; ?>
      </div>
    <?php endif ?>

    <?php if (!empty($content['tertiary'])): ?>
      <div class="tertiary-content">
        <?php print $content['tertiary']; ?>
      </div>
    <?php endif ?>

    <?php if (!empty($content['attachment_4_1']) || !empty($content['attachment_4_2']) || !empty($content['attachment_4_3']) || !empty($content['attachment_4_4'])): ?>
      <div class="attachments-wrapper attachments-4-4">
        <div class="attachment-first">
          <div class="grid-inner"><?php print $content['attachment_4_1']; ?></div>
        </div>
        <div class="attachment-second">
          <div class="grid-inner"><?php print $content['attachment_4_2']; ?></div>
        </div>
        <div class="attachment-third">
          <div class="grid-inner"><?php print $content['attachment_4_3']; ?></div>
        </div>
        <div class="attachment-fourth">
          <div class="grid-inner"><?php print $content['attachment_4_4']; ?></div>
        </div>
      </div>
    <?php endif ?>

    <?php if (!empty($content['attachment_3_1']) || !empty($content['attachment_3_2']) || !empty($content['attachment_3_3'])): ?>
      <div class="attachments-wrapper attachments-3-3">
        <div class="attachment-first">
          <div class="grid-inner"><?php print $content['attachment_3_1']; ?></div>
        </div>
        <div class="attachment-second">
          <div class="grid-inner"><?php print $content['attachment_3_2']; ?></div>
        </div>
        <div class="attachment-third">
          <div class="grid-inner"><?php print $content['attachment_3_3']; ?></div>
        </div>
      </div>
    <?php endif ?>

    <?php if (!empty($content['attachment_2_1']) || !empty($content['attachment_2_2'])): ?>
      <div class="attachments-wrapper attachments-2-2">
        <div class="attachment-first">
          <div class="grid-inner"><?php print $content['attachment_2_1']; ?></div>
        </div>
        <div class="attachment-second">
          <div class="grid-inner"><?php print $content['attachment_2_2']; ?></div>
        </div>
      </div>
    <?php endif ?>

    <?php if (!empty($content['attachment_1_1'])): ?>
      <div class="group-blocks--wrapper attachments-wrapper attachments-1-1">
          <?php print $content['attachment_1_1']; ?>
      </div>
    <?php endif ?>
  </div>
</div>
