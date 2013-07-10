<?php
/**
 * @file
 * TODO: Having odd/even implemented here seems like a very one-off solution.
 * Could our base theme either provide this as an option for theme('item_list')
 * or provide the necessary styling using nth-child selectors?
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
