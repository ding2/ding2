<?php if ($logo || $site_name || $site_slogan): ?>
  <?php if ($logo): ?>
    <div class="logo">
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
    </div>
  <?php endif; ?>
  <?php if ($site_name || $site_slogan): ?>
    <div class="site-name-wrapper">
      <?php if ($site_name): ?>
        <h1 class="site-name<?php if ($site_slogan) print '-with-slogan' ?>">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <?php print $site_name; ?>
          </a>
        </h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <div class="site-slogan">
          <?php print $site_slogan; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>
<?php endif; ?>

<!-- Temporary until my local version works again -->

<ul class="topbar-menu">
  <li><a href="/search" class="topbar-menu-item-active"><i class="icon-search"></i><span><?php print t('Search'); ?></span></a></li>
  <li><a href="/user" class="topbar-menu-item"><i class="icon-user"></i><span><?php print t('Log in / create user'); ?></span></a></li>
  <li><a href="#" class="topbar-menu-item"><i class="icon-align-justify"></i><span><?php print t('Menu'); ?></span></a></li>
</ul>