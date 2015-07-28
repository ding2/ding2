<?php

/**
 * @file
 * DDBasic theme implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */

  // If your theme is set to display the site name, uncomment this line and replace the value:
  $site_name = 'DDBasic bibliotek';

  // If your theme is set to *not* display the site name, uncomment this line:
  // unset($site_name);

  // If your theme is set to display the site slogan, uncomment this line and replace the value:
  // $site_slogan = 'My Site Slogan';

  // If your theme is set to *not* display the site slogan, uncomment this line:
  unset($site_slogan);

  $head_title = 'Hjemmesiden er ikke tilgængelig - ' . $site_name;
  
  // If your theme is set to display the site logo, uncomment this line and replace the value:
  //$logo = 'sites/all/files/customLogo.png';
  
  // If your theme is set to *not* display the site logo, uncomment this line:
  unset($logo);
  
  // Title of this page
  $title = "Tekniske problemer ..";
  
  // Main message. Note HTML markup.
  $content = '<p>Hjemmesiden har tekniske problemer og er ikke tilgængelig i øjeblikket. Prøv venligst igen senere. Tak for din forståelse.</p><hr /><p>Er du hjemmesidens administrator, så tjek venligst database-indstillingerne.</p>';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $classes; ?>">
  <div id="page" class="ding2-site-template">
    
    <section class="topbar">

      <div class="topbar-inner">
        
        <div class="panel-pane pane-pane-header">
          <div class="pane-content">
            <div class="topbar-inner">
              <div class="site-name-wrapper">
                
                <?php if (!empty($logo)): ?>
                  <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                  </a>
                <?php endif; ?>
                        
                <?php if (!empty($site_name)): ?>
                  <h1 class="site-name">
                    <a href="<?php print $base_path ?>" title="<?php print t('Home'); ?>" rel="home">
                      <?php print $site_name; ?>
                    </a>
                  </h1>
                <?php endif; ?>
              </div>
            </div>
          </div>
        </div>        
      </div>

    </section>
    
    <section style="top: 0px;" class="navigation-wrapper fixed">
      <div class="navigation-inner">
        <div class="main-menu-wrapper panel-pane pane-block pane-menu-block-1">
          <ul class="main-menu">
            <li class="first leaf">&nbsp;</li>
          </ul>
        </div>
        <div class="secondary-menu-wrapper panel-pane pane-block pane-menu-block-2">
          <ul class="secondary-menu">
            <li class="first leaf">&nbsp;</li>
          </ul>
        </div>
      </div>
    </section>
    
    <div class="content-wrapper">
      <div class="grid-inner">
        <div class="panel-pane pane-page-content">
          <div class="pane-content">
            <div class="empty-sidebars panel-content-wrapper">
              <div class="primary-content">
                <div class="grid-inner">
                  
                  <article>

                    <header class="page-header">
                      <h1 class="page-title"><?php print $title; ?></h1>
                      <div class="page-image"></div>
                      <div class="page-lead"></div>
                    </header>

                    <section class="page-content">
                      <?php print $content; ?>
                    </section>

                  </article>
                
                </div>
              </div>
            </div>  
          </div>
        </div>
      </div>
    </div>
    
  </div> <!-- /page -->

</body>
</html>

