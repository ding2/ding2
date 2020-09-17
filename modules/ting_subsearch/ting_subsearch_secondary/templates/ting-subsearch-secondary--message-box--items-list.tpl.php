<?php

/**
 * @file
 * Secondary search results list items.
 *
 * @var $items
 */
?>
<?php foreach ($items as $item) : ?>
  <a href="<?php print $item['url']; ?>" target="_blank">
    <div class="ting-subsearch-seondary-message-box-list-item">
      <div class="ting-subsearch-seondary-message-box-list-item--content">
        <?php print $item['markup']; ?>
      </div>
      <div class="ting-subsearch-seondary-message-box-list-item--see-more">
        <?php print t('More details'); ?>
      </div>
    </div>
  </a>
<?php endforeach; ?>
