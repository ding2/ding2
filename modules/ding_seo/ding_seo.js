/**
 * @file
 * Ding SEO asynchronous JSON-LD.
 */

(function($) {
  "use strict";

  // Bypass Drupal behaviors since we just need to insert a script in header
  // once and have no need to interact with other elements on the page.
  $(function() {
    var tingObjectId = Drupal.settings.dingSeo.tingObjectId;
    $.getJSON(`/ding_seo/jsonld/ting_object/${tingObjectId}`, function(data) {
      $('head').append(data.jsonLd);
    });
  });
})(jQuery);
