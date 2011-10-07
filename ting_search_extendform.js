(function($) {

  $(document).ready(function() {
    Drupal.setSelectedLabel();
    Drupal.extendedQueryDisplay();
  });

  $.TingExtendedForm = {};
  $.TingExtendedForm.showExtended = false;


  Drupal.behaviors.clearExtendForm = {
      attach:function(context, settings) {
          $('#extend-form-clear', context).click(function() {
              $("#edit-creator").val('');
              $("#edit-title").val('');
              $("#edit-subject").val('');
              $("#edit-search-block-form--2").val('');
              return false;
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

  Drupal.setSelectedLabel = function() {
    $('.form-item-size').find('label').removeClass('labelSelected');
    $('input[name=size]').filter(':checked').parent().find('label').addClass('labelSelected');
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

