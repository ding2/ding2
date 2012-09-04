<?php
$url = url($model['url']);
$creators_string = implode(", ", $model['creators']);
$title = $model['title'];
?>
<a href="<?php echo $url ?>" title="<?php print check_plain($title) ?><?php if (!empty($creators_string)) { print ': ' . check_plain($creators_string); } ?>">
  <span class="title"><?php print check_plain($title); ?></span>
  <?php if (!empty($creators_string)) { ?>
    <span class="creator"><?php print check_plain($creators_string); ?></span>
  <?php } ?>
</a>