<?php
/**
 * @file
 * Provides a link to login with WAYF.
 *
 * Available variables:
 *  - $login_url: link to the login as a render array.
 *
 * Added js class to match DDBasic top-bar script.
 */
?>
<div class="ding-wayf--login-block js-topbar-user">
  <span class="ding-wayf--login-info">
      <?php print render($login_url) ?>
  </span>
</div>
