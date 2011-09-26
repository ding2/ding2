
(function($) {

  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      Drupal.FoldFacetGroup();

      if (this.processed) {
        return;
      }
      this.processed = true;

      $(window).bind('hashchange.pane-ding-facetbrowser', $.proxy(Drupal.facetbrowser, 'eventhandlerDFOperateByURLFragment')).triggerHandler('hashchange.pane-ding-facetbrowser');
      $(document).bind('click.form-checkbox', $.proxy(Drupal.facetbrowser, 'eventHandlerDFOperateClick'));
    }

  };

  Drupal.facetbrowser = Drupal.facetbrowser || { };
  Drupal.facetbrowser.prototype = {};

  Drupal.facetbrowser.eventhandlerDFOperateByURLFragment = function(event) {
    if (!Drupal.facetbrowser.clicking) {
      Drupal.executeSearch();
    }

    Drupal.facetbrowser.clicking = false;
  };

  Drupal.facetbrowser.idToAttributeString = function(id) {
    // replace spaces with dashes and strip all characters which are not dash, underscore, or in the ranges a-z or 0-9
    return id.replace(/ /g, '-').replace(/[^a-z0-9-_]/g,'');
  };

  Drupal.facetbrowser.eventHandlerDFOperateClick = function(event) {
    var $target = $(event.target);

    if ($target.attr('checked')) {
      // a checkbox has been marked by clicking
      Drupal.facetbrowser.clicking = true;
      var state = {};
      var key = $target.closest('fieldset').attr('data').toLowerCase();
      var value = $target.val();
      var currentValues = $.bbq.getState(key);

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

      if (facet_identifier) {
        // a checkbox has been unmarked by clicking
        Drupal.facetbrowser.clicking = true;
        var match = facet_identifier[0];
        var facet = facet_identifier[1];
        var id = facet_identifier[2];

        facet = 'facet.' + facet;
        facetstate = $.bbq.getState(facet);

        if (facetstate) {
          newstate[facet] = facetstate.filter(function(x) { return id != Drupal.facetbrowser.idToAttributeString(x); });

          if (newstate[facet].length === 0) {
            $.bbq.removeState(facet);
          }
          else {
            $.bbq.pushState(newstate);
          }
        }
      }

      $('ul.pager li a').fragment('', $.param.fragment(), 2);
    }
  };

  Drupal.executeSearch = function() {
    Drupal.CheckHashedFacets();
    // $('.pane-ding-facetbrowser').hide();
    $('.search-results').hide();
    var hasfacets = !$.isEmptyObject($.bbq.getState());
    var firstsearch = Drupal.facetbrowser.clicking === undefined;

    if (!firstsearch || hasfacets) {
      // Trigger the form, and execute the search
      $('.pane-ding-facetbrowser input.form-checkbox:first').trigger('change');
    }

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
          var element_id = element_ids[counter];
          var id_string = Drupal.facetbrowser.idToAttributeString(element_id); 
          var filter_func = function(index) {
                              var r = new RegExp(id_string + "(--[0-9]+)?$");
                              return $(this).attr('id').match(r);
                            };
          var id = $('.pane-ding-facetbrowser input[id^="edit-' + facet_type[1] + '-' + id_string + '"]').filter(filter_func);
          id.attr('checked', true);
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

