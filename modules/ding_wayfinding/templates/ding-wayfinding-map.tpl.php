<?php

/**
 * @file
 * Default template file for ding wayfinding map.
 *
 * Variables:
 *   height: The height of map.
 *   width: The width of the map.
 *   info: Information popup render array about the marker.
 */
?>
<div id="wayfinding-map" style="width: <?php print $width ?>; height: <?php print $height ?>"></div>
<?php
if (!is_null($info)):
  print render($info);
endif;
?>
