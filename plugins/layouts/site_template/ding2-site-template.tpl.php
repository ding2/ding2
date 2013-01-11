<div id="page<?php print $css_id ? " $css_id" : ''; ?>" class="<?php print $classes; ?>">

  <?php if (!empty($content['branding'])): ?>
    <section class="topbar">
      <div class="topbar-inner">
        <?php print render($content['branding']); ?>
      </div>
    </section>
  <?php endif; ?>

  <?php if (!empty($content['header'])): ?>
    <header class="header-wrapper">
      <div class="header-inner">
        <?php print render($content['header']); ?>
      </div>
    </header>
  <?php endif; ?>

  <?php if (!empty($content['navigation'])): ?>
    <section class="navigation-wrapper">
      <div class="navigation-inner">
        <?php print render($content['navigation']); ?>
      </div>
    </section>
  <?php endif; ?>

  <div class="content-wrapper">
    <div class="grid-inner">
      <?php print render($content['content']); ?>
    </div>
  </div>

  <?php if (!empty($content['footer'])): ?>
    <footer class="footer">
      <div class="grid-inner">
        <?php print render($content['footer']); ?>
      </div>
    </footer>
  <?php endif; ?>
  
</div>