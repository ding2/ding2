<div class="channel-view">
  <div class="bpi-actions">
    <?php if (bpi_can_edit_channel($channel)) { echo l(t('Edit'), 'admin/bpi/channel/' . $channel->getId() . '/edit'); } ?>
    <?php if (bpi_can_edit_channel($channel)) { echo l(t('Delete'), 'admin/bpi/channel/' . $channel->getId() . '/delete'); } ?>
  </div>

  <h1><?php echo $channel->getName(); ?></h1>

  <div class="description"><?php echo $channel->getDescription(); ?></div>

  <div>
    <?php echo t('Channel administrator'); ?>: <?php echo l($channel->getAdmin()->getName(), 'admin/bpi/user/' . $channel->getAdmin()->getId()); ?>, <?php echo $channel->getAdmin()->getAgency()->getName(); ?>
  </div>

  <h2><?php echo t('Channel editors'); ?></h2>

  <?php if (bpi_can_edit_channel($channel)): ?>
    <ul class="action-links">
      <li>
<?php echo l(t('Add editors to channel'), 'admin/bpi/user', array('query' => array('add-to-channel' => $channel->getId()))); ?>
      </li>
    </ul>
  <?php endif ?>

  <?php echo theme('bpi_user_list', array(
    'items' => $channel->getEditors(),
    '#channel' => $channel,
    'empty' => t('Channel has no editors'),
  )); ?>

  <h2><?php echo t('Channel content'); ?></h2>

  <?php if (bpi_can_contribute_to_channel($channel)): ?>
    <ul class="action-links">
      <li>
        <?php echo l(t('Add nodes to channel'), 'admin/bpi/'); ?>
      </li>
    </ul>
  <?php endif ?>

  <?php if ($channel->getNodeLastAddedAt()): ?>
    <p>
      <?php echo t('Node last added to channel at !timestamp', array('!timestamp' => $channel->getNodeLastAddedAt()->format('Y-m-d H:i:s'))); ?>
    </p>
  <?php endif ?>

  <?php if ($has_new_content): ?>
    <div class="messages status">
      <?php echo t('Channel has new content!'); ?>
    </div>
  <?php endif ?>

  <?php echo theme('bpi_channel_node_list', array(
    'items' => $nodes,
    '#channel' => $channel,
    'empty' => t('Channel has no nodes'),
  )); ?>
</div>
