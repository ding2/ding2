
(function($){

  $.TingExtendedForm = {};
  $.TingExtendedForm.showExtended = false;

  Drupal.behaviors.showExtendedForm = {
    // 'Show advanced search' link onClick function
    attach: function (context, settings) {
      $('#extend-form-show', context).click(function () {
        if ( ! $.TingExtendedForm.showExtended ) {
          $("#search-extend-form").removeClass('extend-form-show');
          $("#search-extend-form").addClass('extend-form-show');
          $.TingExtendedForm.showExtended = true;
        } else {
          $("#search-extend-form").removeClass('extend-form-show');
          $.TingExtendedForm.showExtended = false;
        }
        return false;
      });
    }
  };

  Drupal.behaviors.hideExtendedForm = {
    // 'Hide Advanced search' link onClick function
    attach: function (context, settings) {
      $('#extend-form-hide', context).click(function () {
        $("#search-extend-form").removeClass('extend-form-show');
        return false;
      });
    }
  };

  Drupal.behaviors.readyExtendedForm = {
    // If there's no 'Show advanced search' link, set display: block.
    attach: function (context, settings) {
      $('#extend-form', context).ready(function () {
        if ( !$('#extend-form-show') ) {
          $("#search-extend-form").addClass('extend-form-show');
        }
      });
    }
  };

}(jQuery));

function extendSearch(id,val) {
  document.getElementById(id).value = val;
}