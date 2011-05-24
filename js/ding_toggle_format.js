(function($){
  $(document).ready(function(){
    setToggleFormat();
  });
  var format = ( $.cookie("ding_toggle_format") ) ? $.cookie("ding_toggle_format") : 'short';
  $.cookie("ding_toggle_format", format);
})(jQuery);


function setToggleFormat() {
  if ( !document.getElementById('ding-toggle-format') )
    return false;
  document.getElementById('ding-toggle-format').onclick = toggleFormat;
}

function toggleFormat() {
  var toFormat = ( jQuery.cookie("ding_toggle_format") == 'short' ) ? 'long' : 'short';
  mySwitchClassname (this,'ding-toggle-format-' + jQuery.cookie("ding_toggle_format"),'ding-toggle-format-' + toFormat);
  jQuery.cookie("ding_toggle_format", toFormat);
  return false;
}
