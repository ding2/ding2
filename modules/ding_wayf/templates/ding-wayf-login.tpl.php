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
<div class="ding-wayf--login-block">
  <span class="ding-wayf--login-info">
    <?php print drupal_render($link); ?>
  </span>
</div>
