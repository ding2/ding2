
/**
 * Behaviour to set up the search carousel.
 */
Drupal.behaviors.tingSearchCarousel = function(context) {
  $('.ting-search-carousel').each(function() {
    var carousel = $(this);
    carousel.find('.search-results .active ul:not(:has(li))').each(function(i) {
      Drupal.tingSearchCarousel.initCarousel(this);
    });
    carousel.find('.search-controller li').each(function(i) {
      $(this).click(function() {
        Drupal.tingSearchCarousel.setActiveCarousel(carousel, i);
      });
    });
  });
}

Drupal.tingSearchCarousel = {};
Drupal.tingSearchCarousel.prevState = null;

Drupal.tingSearchCarousel.initCarousel = function(resultList) {
  $(resultList).jcarousel({
    vertical: false, //
    scroll: 6, //amount of items to scroll by
    animation: "slow", // slow - fast
    auto: "0", //autoscroll in seconds
    wrap: "last",
    itemLoadCallback: Drupal.tingSearchCarousel.itemLoad,
    buttonNextCallback: Drupal.tingSearchCarousel.buttonNext
  });
};

Drupal.tingSearchCarousel.itemLoad = function(carousel, state) {
  // Only consider more search results when user presses next. Previous posts have already been loaded
  // HACK: jCarousel triggers 'prev' when clicking next button the first time.
  // Handle this by keeping track of previous state.
  if (state != 'prev' || Drupal.tingSearchCarousel.prevState == 'init') {
    var start = (state != 'init') ? carousel.last : 0;

    //Only load items if they haven't been loaded already
    if (carousel.size() < start+Drupal.settings.tingSearchCarousel.resultsPerPage) {
      var index = Drupal.tingSearchCarousel.activeIndex(carousel.container);
      if (state == 'init') {
        Drupal.tingSearchCarousel.setLoading(carousel.container, true);
      }

      jQuery.get(Drupal.settings.basePath + 'ting_search_carousel/results/ahah/' + index + '/' + start + '/' + Drupal.settings.tingSearchCarousel.resultsPerPage, function(data, status) {
        Drupal.tingSearchCarousel.setLoading(carousel.container, false);

        //add new items
        var size = start;
        $('<ul>' + data + '</ul>').find('li').each(function(i) {
          carousel.add(start + i, $(this).html());
          size++;
        });

        //update size with number of added items;
        (size > start) ? carousel.size(size) : carousel.inTail = true;

        //reset carousel position on init
        if (state == 'init') {
          carousel.scroll(0);
        }
      });
    }
  }

  Drupal.tingSearchCarousel.prevState = state;
};

Drupal.tingSearchCarousel.activeIndex = function(carousel) {
  var searches = $(carousel).parents('.ting-search-carousel').find('.search-controller li');
  return searches.index(searches.parent().find('.active').get(0));
};

/**
 * Switch between the carousel tabs.
 */
Drupal.tingSearchCarousel.setActiveCarousel = function(carousel, index) {
  $carousel = $(carousel);
  $carousel.find('.search-controller li').removeClass('active');
  $carousel.find('.search-controller li:eq(' + index + ')').addClass('active');

  $carousel.find('.search-results > li:eq(' + index + ') ul:not(:has(li))').each(function(i) {
    Drupal.tingSearchCarousel.initCarousel(this);
  });

  $carousel.find('.search-results > li').removeClass('active');
  $carousel.find('.search-results > li:eq(' + index + ')').addClass('active');
};

/**
 * Set the loading class to make the spinner appear.
 */
Drupal.tingSearchCarousel.setLoading = function(carousel, loading) {
  $(carousel).parents('.ting-search-carousel').find('.search-results').each(function() {
    (loading) ? $(this).addClass('loading') : $(this).removeClass('loading');
  });
};

