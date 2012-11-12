<?php if ($models && (sizeof($models) > 0)) :?>
<h3><?php print t("Others borrowed:"); ?></h3>
<ul class="list simple">
  <?php foreach ($models as $i => $model) : ?>
    <li class="<?php echo (($i % 2) == 0) ? 'odd' : 'even' ?>">
      <?php echo theme('ding_adhl_frontend_recommendation_list_entry', array("model" => $model)); ?>
    </li>
  <?php endforeach; ?>
</ul>
<?php endif; ?>
