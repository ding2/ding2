<?php

/**
 * @file
 * Default template for ting subsearch secondary message box item list.
 *
 * Available variables:
 *   - $items: An array of ting_subsearch_secondary message box list items.
 */
?>
<ul>
  <?php foreach ($items as $item) : ?>
    <li>
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
    </li>
  <?php endforeach; ?>
</ul>
