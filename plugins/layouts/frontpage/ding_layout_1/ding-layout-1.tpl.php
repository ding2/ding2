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

/**
 * Add a css class based on wich regions have content
 */
$add_class = '';

if (empty($content['top_secondary'])) {
  $add_class.= 'no-top-secondary ';
}

if (empty($content['main_left_right'])) {
  $add_class.= 'no-main-left-right ';
}

if (empty($content['main_right_right'])) {
  $add_class.= 'no-main-right-right ';
}
?>
<div <?php if (!empty($css_id)) { print " id=\"$css_id\""; } ?> class="<?php echo $add_class; ?> panel-content-wrapper">

  <div class="top-wrapper">
    <div class="top-content">
      <div class="grid-inner"><?php print $content['top']; ?></div>
    </div>

    <?php if (!empty($content['top_secondary'])): ?>
      <div class="top-secondary">
        <div class="grid-inner"><?php print $content['top_secondary']; ?></div>
      </div>
    <?php endif ?>
  </div>

  <div class="main-wrapper">
    <div class="main-content">
      <div class="grid-inner"><?php print $content['main_content']; ?></div>
    </div>

    <?php if (!empty($content['main_left_right'])): ?>
      <div class="main-left-right">
        <div class="grid-inner"><?php print $content['main_left_right']; ?></div>
      </div>
    <?php endif ?>

    <?php if (!empty($content['main_right_right'])): ?>
      <div class="main-right-right">
        <div class="grid-inner"><?php print $content['main_right_right']; ?></div>
      </div>
    <?php endif ?>
  </div>

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
    <div class="attachments-wrapper attachments-1-1">
      <div class="attachment-first">
        <div class="grid-inner"><?php print $content['attachment_1_1']; ?></div>
      </div>
    </div>
  <?php endif ?>

</div>
