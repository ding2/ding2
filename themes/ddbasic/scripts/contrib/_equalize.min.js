/**
 * equalize.js
 * Author & copyright (c) 2012: Tim Svensen
 * Dual MIT & GPL license
 *
 * Page: http://tsvensen.github.com/equalize.js
 * Repo: https://github.com/tsvensen/equalize.js/
 *
 * NOTE:
 * This script has been changed to support Drupal's markup hell.
 * Instead of only finding max height of nearest children of the specified element,
 * it cycles through all descendents.
 * 
 * Furthermore it sets the height of all descendents with a class containing "grid"
 * in the name. This is VERY Latto specific.
 * 
 */
;(function($) {

  $.fn.equalize = function(options) {
    var $containers = this, // this is the jQuery object
        reset       = false,
        equalize,
        type;

    // when options are an object
    if ($.isPlainObject(options)) {
      equalize = options.equalize || 'height';
      reset    = options.reset || false;
    } else { // otherwise, a string was passed in or default to height
      equalize = options || 'height';
    }

    if (!$.isFunction($.fn[equalize])) { return false; }

    // determine if the height or width is being equalized
    type = (equalize.indexOf('eight') > 0) ? 'height' : 'width';

    return $containers.each(function() {
      var $children = $(this).find('*'), // Iterate through all descendents to find the tallest one.
          max = 0; // reset for each container
                 
      $children.each(function() {
        var $element = $(this),
            value;
        if (reset) { $element.css(type, ''); } // remove existing height/width dimension
        value = $element[equalize]();          // call height(), outerHeight(), etc.
        if (value > max) { max = value; }      // update max
      });
      
      $(this).find('*').each(function() {
        var classAttribute = $(this).attr('class') == undefined ? '' : $(this).attr('class');
        if(classAttribute.indexOf('grid') > -1) { // Find all children containing grid in the class.
          $(this).css(type, max +'px');
        }
      });
    });
  };

}(jQuery));