<div class="user-view">
  <h1><?php echo $user->getName(); ?></h1>

  <div><?php echo $user->getEmail(); ?></div>

  <h2><?php echo t('Channels'); ?></h2>

  <?php echo theme('bpi_channel_list', array(
    'items' => $channels,
    'empty' => t('User has no channels'),
  )); ?>
</div>
