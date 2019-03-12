<div class="ting-object view-mode-teaser clearfix">
  <div class="ting-object view-mode-search-result imagestyle-ding-list-medium list-item-style clearfix">
    <div class="inner">
      <?php print $cover; ?>
      <div id="ting-object-ting-object-search-result-group-ting-right-col-search" class="ting-object-right group-ting-right-col-search field-group-div field-group-format group-ting-right-col-search">
        <div class="field field-name-ting-title field-type-ting-title field-label-hidden">
          <span class="search-result--heading-type js-toggle-info-container"><?php print $maintype; ?></span>
          <h2><?php print $title; ?></h2>
        </div>
        <div class="field field-name-ting-author field-type-ting-author field-label-hidden"><?php print $creators; ?></div>
        <div id="ting-object-ting-object-search-result-group-info" class="info-container group-info field-group-div field-group-format group-info">
          <div class="field field-name-ting-abstract field-type-ting-abstract field-label-hidden">
            <div class="field-items">
              <div class="field-item even"><?php print $abstract; ?></div>
            </div>
          </div>
          <?php print $series; ?>
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
