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

  Drupal.behaviors.toggleSort = {
    attach: function(context, settings) {
      $('#edit-sort').change(function() {
        $('#ting-search-sort-form').trigger("submit");
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

