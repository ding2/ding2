<div class="ting-object view-mode-teaser clearfix">
  <div class="ting-object view-mode-search-result imagestyle-ding-list-medium list-item-style clearfix">
    <div class="inner">
      <div id="ting-object-ting-object-search-result-group-ting-left-col-search" class="ting-object-left group-ting-left-col-search field-group-div field-group-format group-ting-left-col-search">
        <?php print $cover; ?>
      </div>
      <div id="ting-object-ting-object-search-result-group-ting-right-col-search" class="ting-object-right group-ting-right-col-search field-group-div field-group-format group-ting-right-col-search">
        <div class="field field-name-ting-title field-type-ting-title field-label-hidden">
          <?php print $title; ?>
        </div>
        <div class="field field-name-ting-author field-type-ting-author field-label-hidden"><?php print $creators; ?></div>
        <div id="ting-object-ting-object-search-result-group-info" class="info-container group-info field-group-div field-group-format group-info">
          <div class="field field-name-ting-abstract field-type-ting-abstract field-label-hidden">
            <div class="field-items">
              <div class="field-item even"><?php print $abstract; ?></div>
            </div>
          </div>
          <?php if (!empty($series)) : ?>
            <div class="field field-name-ting-series field-type-ting-series field-label-above">
              <div class="field-label"><?php print t('Series') ?></div>
              <div class="field-items">
                <div class="field-item even"><?php print $series; ?></div>
              </div>
            </div>
          <?php endif; ?>
          <div class="availability search-result--availability">
            <strong><?php print t('Borrowing options') ?></strong>
            <p class="js-online">
              <?php print implode($types); ?>
            </p>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
