

  <div class="topbar-inner">
    <?php if ($logo || $site_name || $site_slogan): ?>
      <?php if ($logo): ?>
        <div class="logo">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          </a>
        </div>
      <?php endif; ?>
      <?php if ($site_name || $site_slogan): ?>
        <?php if ($site_name): ?>
          <div class="site-name">
            <h1>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                <?php print $site_name; ?>
              </a>
            </h1>
          </div>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
          <div class="site-slogan">
            <?php print $site_slogan; ?>
          </div>
        <?php endif; ?>
      <?php endif; ?>
    <?php endif; ?>

    <div class="search-compact js-fixed-element">
      <div class="search-field-wrapper">
        <i class="icon-search"></i>
        <input type="text" placeholder="Søg på biblioteket..." class="search-input" />
        <input type="submit" value="Søg" />
      </div>
    </div>

    <div class="user-compact js-fixed-element">
      <div class="user-field-wrapper"><a class="js-show-element" rel="user-login-block"><i class="icon-lock"></i>Log ind</a></div>
    </div>

  </div>
