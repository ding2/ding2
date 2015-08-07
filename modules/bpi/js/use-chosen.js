(function($) {
  $(document).ready(function() {
    $('.bpi-facets select[multiple]').each(function(index, el) {
      var no_results_text = $(el).data('no-matches');
      $(el).chosen({
        width: Math.max($(el).width(), 800) + 'px',
        no_results_text: no_results_text,
        allow_single_deselect: true
      });
    });
  });
})(jQuery);
