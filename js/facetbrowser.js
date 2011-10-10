
(function($) {

  Drupal.behaviors.facetbrowser = {
    attach: function(context, settings) {
      Drupal.FoldFacetGroup();

      // Check for click in checkbox, and execute search
      $(Drupal.settings.dingFacetBrowser.mainElement + ' .form-type-checkbox input').change(function(e) {
        $('body').prepend('<div class="facetbrowser_overlay"><div class="spinner"></div></div>');
        window.location = $(e.target).parent().find('a').attr('href');
      });
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

	if( (facetGroup.find('.form-type-checkbox:visible').size() >= facetGroup.attr('count')) && (clickedKey.id == 'expand_more') ) {
	    facetGroup.find('#expand_more').remove();	    
	}
	
	if( clickedKey.id == 'expand_less' ){
	    if( !(facetGroup.find('#expand_more').length) ) {	
		facetGroup.append('<span class="expand" id="expand_more">' + Drupal.t('Vis flere') + '</span>');
	    }
	}
    });
};


})(jQuery);


