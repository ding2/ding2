<?php

/**
 * @file
 * Default template for ting subsearch bibdk message box item list.
 *
 * Available variables:
 *   - $items: An array of ting_subsearch_bibdk message box list items.
 */
?>
<ul>
  <?php foreach ($items as $item) : ?>
    <li class="ting-subsearch-bibdk-message-box-list-item">
      <a href="<?php print $item['url']; ?>" target="_blank">
        <div class="ting-subsearch-bibdk-message-box-list-item--content">
          <?php print $item['markup']; ?>
        </div>
        <div class="ting-subsearch-bibdk-message-box-list-item--see-more">
          <?php print t('More details'); ?>
        </div>
      </a>
    </li>
  <?php endforeach; ?>
</ul>
