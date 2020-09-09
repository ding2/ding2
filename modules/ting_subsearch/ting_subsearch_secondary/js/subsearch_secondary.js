/**
 * @file
 * Secondary search JS functionality.
 */

(function ($) {
  'use strict';

  var settings = Drupal.settings.tingSubsearchSecondary;

  $.ajax({
    type: 'POST',
    url: '/subsearch_secondary',
    data: {
      'keys': settings.keys,
      'numResults': settings.numResults
    },
  }).done(function (r) {
    if (r !== '') {
      var message = $(r);
      $('#subsearch-secondary').html(message);
      Drupal.attachBehaviors(message);
    }
  }).fail(function (e) {
    console.log(e);
  });

})(jQuery);
