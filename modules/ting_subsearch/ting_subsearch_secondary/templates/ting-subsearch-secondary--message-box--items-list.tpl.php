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
    <div class="message-box--list-item">
      <div class="message-box--content">
        <?php print $item['markup']; ?>
      </div>
      <div class="message-box--see-more">
        <?php print t('More details'); ?>
      </div>
    </div>
  </a>
<?php endforeach; ?>
