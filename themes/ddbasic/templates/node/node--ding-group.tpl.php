
<article class="<?php print $classes; ?>"<?php print $attributes; ?>>
	<h1 class="title"><?php print $title; ?></h1>

  <div class="content"<?php print $content_attributes; ?>>
    <?php print render($content); ?>
  </div>
</article>
