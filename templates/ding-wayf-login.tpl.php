<?php
/**
 * @file
 * Default implementation of the ding-wayf-login-tpl, which provides a link to
 * login with WAYF.
 *
 * Available variables:
 *  - $link: link to the login as a render array.
 */
?>
<div class="ding-wayf--logon-block">
  <span class="ding-wayf--logon-info">
    <?php print drupal_render($link); ?>
  </span>
</div>
