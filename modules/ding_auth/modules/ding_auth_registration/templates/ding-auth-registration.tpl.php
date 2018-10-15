<?php
/**
 * Default template for user self registration information page.
 *
 * Available variables:
 *  - $title: Headline and page title.
 *  - $content: The content for the page.
 *  - $link: Link to login page.
 *
 * Note: The page have pane classes to make it look correct in DDB default theme
 *       this is not optimal, but the only other solution would be to use
 *       exiting_pages module to convert this to an panel page (but it seams
 *       faster for performance and easier to just use the classes).
 */
?>
<div class="empty-sidebars default-layout">
  <div class="layout-wrapper">
    <div class="pane-content">
<<<<<<< HEAD:modules/ding_gatewayf/modules/ding_gatewayf_registration/templates/ding-gatewayf-registration-information.tpl.php
      <div class="primary-content ding-gatewayf">
        <h2 class="pane-title"><?php print render($title); ?></h2>
        <div class="ding-gatewayf--registration-information">
          <?php print render($content); ?>
        </div>
        <div class="ding-gatewayf--link-wrapper">
=======
      <div class="primary-content ding-auth">
        <h2 class="pane-title"><?php print render($title); ?></h2>
        <div class="ding-auth--registration-information">
          <?php print render($content); ?>
        </div>
        <div class="ding-auth--link-wrapper">
>>>>>>> AD: Conversion from wayf to auth:modules/ding_auth/modules/ding_auth_registration/templates/ding-auth-registration.tpl.php
          <?php print render($link); ?>
        </div>
      </div>
    </div>
  </div>
</div>

