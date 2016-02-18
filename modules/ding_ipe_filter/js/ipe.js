(function ($) {
  "use strict";

  $(document).on('click', '.ipe-trigger', function() {
    var links = '#ipe-add-' + $(this).attr('target_region');
    var link_offset = Math.abs(parseInt(screen.width) - parseInt($(this).parent().offset().left));
    var direction = (link_offset > 800) ? 'left' : 'right';
    var options = {
      'my': direction + ' top',
      'at': 'left bottom',
      'of': $(this),
      'offset': '0 3'
    };
    $(links).fadeToggle('fast').position(options);
    return false;
  });

  $(document).on('mouseleave', '.ipe-popup', function() {
    $(this).fadeToggle('fast');
  });
})(jQuery);
