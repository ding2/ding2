<?php
function resetState($lms_url) {
  @file_get_contents($lms_url . '/reset.php');
}
