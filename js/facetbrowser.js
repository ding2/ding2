
(function($) {

  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      Drupal.FoldFacetGroup();

      var main_element = $(Drupal.settings.dingFacetBrowser.mainElement);

      // Wrap all facet fieldsets marked as hidden in a container so we can hide
      // em. The link text is show less and will be changed to show more if the
      // cookie is false.
      var show_more = $('<a href="#" class="expand-facets">' + Drupal.t('Show less filters') + '</a>');
      main_element.find('fieldset.hidden').wrapAll('<div id="hidden-facets" />');
      main_element.find('#hidden-facets').after(show_more);

      // Check the cookie.
      if ($.cookie("ding_factbrowers_toggle") != 'true') {
        main_element.find('#hidden-facets').hide();
        show_more.text(Drupal.t('Show more filters'));
      }

      show_more.click(function(e) {
        e.preventDefault();

        // Toggle facts groups and update link/button text.
        main_element.find('#hidden-facets').toggle('fast', function () {
          var visible = $(this).is(':visible');
          show_more.text(
            visible ? Drupal.t('Show less filters') : Drupal.t('Show more filters')
          );

          // Set cookie, so to remember if they where shown.
          $.cookie("ding_factbrowers_toggle", visible);
        });

        return false;
      });

      // Check for click in checkbox, and execute search.
      main_element.find('.form-type-checkbox input').change(function(e) {
        $('body').prepend('<div class="facetbrowser_overlay"><div class="spinner"></div></div>');
        window.location = $(e.target).parent().find('a').attr('href');
      });
    }
  };

  /**
  * Fold facet groups to show only x unselected checkboxes per group.
  */
  Drupal.FoldFacetGroup = function() {

    var main_element = $(Drupal.settings.dingFacetBrowser.mainElement);

    // Add show more button to each facet group and hide some terms.
    main_element.find('fieldset.form-wrapper').each(function() {
      var facetGroup = $(this);

      // Limit the number of visible terms in the group.
      var number_of_terms = Drupal.settings.dingFacetBrowser.number_of_terms;
      var terms_not_checked = facetGroup.find('.form-type-checkbox input:not(:checked)');
      if (terms_not_checked.size() > number_of_terms) {
        terms_not_checked.slice(number_of_terms).parent().hide();
      }

      // Add expand button, if there are more to show.
      if (terms_not_checked.length > number_of_terms) {
        facetGroup.append('<a href="#" class="expand expand-more" id="expand_more">' + Drupal.t('Show more') + '</a>');
      }

      // Add some classes to checkbox wrappers.
      facetGroup.find('.form-type-checkbox input:checked').parent().addClass('selected-checkbox');
      facetGroup.find('.form-type-checkbox input:not(:checked)').parent().addClass('unselected-checkbox');

      // Add some div wrappers around selected and unselected checkboxes.
      facetGroup.find('.selected-checkbox').wrapAll('<div class="selected-checkbox-group" />');
      facetGroup.find('.unselected-checkbox').wrapAll('<div class="unselected-checkbox-group" />');

      // Add a unselect all link.
      if (facetGroup.find('.selected-checkbox-group').length) {
        facetGroup.find('.selected-checkbox-group').append('<a href="#" class="unselect">' + Drupal.t('Remove all selected') + '</a>');
      }

    });

    /**
    * Bind click function to show more and show less links.
    */
    main_element.find('.expand').live('click', function(e) {
      e.preventDefault();

      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();

      facetGroup.find('.form-type-checkbox.unselected-checkbox:' + (clickedKey.id == 'expand_more' ? 'hidden': 'visible')).each(function(count, facetElement) {
        if (clickedKey.id == 'expand_more' && count < Drupal.settings.dingFacetBrowser.number_of_terms) {
          $(facetElement).slideDown('fast', function() {
            if (facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() >= Drupal.settings.dingFacetBrowser.number_of_terms &&
                facetGroup.find('#expand_less').size() === 0 &&
                count % Drupal.settings.dingFacetBrowser.number_of_terms === 0) {
              facetGroup.append('<a href="#" class="expand expand-less" id="expand_less">' + Drupal.t('Show less') + '</a>');
            }
          });
        }
        else if (clickedKey.id == 'expand_less' && count >= Drupal.settings.dingFacetBrowser.number_of_terms) {
          $(facetElement).slideUp('fast', function() {
            if (facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() == Drupal.settings.dingFacetBrowser.number_of_terms &&
                facetGroup.find('#expand_less:visible')) {
              facetGroup.find('#expand_less').fadeOut().remove();
            }
          });
        }
      });

      // Need to make sure we have the correct amount of unselected checkboxes to check against when wanting to remove the show more link.
      var unselectedSize = facetGroup.attr('count')-facetGroup.find('.form-type-checkbox.selected-checkbox').size();

      if ((facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() >= unselectedSize) && (clickedKey.id == 'expand_more')) {
          facetGroup.find('#expand_more').remove();
      }

      if (clickedKey.id == 'expand_less'){
        if (!(facetGroup.find('#expand_more').length)) {
          facetGroup.append('<span class="expand expand-more" id="expand_more">' + Drupal.t('Show more') + '</span>');
        }
      }

      return false;
    });

    /**
    * Bind click function to the unselect all selected checkboxes link.
    */
    main_element.find('.unselect').live('click', function(e) {
      e.preventDefault();

      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();
      var checkedFacets = '';
      facetGroup.find('.form-type-checkbox.selected-checkbox').each(function() {
        var element = $(this);
        // Uncheck checkboxes (for the visual effect).
        element.find('input').click();

        // Find the facets to be deselected and generate new URL.
        var facetMatch = element.find('a').attr('href').match(/&facets\[\]=-facet.*/);
        checkedFacets += facetMatch[0];
        if (checkedFacets) {
          $('body').prepend('<div class="facetbrowser_overlay"><div class="spinner"></div></div>');
          window.location.href += checkedFacets;
        }
      });

      return false;
    });
  };

})(jQuery);


