<?php
/**
 * @file
 * Ting field search two column 66/33 stacked layout template file.
 */
?>

<div <?php if (!empty($css_id)) { print 'id="' . $css_id . '"'; } ?> class="ting-field-search-panel-layout">
  <?php if (!empty($content['header']) || !empty($content['top'])) : ?>
    <div class="top-and-header-content">
      <div class="layout-wrapper">
        <?php if (!empty($content['header'])) : ?>
          <div class="header-content">
            <?php print $content['header']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['top'])) : ?>
          <div class="top-content">
            <?php print $content['top']; ?>
          </div>
        <?php endif; ?>
      </div>
    </div>
  <?php endif; ?>
  <?php if (!empty($content['main']) || !empty($content['right'])) : ?>
    <div class="main-and-right-content">
      <div class="layout-wrapper">
        <div class="primary-content">
          <?php print $content['main']; ?>
        </div>
        <?php if (!empty($content['right'])) : ?>
          <aside class="right-content">
            <?php print $content['right']; ?>
          </aside>
        <?php endif; ?>
      </div>
    </div>
  <?php endif; ?>
  <?php if (!empty($content['footer'])) : ?>
    <div class="layout-wrapper">
      <div class="footer-content">
        <?php print $content['footer']; ?>
      </div>
    </div>
  <?php endif; ?>
</div>
