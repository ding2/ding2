<?php
/** Variables: $footer_blocks **/

$num_footer_blocks = count($footer_blocks);

?>
<div class="ding-footer-wrapper">
<?php

  $csss = array('grid-full');
  
  switch ($num_footer_blocks) {
  case 1:
    $csss = array('grid-full');
    break;
  case 2:
    $csss = array('grid-8-left',
		  'grid-8-right');
    break;
  case 3:
    $csss = array('grid-4-left',
		  'grid-8-center',
		  'grid-4-right');
    break;
  case 4:
    $csss = array('grid-4-left',
		  'grid-4-center-left',
		  'grid-4-center-right',
		  'grid-4-right');
    break;
  default:
    $csss = array_fill(0, $num_footer_blocks, 'grid-undefined');
    break;
  }

foreach($footer_blocks as $key => $foot) {
  
?>
  <div class="<?php echo $csss[$key]; ?>">
<?php echo $foot['content']['value']; ?>
  </div>
<?php

}

?>
</div>
