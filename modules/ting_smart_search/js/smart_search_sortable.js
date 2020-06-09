(function($) {

  Drupal.behaviors.smartsearchSortable = {
    attach: function(context, settings) {
      var material_arr = [];
      $('#field-sss-boost-materials-values .form-item.form-type-textfield input.form-text').each(function(index){
          material_arr[index] = $(this).val();
      });
      $( ".ting_search-results" ).sortable({
        revert: true,
        scroll: true,
        opacity: 0.5,

        start: function(event, ui) {

          $(this).attr('data-previndex', ui.item.index());
        },
        update: function(event, ui) {

          var end = ui.item.index();
          var start = $(this).attr('data-previndex');
          $(this).removeAttr('data-previndex');
          $('.ting_search-results .list-item').each(function(n,v){
            var material = decodeURIComponent($('a', this).attr('href').split(/[/ ]+/).pop().split('?').shift());

            if ( start < material_arr.length && n == end ) {
              var temp_mat = material_arr.splice(start, 1)[0];
              material_arr.splice(end,0,material);
            } else if (n == end) {
                material_arr.splice(end,0, material);
              }
          });
          $('.ting_search-results .list-item').each(function(n,v){
            $('input#edit-field-sss-boost-materials-und-'+n+'-value').val(material_arr[n]);
          });
        },
        stop: function(event, ui) {
          var sortedIDs = $(this).sortable( "toArray", {attribute: 'class'} );
        }

      });
      $( "ol, li" ).disableSelection();
    }
  };

} (jQuery));
