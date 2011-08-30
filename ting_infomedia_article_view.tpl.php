<?php
//drupal_add_js(drupal_get_path('module','infomedia').'/jquery.fancybox-1.3.4.js');
//drupal_add_css(drupal_get_path('module','infomedia').'/jquery.fancybox-1.3.4.css');
//print_r($variables);
?>

<hr style="margin-bottom:1em"/>
<div class="infomedia_image">
<img src="<?php echo drupal_get_path('module','ting_infomedia').'/ting_infomedia_logo.gif';?>"/>
</div>
<?php echo $variables['element']['#markup']; ?>
