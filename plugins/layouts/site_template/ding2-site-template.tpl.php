<div id="page<?php print $css_id ? " $css_id" : ''; ?>" class="<?php print $classes; ?>">

  <?php if (!empty($content['branding'])): ?>
    <div class="branding">
      <div class="grid-inner">
        <?php print render($content['branding']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['header'])): ?>
    <header>
      <div class="grid-inner">
        <div class="header-inner">
          <?php print render($content['header']); ?>
        </div>
      </div>
    </header>
  <?php endif; ?>

  <div class="main-content">
    <div class="content-wrapper">
      <div class="content-inner">
        <?php print render($content['content']); ?>
      </div>
    </div>
  </div>

  <?php if (!empty($content['footer'])): ?>
    <footer>
      <div class="grid-inner">
        <div class="footer-wrapper">
          <div class="footer-content">
            <?php print render($content['footer']); ?>
          </div>
        </div>
      </div>
    </footer>
  <?php endif; ?>
  
  <?php if (!empty($content['bottom'])): ?>
    <div class="bottom">
      <div class="grid-inner">
        <?php print render($content['bottom']); ?>
      </div>
    </div>
  <?php endif; ?>

</div>