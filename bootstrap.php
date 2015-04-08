<?php
function resetState() {
  @file_get_contents('http://alma.lc/web/reset.php');
}
