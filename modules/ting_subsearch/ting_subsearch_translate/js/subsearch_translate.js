/**
 * @file
 * Subsearch Translate module JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearchTranslate;

  $.ajax({
    type: 'POST',
    url: '/subsearch_translate' + settings.query,
    data: {
      'originalSearch': settings.originalSearch,
      'originalSearchNumResults': settings.originalSearchNumResults,
    },
  }).done(function(r) {
    if (r !== '') {
      var message = $(r);
      $('#ting-subsearch-translate-placeholder').replaceWith(message);
      Drupal.attachBehaviors(message);
    }
    else {
      $('#ting-subsearch-translate-placeholder').remove();
    }
  }).fail(function(e) {
    console.log(e);
  });
})(jQuery);
