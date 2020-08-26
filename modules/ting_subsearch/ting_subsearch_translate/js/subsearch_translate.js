/**
 * @file
 * Subsearch Translate module JS functionality.
 */

(function ($) {
  'use strict';

  let stSettings = Drupal.settings;

  let keys = stSettings.subsearch_translate.keys;
  let conditions = stSettings.subsearch_translate.conditions;
  let results = stSettings.subsearch_translate.results;

  $.ajax({
    type: 'POST',
    url: '/subsearch_translate',
    data: {
      'keys': keys,
      'conditions': conditions,
      'results': results
    },
  })
      .done(r => {
        if (r !== '') {
          // @TODO: Rework wrapper attaching in more "Drupal" approach.
          let main = $('.pane-page-content');
          main.prepend('<div id="subsearch-translate" style="background-color: #F1F2F2; padding-top: 30px;"><div style="max-width: 1124px;margin-left: auto;margin-right: auto;width: 90%;" class="translate inner-content"></div></div>');
          let wrapper = $('#subsearch-translate .inner-content');
          wrapper.html(r);
        }
      })
      .fail(e => {
        console.log(e);
      });
})(jQuery, Drupal);
