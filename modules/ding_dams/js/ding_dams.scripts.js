/**
 * @file
 */
(function ($) {
  "use strict";
  Drupal.behaviors.ding_dams = {
    attach: function (context) {

      $('#media-tabs-wrapper').find('ul > li').click(function () {
        var ele = $(this);
        ele.parent('ul').find('li').removeClass('active');

        if (ele.hasClass('ui-state-active')) {
          ele.addClass('active');
        }

        // Catch the click on a media item
        $('.media-item', context).bind('click', function () {
          // Remove selection from any selected item.
          $('.media-item').removeClass('selected');
          // Set the current item to active
          $(this).addClass('selected');
          // Add this FID to the array of selected files
          var fid = $(this).attr('data-fid');

          // Edit button.
          var edit_button_href = '/file/' + fid + '/edit';
          var $edit_button = $('.form-actions a#edit-media-button');

          if ($edit_button.length === 0) {
            $edit_button = $('<a>')
                .addClass('button')
                .attr('id', 'edit-media-button')
                .attr('target', '_blank')
                .html(Drupal.t('Edit'))
                .appendTo('.form-actions');
          }

          $edit_button
              .attr('href', edit_button_href)
              .show();

          // Track button.
          var track_button_href = '/file/' + fid + '/usage';
          var $track_button = $('.form-actions a#track-media-button');

          if ($track_button.length === 0) {
            $track_button = $('<a>')
                .addClass('button')
                .attr('id', 'track-media-button')
                .attr('target', '_blank')
                .html(Drupal.t('Track'))
                .appendTo('.form-actions');
          }

          $track_button
              .attr('href', track_button_href)
              .show();
        });
      });
    }
  };

  $(document).ready(function () {
    // Set youtube tab as default if search was made.
    if (window.location.hash.length > 0 && window.location.hash === '#media-youtube-search-tab') {
      $('[href="#media-tab-youtube"]').click();
      window.location.hash = '';
    }

    Drupal.theme.prototype.dams_modal = function () {
      var html = '';
      html += '<div id="ctools-modal" class="popups-box">';
      html += '  <div class="ctools-modal-content ctools-modal-dams-modal-content">';
      html += '      <div class="modal-header">';
      html += '        <a class="close close-messages-button" href="#">';
      html += '        </a>';
      html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
      html += '      </div>';
      html += '    <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
      html += '  </div>';
      html += '</div>';
      return html;
    };

  });
})(jQuery);
