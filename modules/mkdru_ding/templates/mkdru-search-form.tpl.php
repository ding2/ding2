<?php
/**
 * @file
 * Search form template.
 */
?>

<div class="row">
  <div class="col-lg-12">
    <div class="input-group">
      <?php print render($form['basic']['keys']); ?>
      <div class="input-group-btn">
        <?php print render($form['basic']['submit']); ?>
      </div >
    </div>
  </div>
  <?php print drupal_render_children($form); ?>
</div>
<form class="mkdru-dropdowns">
  <div class="dropdown-wrapper">
  <select class="mkdru-sort">
    <option value="relevance" selected="selected"><?php print t("Sort by: ") ?><?php print t("relevance") ?></option>
    <option value="title:1"><?php print t("Sort by: ") ?><?php print t("title") ?></option>
    <option value="date:0"><?php print t("Sort by: ") ?><?php print t("newest") ?></option>
    <option value="date:1"><?php print t("Sort by: ") ?><?php print t("oldest") ?></option>
  </select>
  <select class="mkdru-perpage">
    <option value="10"><?php print t("Show per page: ") ?>10</option>
    <option value="20" selected="selected"><?php print t("Show per page: ") ?>20</option>
    <option value="30"><?php print t("Show per page: ") ?>30</option>
    <option value="50"><?php print t("Show per page: ") ?>50</option>
  </select>
  </div>
</form>
