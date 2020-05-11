/**
 * @file
 */

(function ($) {
  'use strict';

  let uploadAnother = '#js-upload-another';

  /**
   * Change frontend to visualize that upload to cover service has finished.
   *
   * @param uploadNewHref
   *   A url to page one of the form.
   */
  function setCompletedState(uploadNewHref) {
    $(uploadAnother).attr("href", uploadNewHref);
    $(uploadAnother).removeClass('disabled');
    $('.js-spinner').hide();
    $('.js-confirmation').show();
  }

  Drupal.behaviors.ddbCoverUpload = {
    attach: function (context, settings) {
      // Store link url and disable link.
      let uploadNewHref = $(uploadAnother).attr("href");
      $(uploadAnother).removeAttr('href');

      function checkSubmission() {
        $.ajax({
          type: 'get',
          dataType : 'json',
          url: '/admin/config/cover_upload/submitted/check-submission',
          success: function(data) {
            switch (data.status) {
              case 'success':
                setCompletedState(uploadNewHref);
                break;

              case 'error':
                console.log(data);
                $('.js-error .error').html(data.message);
                $('.js-spinner').hide();
                $('.js-error').show();
                break;
            }
          },
        });
      }

      checkSubmission();
    }
  };
}(jQuery));
