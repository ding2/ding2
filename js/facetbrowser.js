
(function($) {

  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      Drupal.FoldFacetGroup();

      if (this.processed) {
        return;
      }
      this.processed = true;
      Drupal.executeSearch();

      $(window).bind('hashchange.pane-ding-facetbrowser', $.proxy(Drupal.facetbrowser, 'eventhandlerDFOperateByURLFragment')).triggerHandler('hashchange.pane-ding-facetbrowser');

      $(document).bind('click.form-checkbox', $.proxy(Drupal.facetbrowser, 'eventHandlerDFOperateClick'));

    }

  };

  Drupal.facetbrowser = Drupal.facetbrowser || { };
  Drupal.facetbrowser.prototype = {};

  Drupal.facetbrowser.eventhandlerDFOperateByURLFragment = function(event) {
    var state = $.bbq.getState();
    if (state) {
      Drupal.executeSearch();
    }
  };

  Drupal.facetbrowser.eventHandlerDFOperateClick = function(event) {
    var $target = $(event.target);
    if ($target.attr('checked')) {
      var state = {};
      var key = $target.closest('fieldset').attr('data');
      var value = $target.val();

      currentValues = $.bbq.getState(key);

      if (currentValues === undefined) {
        currentValues = [];
        currentValues.push(value);
      }
      else if (currentValues.indexOf(value) == -1) {
        currentValues.push(value);
      }
      state[key] = currentValues;
      $.bbq.pushState(state,0);
      // Add the url state to pagers
      $('ul.pager li a').fragment('', $.param.fragment(), 2);
    }
    else {
      // Remove unchecked facet from url state
      var facetmatching = /^edit-([^-]+)-(.+)--/,
      facetstate, newstate = {};
      var facet_identifier = $target[0].id.match(facetmatching);
      var match = facet_identifier[0];
      var facet = facet_identifier[1];
      var id = facet_identifier[2];

      facet = 'facet.' + facet;
      facetstate = $.bbq.getState(facet);

      if (facetstate) {
        newstate[facet] = facetstate.filter(function(x) { return id != x.replace(/ /g, '-'); });

        if (newstate.length === 0) {
          $.bbq.removeState(facet);
        }
        else {
          $.bbq.pushState(newstate);
        }
      }
      $.bbq.removeState($(this).closest('fieldset').attr('data'));
    }
  };

  Drupal.executeSearch = function() {
    Drupal.CheckHashedFacets();
    // $('.pane-ding-facetbrowser').hide();
    $('.search-results').hide();
    // Trigger the form, and execute the search
    $('.pane-ding-facetbrowser input.form-checkbox:checked:first').trigger('change');
    // Add fragments to pager when toggeling facetbrowser
    $('ul.pager li a').fragment('', $.param.fragment(), 2);
    // TODO: Change to use native Drupal ajax function overrides.
    // When then search is complete then show panes again.
    $(document).ajaxComplete(function(e, xhr, settings) {
      $('.pane-ding-facetbrowser').show();
      $('.search-results').show();
    });
  };

  /**
 * Automatic fill facet checkboxes with values from url hashes.
 */
  Drupal.CheckHashedFacets = function() {
    $('.pane-ding-facetbrowser input.form-checkbox').attr('checked', false);
    var hashobj = $.deparam.querystring($.param.fragment());

    if (hashobj) {
      for (var key in hashobj) {
        var element_ids = hashobj[key];
        var facet_type = key.split('.', - 1);
        for (var counter in element_ids) {
          element_id = element_ids[counter];
          $('.pane-ding-facetbrowser input[id^="edit-' + facet_type[1] + '-' + element_id.replace(/ /g, "-") + '"]').attr('checked', true);
        }
      }
    }
  };

  /**
 * Fold facet groups to show only 5 per group.
 */
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
    });

    $(Drupal.settings.dingFacetBrowser.mainElement + ' .expand').live('click', function() {
      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();

      facetGroup.find('.form-type-checkbox:' + (clickedKey.id == 'expand_more' ? 'hidden': 'visible')).each(function(count, facetElement) {
        if (clickedKey.id == 'expand_more' && count < Drupal.settings.dingFacetBrowser.showCount) {
          $(facetElement).slideDown('fast', function() {
            if (facetGroup.find('.form-type-checkbox:visible').size() >= Drupal.settings.dingFacetBrowser.showCount && facetGroup.find('#expand_less').size() === 0 && count % Drupal.settings.dingFacetBrowser.showCount === 0) {
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
  };


})(jQuery);

