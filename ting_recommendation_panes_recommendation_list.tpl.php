<?php if ($objects && (sizeof($objects) > 0)) :?>
<div class="ding-box-wide">
  <h3><?php print t("Other did borrow:"); ?></h3>
  <ul class="ting-recommendation">
	  <?php foreach ($objects as $i => $object) : ?>
	    <li class="<?php echo (($i % 2) == 0) ? 'odd' : 'even' ?> <?php echo ((is_int(($i-1) / 4)) || (is_int($i / 4))) ? 'either' : 'or' ; ?>">
	      <?php echo theme('ting_recommendation_panes_recommendation_list_entry', $object); ?>      
	    </li>    
	  <?php endforeach; ?>
  </ul>
</div>  
<?php endif; ?>