<?php
/**
 * @file
 * Template for showing post-submission page.
 *
 * Available variables:
 * - $data: Data fetched from session.
 * - $image: URL of the displayed image.
 */
?>
<div class="container">
  <div class="row">
    <div class="col-12 center">
      <?php if ($image) : ?>
        <img class="img-submitted" src="<?php print $image; ?>">
      <?php endif; ?>
      <div class="js-spinner">
        <div class="spinner">
          <?php print file_get_contents($path . '/images/spinner.svg'); ?>
        </div>
        <h3><?php print t('Sending image to cover service - Please wait a moment');?></h3>
      </div>
      <div class="js-confirmation" style="display:none">
        <?php if ($image) : ?>
          <div class="success">
            <?php print file_get_contents($path . '/images/check.svg'); ?>
          </div>
          <h3><?php print t('Success - Your image will now be added to cover service'); ?></h3>
        <?php else : ?>
          <h3>
            <p><?php print t('Local image not found.') ?></p>
            <p><?php print t('Images are deleted after upload. Did you perhaps reload this page?') ?></p>
          </h3>
          <p><a class="btn btn-primary disabled" id="js-upload-another" href="/admin/config/cover_upload/upload"><?php print t('Upload another'); ?></a></p>
        <?php endif; ?>
      </div>
      <div class="js-error" style="display:none">
        <h3><?php print t('Error - Your image was not uploaded'); ?></h3>
        <p class="error"><?php print t('Unknown error happened') ?></p>
      </div>
    </div>
  </div>
  <div class="border border-gray">
    <div class="row">
      <div class="col-12">
        <h2 class="center"><?php print t('It may take time before new images are displayed'); ?></h2>
      </div>
    </div>
    <div class="row">
      <div class="col-3">
        <div class="media center">
          <div class="media-icon">
            <?php print file_get_contents($path . '/images/indexing.svg'); ?>
          </div>
          <div class="media-body">
            <h3><?php print t('Indexing'); ?></h3>
            <p><?php print t('Before the cover can be displayed it must be indexed by cover service. There may be a queue, but usually it takes 1-2 minutes.'); ?></p>
          </div>
        </div>
      </div>
      <div class="col-3">
        <div class="media center">
          <div class="media-icon">
            <?php print file_get_contents($path . '/images/cache_cms.svg'); ?>
          </div>
          <div class="media-body">
            <h3><?php print t('Cache in CMS'); ?></h3>
            <p><?php print t('To minimize loadon CMS installations images are cached. It may take up to 24 hours before new images are fetched.'); ?></p>
          </div>
        </div>
      </div>
      <div class="col-3">
        <div class="media center">
          <div class="media-icon">
            <?php print file_get_contents($path . '/images/cache_browser.svg'); ?>
          </div>
          <div class="media-body">
            <h3><?php print t('Cache in browser'); ?></h3>
            <p><?php print t('The users browser cache images. These images may be cached for 30 days or more.'); ?></p>
          </div>
        </div>
      </div>
      <div class="col-3">
        <div class="media center">
          <div class="media-icon">
            <?php print file_get_contents($path . '/images/delete_cache.svg'); ?>
          </div>
          <div class="media-body">
            <h3><?php print t('Delete browser cache'); ?></h3>
            <p><?php print t("If you don't see your new image after 24 hours you can try to delete your browsers cache or use incognito/private window."); ?></p>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="row">
    <div class="col-12">
      <p><a class="btn btn-primary disabled" id="js-upload-another" href="/admin/config/cover_upload/upload"><?php print t('Upload another'); ?></a></p>
    </div>
  </div>
</div>
