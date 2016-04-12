<?php
/**
 * @file
 * Templatefile for the completeness barometer
 */
?>
<div class="user-barometer">
  <?php
if ($barometer === TRUE): ?>
	<div class="user-barometer-container">
		<div class="user-barometer-completed" style="width: <?php print round($procent, 2); ?>%;">
		</div>
		<div class="user-barometer-status">
			<?php print t('Your user profile is @procent % completed', array('@procent' => round($procent))); ?>	
		</div>		
	</div>
  <?php endif; ?>
	<div class="user-barometer-tip">
		<?php print $markup; ?>
	</div>
</div>
