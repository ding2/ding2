/**
 * @file
 * Fix some issues on the date repeat form element, that shows all configuration
 * options on page load, which makes it really confusing. The date repeat field
 * uses the #states API from FAPI and it works after the form-element is used
 * first time, but it seems to fail to initialize the states.
 */

(function($) {
  'use strict';

  $(function() {
    // Simulate a change of date repeat input select, so that it only shows the
    // relevant parts for the selection.
    $('.date-repeat-input select').val('DAILY').change();
    $('.date-repeat-input select').val('WEEKLY').change();

    // Hide different fieldsets if they are not selected. States API fails to do
    // this initially, but when users make changes it will work.
    if (!$('.date-clear input[type="checkbox"]').is(':checked')) {
      $('#repeat-settings-fieldset').hide();
    }
    if (!$('.form-item-field-ding-event-date-und-0-rrule-show-exceptions input[type="checkbox"]').is(':checked')) {
      $('#edit-field-ding-event-date-und-0-rrule-exceptions').hide();
    }
    if (!$('.form-item-field-ding-event-date-und-0-rrule-show-additions input[type="checkbox"]').is(':checked')) {
      $('#edit-field-ding-event-date-und-0-rrule-additions').hide();
    }
  });

})(jQuery);
