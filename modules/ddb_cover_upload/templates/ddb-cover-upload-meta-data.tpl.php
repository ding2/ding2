<?php
/**
 * @file
 * Template for showing material information and image metadata.
 *
 * Available variables:
 * - $material: A ting material.
 * - $meta_data: Array of metadata related to the image displayed.
 */
?>
<div>
  <h3><?php print t('Material information');?></h3>
  <div class="content">
    <?php if (!empty($material)) : ?>
      <div class="field field-label-inline">
        <div class="field-label"><?php print t('Post id') . ':';?>&nbsp;</div>
        <div><?php print $material->getId(); ?></div>
      </div>
      <div class="field field-label-inline">
        <div class="field-label"><?php print t('Material name') . ':';?>&nbsp;</div>
        <div><?php print $material->getTitle(); ?></div>
      </div>
    <?php else : ?>
      <span class="changed-warning">(<?php print t('Missing material'); ?>)</span>
    <?php endif; ?>
  </div>

  <h3>
    <?php print t('Image metadata');?>
  </h3>

  <div class="content">
    <div class="field field-label-inline">
      <div class="field-label"><?php print t('Image dimensions') . ':';?>&nbsp;</div>
      <div><?php print $meta_data['file_dimensions']['x'] . ' x ' . $meta_data['file_dimensions']['y'];?></div>
    </div>
    <div class="field field-label-inline">
      <div class="field-label"><?php print t('Image file type') . ':';?>&nbsp;</div>
      <div><?php print $meta_data['file_type'];?></div>
    </div>
    <div class="field field-label-inline">
      <div class="field-label"><?php print t('Image file size') . ':';?>&nbsp;</div>
      <div><?php print $meta_data['file_size'] / 1000;?>KB</div>
    </div>
    <div class="field field-label-inline">
      <div class="field-label"><?php print t('Author') . ':';?>&nbsp;</div>
      <div><?php print $meta_data['author']?></div>
    </div>
  </div>
</div>
