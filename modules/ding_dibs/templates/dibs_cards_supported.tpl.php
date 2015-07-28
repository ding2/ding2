<?php
/**
 * @file
 * Template to render the DIBS credit card info block.
 */
?>
<div id="dibs-cards-supported" class="clearfix">

<?php
  foreach ($cards_supported as $key=>$card) {
    print '  <p class="card">' . $card . '</p>';
  }
?>

</div>
