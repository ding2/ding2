<?php if ($models && (sizeof($models) > 0)) :?>
<h3><?php print t("Others borrowed:"); ?></h3>
<ul class="list simple">
  <?php foreach ($models as $i => $model) : ?>
    <li class="<?php echo (($i % 2) == 0) ? 'odd' : 'even' ?>">
      <?php echo theme('ting_recommendation_panes_recommendation_list_entry', array("model" => $model)); ?>
    </li>
  <?php endforeach; ?>
</ul>
<?php endif; ?>
