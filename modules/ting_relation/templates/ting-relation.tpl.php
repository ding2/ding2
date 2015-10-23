<?php
/**
 * @file
 * Default implementation of ting_relation template file.
 *
 * Available variables:
 *   - $title: Relation title string.
 *   - $abstract: Short description of the relation (from the entities
 *     description field or abstract field).
 *   - $online: Array with title and url to more information online.
 *   - $fulltext_link: Link to docbook format inserted by ting_fulltext module.
 */
?>
<div <?php print $attributes?>>
  <h4><?php print $title ?></h4>
  <?php if (isset($abstract)) :?>
    <div class="abstract"><?php print $abstract; ?></div>
  <?php endif; ?>
  <?php if (isset($online['url'])) :?>
    <a class="online_url" target="<?php print $target;?>" href="<?php print $online['url'] ?>"><?php print $online['title']; ?></a>
  <?php endif; ?>
  <?php if (isset($fulltext_link)) :?>
    <?php print $fulltext_link; ?>
  <?php endif; ?>
</div>
