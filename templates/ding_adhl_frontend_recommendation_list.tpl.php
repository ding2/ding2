<?php
/**
 * @file
 *
 */
?>
<?php if (!empty($recommendations)) :?>
<h3><?php print t("Others borrowed:"); ?></h3>
<ul>
  <?php foreach ($recommendations as $i => $recommendation) : ?>
    <li class="<?php echo (($i % 2) == 0) ? 'odd' : 'even' ?>">
      <?php echo theme('ding_adhl_frontend_recommendation_list_entry', array("recommendation" => $recommendation)); ?>
    </li>
  <?php endforeach; ?>
</ul>
<?php endif; ?>
