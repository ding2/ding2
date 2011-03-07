(function($) {
  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {

      Drupal.FoldFacetGroup();
    }
  };

  $(window).bind('hashchange', function(e) {
    var hashobj = $.deparam.querystring($.param.fragment());

    $( ' .form-checkbox').live('click', function() {
      if ($(this).attr('checked') == false) {
        // Remove the unchecked facet from the url state
        $.bbq.removeState($(this).closest('fieldset').attr('data'));
      }
      else {
        // Add the checked facet to the url state
        var state = {},
        key = $(this).closest('fieldset').attr('data'),
        value = $(this).val();
        state[key] = value;
        $.bbq.pushState(state, 0);
      }
    });

    for (var key in hashobj) {
      var fieldset_element = key.replace(/\./, "-");
      var facet_element = hashobj[key].replace(/\./, "-");
    }
  });

  Drupal.FoldFacetGroup = function() {
    $(Drupal.settings.dingFacetBrowser.mainElement + ' fieldset.form-wrapper').each(function() {
      var facetGroup = $(this);
      if (facetGroup.find('.form-type-checkbox').size() > Drupal.settings.dingFacetBrowser.showCount) {
        facetGroup.find('.form-type-checkbox').each(function(counter, facetElement) {
          if (counter >= Drupal.settings.dingFacetBrowser.showCount) {
            $(facetElement).hide();
          }
        });
        if (!facetGroup.find('#expand_more').length) {
          facetGroup.append('<span class="expand" id="expand_more">' + Drupal.t('Vis flere') + '</span>');
        }
      }
      else {
      }
    });

    $(Drupal.settings.dingFacetBrowser.mainElement + ' .expand').live('click', function() {
      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();

      facetGroup.find('.form-type-checkbox:' + (clickedKey.id == 'expand_more' ? 'hidden' : 'visible')).each(function(count, facetElement) {
        if (clickedKey.id == 'expand_more' && count < Drupal.settings.dingFacetBrowser.showCount) {
          $(facetElement).slideDown('fast', function() {
            if (facetGroup.find('.form-type-checkbox:visible').size() >= Drupal.settings.dingFacetBrowser.showCount && facetGroup.find('#expand_less').size() == 0 && count % Drupal.settings.dingFacetBrowser.showCount == 0) {
              facetGroup.find('#expand_more').after('<span class="expand" id="expand_less">' + Drupal.t('Luk') + '</span>');
            }
          });
        }
        else if (clickedKey.id == 'expand_less' && count >= Drupal.settings.dingFacetBrowser.showCount) {
          $(facetElement).slideUp('fast', function() {
            if (facetGroup.find('.form-type-checkbox:visible').size() == Drupal.settings.dingFacetBrowser.showCount && facetGroup.find('#expand_less:visible')) {
             facetGroup.find('#expand_less').fadeOut().remove();
            }

          });
        }
      });

    });
  }

  // Since the event is only triggered when the hash changes, we need to trigger
  // the event now, to handle the hash the page may have loaded with.
  $(window).trigger('hashchange');

})(jQuery);
