/**
 * @file
 */

(function ($) {
  Drupal.behaviors.ding_dams = {
    attach: function (context) {

      $('#media-tabs-wrapper > ul > li').click(function() {
        var ele = $(this);
        ele.parent('ul').find('li').removeClass('active');

        if (ele.hasClass('ui-state-active')) {
          ele.addClass('active');
        }
      });
      $('#media-tabs-wrapper > ul > li.ui-state-active').addClass('active');

      $('.form-actions #track-media-button', context).remove();
      $('.form-actions #edit-media-button', context).remove();
      // Catch the click on a media item
      $('.media-item', context).bind('click', function (e) {
        var empty_settings = [];
        // Remove all currently selected files
        $('.media-item').removeClass('selected');
        // Set the current item to active
        $(this).addClass('selected');
        // Add this FID to the array of selected files
        var fid = $(this).attr('data-fid');

        // Edit button
        var x = $('<a>');
        x.addClass('button').attr('href', '/file/' + fid + '/edit').attr('id', 'edit-media-button').html('Edit');
        x.attr('target', '_blank');
        $('.form-actions', context).append(x);
        $('.form-actions #edit-media-button', context).show();

        Drupal.behaviors.AJAX.attach(x, empty_settings);

        // Track button
        var y = $('<a>');
        y.addClass('button').attr('id', 'track-media-button').attr('href', '/file/' + fid + '/usage').attr('target','_blank').html('Track');
        $('.form-actions', context).append(y);
        $('.form-actions #track-media-button', context).show();
        Drupal.behaviors.AJAX.attach(y, empty_settings);
      });

    }
  };

  $(document).ready(function() {
    // Set youtube tab as default if search was made.
    if (window.location.hash.length > 0 && window.location.hash == '#media-youtube-search-tab') {
      $('[href="#media-tab-youtube"]').click();
      window.location.hash = '';
    }
  });
})(jQuery);
