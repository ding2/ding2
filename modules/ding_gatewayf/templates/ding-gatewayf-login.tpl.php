<?php
/**
 * @file
 * Default implementation of the ding-gatewayf-login.tpl, which provides a link to
 * login with gatewayf.
 *
 * Available variables:
 *  - $link: link to the login as a render array.
 *
 * @TODO: The classes here are not prefixed with gatewayf, but just wayf. It's
 *        this way to support sites that have already used the other WAYF module
 *        and can be changed later on.
 */
?>
<div class="ding-wayf--login-block">
  <span class="ding-wayf--login-info">
    <?php print drupal_render($link); ?>
  </span>
</div>
