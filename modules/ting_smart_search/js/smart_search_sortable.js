(function($) {

  Drupal.behaviors.smartsearchSortable = {
    attach: function(context, settings) {
      var changed = false;
      var material_arr = [];
      $('#field-sss-boost-materials-values .form-item.form-type-textfield input.form-text').each(function(index){
          material_arr[index] = $(this).val();
      });
console.log(material_arr);
      $( ".ting_search-results" ).sortable({
        revert: true,
        scroll: true,
        opacity: 0.5,

        start: function(event, ui) {

          var start = ui.item.index()
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
          console.log(material_arr);
        },
        stop: function(event, ui) {
          var sortedIDs = $(this).sortable( "toArray", {attribute: 'class'} );
          console.log(sortedIDs);
        }

      });
      $( "ol, li" ).disableSelection();
 /**
  * Maybee we can use this if materials are moved out of the list.
*/
      function array_move(arr, old_index, new_index) {
        if (new_index >= arr.length) {
          var k = new_index - arr.length + 1;
          while (k--) {
            arr.push(undefined);
          }
        }
        arr.splice(new_index, 0, arr.splice(old_index, 1)[0]);
        return arr; // for testing
      };

    }
  };

} (jQuery));
