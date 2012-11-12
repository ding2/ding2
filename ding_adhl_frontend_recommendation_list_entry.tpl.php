<?php
/**
 * @file
 *
 */

$url = url($model['url']);
$creators_string = check_plain(implode(", ", $model['creators']));
$title = $model['title'];
?>
<a href="<?php echo $url ?>" title="<?php print check_plain($title) ?><?php echo !empty($creators_string) ? ': ' . $creators_string : ''; ?>">
  <span class="title"><?php print check_plain($title); ?></span>
  <?php if (!empty($creators_string)) : ?>
    <span class="creator"><?php print $creators_string; ?></span>
  <?php endif; ?>
</a>