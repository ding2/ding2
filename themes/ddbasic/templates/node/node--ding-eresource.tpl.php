<article class="<?php print $classes; ?> node-full"<?php print $attributes; ?>>
  <div class="inner">
  	<div class="left">
  		<?php print render($content['group_left']); ?>
  	</div>
  	<div class="right">
  		<h1><?php print $title; ?></h1>
  		<?php print render($content['group_right']['field_ding_eresource_category']); ?>
  		<div class="section meta">
  			<?php print render($content['group_right']['field_ding_eresource_access']); ?>
  		</div>
  		<?php print render($content['group_right']); ?>
  	</div>
  </div>
</article>