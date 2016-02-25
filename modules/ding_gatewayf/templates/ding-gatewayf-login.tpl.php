<?php
/**
 * @file
 * Default implementation of the ding-gatewayf-login.tpl, which provides a link to
 * login with gatewayf.
 *
 * Available variables:
 *  - $link: link to the login as a render array.
 */
?>
<div class="ding-gatewayf--login-block js-topbar-user">
  <span class="ding-gatewayf--login-info">
    <?php print drupal_render($link) ?>
  </span>
</div>
