<?php

/**
 * @file
 * Default template file for ting_relations theme function.
 *
 * Available variables:
 *   - $attributes: Mainly string with the rendered class variables.
 *   - $attributes_array: Array with the attributes.
 *   - $title: The relation group title.
 *   - $source: The name of the type of relations in this group.
 *   - $relations: The relations inside this groups of relations, which should
 *     be rendered as ting_relation.
 */
?>
<h2><span class="field-group-format-toggler"><?php print $title; ?></span></h2>
<div class="field-group-format-wrapper" style="display: none;">
<?php foreach ($relations as $relation) : ?>
  <?php print render($relation); ?>
<?php endforeach; ?>
</div>
