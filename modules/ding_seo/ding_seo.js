/**
 * @file
 * Ding SEO asynchronous JSON-LD.
 */

(function($) {
  "use strict";

  // TODO: Add comment explaining why we're not using Drupal behaviors.
  $(function() {
    var tingObjectId = Drupal.settings.dingSeo.tingObjectId;
    $.get(`/ding_seo/jsonld/ting_object/${tingObjectId}`, function(jsonld) {
      $('head').append(jsonld);
    });
  });
})(jQuery);
