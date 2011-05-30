(function($){
  $(document).ready(function(){
    var format = ( $.cookie("ding_toggle_format") ) ? $.cookie("ding_toggle_format") : 'short';
    $.cookie("ding_toggle_format", format, { expires: 30 });
    setToggleFormat(format);
  });
})(jQuery);


function setToggleFormat(format) {
  if ( !jQuery("#ding-toggle-format") )
    return false;
  setFormat(format);
  jQuery("#ding-toggle-format").click(function() {
    var toFormat = ( jQuery.cookie("ding_toggle_format") == 'short' ) ? 'long' : 'short';
    return setFormat(toFormat);
  });
}


function setFormat(format) {
  jQuery("#ding-toggle-format").removeClass('ding-toggle-format-long');
  jQuery("#ding-toggle-format").removeClass('ding-toggle-format-short');
  jQuery("#ding-toggle-format").addClass('ding-toggle-format-' + format);
  jQuery("li.search-result").removeClass('ding-format-long');
  jQuery("li.search-result").removeClass('ding-format-short');
  jQuery("li.search-result").addClass('ding-format-' + format);
  jQuery.cookie("ding_toggle_format", format, { expires: 30 });
  return false;
}

