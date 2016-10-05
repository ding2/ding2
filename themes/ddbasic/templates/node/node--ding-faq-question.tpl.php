<article class="<?php print $classes; ?> node-full"<?php print $attributes; ?>>
  <div class="inner">
    <div class="left">
  		<?php print render($content['group_left']); ?>
  	</div>
  	<div class="right">
  		<h1><?php print $title; ?></h1>
  		<?php print render($content['group_right']); ?>
  	</div>
  	<div class="buttons">
    	<?php print l(t('FAQ'), 'faq'); ?>
  	</div>
  </div>
</article>