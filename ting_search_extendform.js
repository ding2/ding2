
(function($){

  $(document).ready(function(){
    Drupal.setSelectedLabel();
  });

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

  Drupal.behaviors.toggleSize = {
    attach: function (context, settings) {
      $('.form-item-size').find('input').change(function () {
        Drupal.setSelectedLabel();
        var action = $("#search-controls-form").attr("action").split('?');
        action = action[0] + '?sort=' + $('#edit-sort').val() + '&size=' + $("input[name='size']:checked").val();
        document.location.href = action;
      });
    }
  };

  Drupal.behaviors.toggleSort = {
    attach: function (context, settings) {
      $('#edit-sort').change(function () {
        var action = $("#search-controls-form").attr("action").split('?');
        action = action[0] + '?sort=' + $('#edit-sort').val() + '&size=' + $("input[name='size']:checked").val();
        document.location.href = action;
      });
    }
  };

  Drupal.setSelectedLabel = function () {
    $('.form-item-size').find('label').removeClass('labelSelected');
    $('input[name=size]').filter(':checked').parent().find('label').addClass('labelSelected');
  }

}(jQuery));

function extendSearch(id,val) {
  document.getElementById(id).value = val;
}