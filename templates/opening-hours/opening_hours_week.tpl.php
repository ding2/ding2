<?php
/**
 * @file
 * Template for rendering opening hours week.
 */

if (!empty($preface)) {
  print $preface;
}
?>
<a href="javascript:return false;" class="opening-hours-toggle"><?php print t('Opening hours'); ?></a>
<div class="opening-hours-week placeholder" data-nid="<?php print $node->nid; ?>">
  <div class="header">
    <a class="prev" href="#prev"><i class="icon-arrow-left"></i></a>
    <?php print t('Week'); ?>
    <span class="week_num"></span> –
    <span class="from_date"></span> –
    <span class="to_date"></span>
    <a class="next" href="#next"><i class="icon-arrow-right"></i></a>
  </div>
  <div class="days"></div>
</div>

