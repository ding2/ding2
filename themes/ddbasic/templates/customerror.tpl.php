<?php
/**
 * @file
 * DDBasic theme's implementation for displaying CustomError's module response.
 *
 * Available variables:
 * - $content: An rendered content field provided by CustomError module.
 */
?>
<div class="empty-sidebars default-layout">
  <div class="layout-wrapper">
    <div class="primary-content">
      <article class="page">
        <header class="page-header"></header>
        <section class="page-content">
          <?php print render($content['value']); ?>
        </section>
        <footer class="page-footer"></footer>
      </article>
    </div>
  </div>
</div>
