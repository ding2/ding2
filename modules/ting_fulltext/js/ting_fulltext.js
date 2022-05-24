(function ($) {
    "use strict";

    var SearchExpansionResults = function (response) {
        $("#ting-lektor-fulltext").html(response);
    }

    Drupal.behaviors.fullTextReview = {
        attach: function (context) {
            $.get(Drupal.settings.tingFulltext.url, null, SearchExpansionResults);
        }
    };

})(jQuery);
