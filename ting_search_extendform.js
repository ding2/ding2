(function($) {

  $(document).ready(function() {
    Drupal.setSelectedLabel();
    Drupal.extendedFormOnload();
    Drupal.extendedQueryDisplay();
  });

  $.TingExtendedForm = {};
  $.TingExtendedForm.showExtended = false;

  Drupal.behaviors.showExtendedForm = {
    // 'Show advanced search' link onClick function
    attach: function(context, settings) {
      $('#extend-form-show', context).click(function() {
        if (!$.TingExtendedForm.showExtended) {
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
    attach: function(context, settings) {
      $('#extend-form-hide', context).click(function() {
        $("#search-extend-form").removeClass('extend-form-show');
        return false;
      });
    }
  };

  Drupal.behaviors.readyExtendedForm = {
    // If there's no 'Show advanced search' link, set display: block.
    attach: function(context, settings) {
      $('#extend-form', context).ready(function() {
        if (!$('#extend-form-show')) {
          $("#search-extend-form").addClass('extend-form-show');
        }
      });
    }
  };

  Drupal.behaviors.toggleSize = {
    attach: function(context, settings) {
      $('.form-item-size').find('label').click(function() {
        var radioVal = $('#' + $(this).attr('for')).val();
        $('#' + $(this).attr('for')).attr('checked', true);
        Drupal.setSelectedLabel();
        var action = document.location.href;
        var query_delimiter = action.indexOf('?') > 0 ? '&' : '?';
        action = action + query_delimiter + 'sort=' + $('#edit-sort').val() + '&size=' + $("input[name='size']:checked").val();
        document.location.href = action;
      });
    }
  };

  Drupal.behaviors.toggleSort = {
    attach: function(context, settings) {
      $('#edit-sort').change(function() {
        var action = document.location.href;
        var query_delimiter = action.indexOf('?') > 0 ? '&' : '?';
        action = action + query_delimiter + 'sort=' + $('#edit-sort').val() + '&size=' + $("input[name='size']:checked").val();
        document.location.href = action;
      });
    }
  };

  Drupal.behaviors.setExtendedFormCreator = {
    attach: function(context, settings) {
      $('#edit-extendform-creator').change(function() {
        $('#extend_search_creator').val($('#edit-extendform-creator').val());
      });
    }
  };

  Drupal.behaviors.setExtendedFormTitle = {
    attach: function(context, settings) {
      $('#edit-extendform-title').change(function() {
        $('#extend_search_title').val($('#edit-extendform-title').val());
      });
    }
  };

  Drupal.behaviors.setExtendedFormSubject = {
    attach: function(context, settings) {
      $('#edit-extendform-subject').change(function() {
        $('#extend_search_subject').val($('#edit-extendform-subject').val());
      });
    }
  };

  Drupal.behaviors.setExtendedFormSubmit = {
    attach: function(context, settings) {
      $('#search-extend-form').keypress(function(e) {
        c = e.which ? e.which: e.keyCode;
        if (c == 13) {
          $('#extend_search_creator').val($('#edit-extendform-creator').val());
          $('#extend_search_title').val($('#edit-extendform-title').val());
          $('#extend_search_subject').val($('#edit-extendform-subject').val());
          $('#search-block-form').submit();
          return false;
        }
      });
    }
  };

  Drupal.setSelectedLabel = function() {
    $('.form-item-size').find('label').removeClass('labelSelected');
    $('input[name=size]').filter(':checked').parent().find('label').addClass('labelSelected');
  };

  Drupal.extendedFormOnload = function() {
    $('#edit-extendform-creator').val($('#extend_search_creator').val());
    $('#edit-extendform-title').val($('#extend_search_title').val());
    $('#edit-extendform-subject').val($('#extend_search_subject').val());
  };
  
  Drupal.extendedQueryDisplay = function() {
    
    var queryText = $("input").filter("[name='search_block_form']").val()
    // var queryText = $('#edit-search-block-form--2').val(); 

    if ( $('#extend_search_creator').val() ) {
      if ( queryText )
        queryText += ' AND ';
      queryText += $('label').filter("[for='edit-extendform-creator']").text() + ' = ';
      queryText += $('#extend_search_creator').val();
    }

    if ( $('#extend_search_title').val() ) {
      if ( queryText )
        queryText += ' AND ';
      queryText += $('label').filter("[for='edit-extendform-title']").text() + ' = ';
      queryText += $('#extend_search_title').val();
    }

    if ( $('#extend_search_subject').val() ) {
      if ( queryText )
        queryText += ' AND ';
      queryText += $('label').filter("[for='edit-extendform-subject']").text() + ' = ';
      queryText += $('#extend_search_subject').val();
    }

    $('#search-query-string').text(queryText);

  };

} (jQuery));

