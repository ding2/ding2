<?php
/**
 *
 * The outer div is needed to target it with JavaScript.  
 */
?>
<div class="ding-user-login-button">
  <a class="button login-button" href="/user"><?php print t('Log in'); ?></a>
  <div class="user">    
    <?php print drupal_render($login_form); ?>
  </div>
</div>