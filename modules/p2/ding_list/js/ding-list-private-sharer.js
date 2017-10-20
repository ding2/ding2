/**
 * @file
 * Share a private list handling
 */
(function ($) {
  "use strict";

  var handler;

  /**
   * Handle private sharer command.
   */
  Drupal.ajax.prototype.commands.ding_list_private_sharer = function (ajax, response, status) {
    if (response.result === true) {
      sharer(response.community);
      ddbasic.popupbar.close();
    }
  };

}(jQuery));
