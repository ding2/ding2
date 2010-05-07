<a href="<?php echo $object->url ?>" title="<?php print check_plain($object->title) ?><?php if (!empty($object->creators_string)) { print ': ' . check_plain($object->creators_string); } ?>">
  <span class="title"><?php print check_plain($object->title); ?></span>
  <?php if (!empty($object->creators_string)) { ?>
    <span class="creator"><?php print check_plain($object->creators_string); ?></span>
  <?php } ?>
</a>
