/**
 * @file
 * Use Drupal's built in modal.
 */

(function ($) {
  Drupal.behaviors.ddbCoverUpload = {
    attach: function (context, settings) {
      let dialogLink = '.opener-modal';
      $(dialogLink).click(function() {

        console.log('test');

        let dialogId = '#' + $(this).attr("data-dialog");
        $(dialogId).dialog({
          title: $(dialogId).attr("data-title"),
          autoOpen: false,
          resizable: false,
          draggable: false,
          modal: true,
          dialogClass: 'set-size'
        });

        $(dialogId).dialog('open');
      });
    }
  };
}(jQuery));
