<?php
/**
 * @file
 * Default template file for ting_relations theme function.
 *
 * Available variables:
 *   - $title: The relation group title.
 *   - $source: The name of the type of relations in this group.
 *   - $relations: The relations inside this groups of relations, which should
 *     be rendered as ting_relation.
 */
?>
<div<?php print $attributes; ?>>
  <h2><?php print $title; ?></h2>
  <?php foreach ($relations as $relation) : ?>
    <?php print render($relation); ?>
  <?php endforeach; ?>
</div>
