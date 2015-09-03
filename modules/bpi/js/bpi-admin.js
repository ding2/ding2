(function($) {
  $(document).ready(function() {
    if ($.fn.chosen) {
      $('.bpi-facets select[multiple]').each(function(index, el) {
        var no_results_text = $(el).data('no-matches');
        $(el).chosen({
          width: Math.max($(el).width(), 800) + 'px',
          no_results_text: no_results_text,
          allow_single_deselect: true
        });
      });
    }

    $('form.bpi').on('submit', function() {
      this.classList.add('bpi-loading');
    });

    $('#bpi-syndicate-page-form select').change(function() {
      // Trigger jQuery submit to make sure that any on submit handlers are run.
      $(this.form).submit();
    });
  });
})(jQuery);
