
(function($) {

  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      Drupal.FoldFacetGroup();

      var main_element = Drupal.settings.dingFacetBrowser.mainElement;
      
      // Wrap all facet fieldsets marked as hidden in a container so we can hide em.
      $(main_element + ' fieldset.hidden').wrapAll('<div id="hidden-facets" />');
      $(main_element + ' #hidden-facets').after('<span class="expand-facets">' + Drupal.t('Show more filters') + '</span>');
      $(main_element + ' #hidden-facets').hide();

      $(main_element + ' .expand-facets').live('click', function() {
        $(main_element + ' #hidden-facets').toggle('fast', function () {
          $(main_element + ' .expand-facets').text(
            $(this).is(':visible') ? Drupal.t('Show less filters') : Drupal.t('Show more filters')
          );
        });
      });

      // Check for click in checkbox, and execute search.
      $(main_element + ' .form-type-checkbox input').change(function(e) {
        $('body').prepend('<div class="facetbrowser_overlay"><div class="spinner"></div></div>');
        window.location = $(e.target).parent().find('a').attr('href');
      });
    }
  };

  /**
  * Fold facet groups to show only 5 unselected checkboxes per group.
  */
  Drupal.FoldFacetGroup = function() {
    
    var main_element = Drupal.settings.dingFacetBrowser.mainElement;
    
    $(main_element + ' fieldset.form-wrapper').each(function() {
      var facetGroup = $(this);
      console.log(Drupal.settings.dingFacetBrowser.number_of_terms)
      if (facetGroup.find('.form-type-checkbox input:not(:checked)').size() > Drupal.settings.dingFacetBrowser.number_of_terms) {
        facetGroup.find('.form-type-checkbox input:not(:checked)').each(function(counter, facetElement) {
          if (counter >= Drupal.settings.dingFacetBrowser.number_of_terms) {
            $(facetElement).parent().hide();
          }
        });
        if (!facetGroup.find('#expand_more').length) {
          facetGroup.append('<span class="expand" id="expand_more">' + Drupal.t('Show more') + '</span>');
        }
      }
      
      // Add some classes to checkbox wrappers.
      facetGroup.find('.form-type-checkbox input:checked').parent().addClass('selected-checkbox');
      facetGroup.find('.form-type-checkbox input:not(:checked)').parent().addClass('unselected-checkbox');
      
      //Add some div wrappers around selected and unselected checkboxes.
      facetGroup.find('.selected-checkbox').wrapAll('<div class="selected-checkbox-group" />');
      facetGroup.find('.unselected-checkbox').wrapAll('<div class="unselected-checkbox-group" />');
      // Add a unselect all link.
      if (facetGroup.find('.selected-checkbox-group').length) {
        facetGroup.find('.selected-checkbox-group').append('<span class="unselect">' + Drupal.t('Remove all selected') + '</span>');
      }

    });

    /**
    * Bind click function to show more and show less links.
    */
    $(main_element + ' .expand').live('click', function() {
      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();

      facetGroup.find('.form-type-checkbox.unselected-checkbox:' + (clickedKey.id == 'expand_more' ? 'hidden': 'visible')).each(function(count, facetElement) {
        if (clickedKey.id == 'expand_more' && count < Drupal.settings.dingFacetBrowser.number_of_terms) {
          $(facetElement).slideDown('fast', function() {
            if (facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() >= Drupal.settings.dingFacetBrowser.number_of_terms && facetGroup.find('#expand_less').size() === 0 && count % Drupal.settings.dingFacetBrowser.number_of_terms === 0) {
              facetGroup.append('<span class="expand" id="expand_less">' + Drupal.t('Show less') + '</span>');
            }
          });
        }
        else if (clickedKey.id == 'expand_less' && count >= Drupal.settings.dingFacetBrowser.number_of_terms) {
          $(facetElement).slideUp('fast', function() {
            if (facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() == Drupal.settings.dingFacetBrowser.number_of_terms && facetGroup.find('#expand_less:visible')) {
              facetGroup.find('#expand_less').fadeOut().remove();
            }

          });
        }
      });
      
      // Need to make sure we have the correct amount of unselected checkboxes to check against when wanting to remove the show more link.
      var unselectedSize = facetGroup.attr('count')-facetGroup.find('.form-type-checkbox.selected-checkbox').size();
      
      if( (facetGroup.find('.form-type-checkbox.unselected-checkbox:visible').size() >= unselectedSize) && (clickedKey.id == 'expand_more') ) {
          facetGroup.find('#expand_more').remove();
      }

      if( clickedKey.id == 'expand_less' ){
        if( !(facetGroup.find('#expand_more').length) ) {
          facetGroup.append('<span class="expand" id="expand_more">' + Drupal.t('Show more') + '</span>');
        }
      }
    });

    /**
    * Bind click function to the unselect all selected checkboxes link.
    */
    $(main_element + ' .unselect').live('click', function() {
      var clickedKey = this;
      var facetGroup = $(clickedKey).parent();
      var checkedFacets = '';
      facetGroup.find('.form-type-checkbox.selected-checkbox').each(function(count, facetElement) {
        // uncheck checkboxes (for the visual effect).
        $(facetElement).find('input').click();
        // Find the facets to be deselected and generate new URL.
        facetMatch = $(facetElement).find('a').attr('href').match(/&facets\[\]=-facet.*/);
        checkedFacets += facetMatch[0];
        if (checkedFacets) {
          $('body').prepend('<div class="facetbrowser_overlay"><div class="spinner"></div></div>');
          window.location = window.location.href + checkedFacets;
        }
      });
    });
  };

})(jQuery);


