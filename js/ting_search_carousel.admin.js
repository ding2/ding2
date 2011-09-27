
Drupal.behaviors.tingSearchCarouselAdmin = function(context)
{
	Drupal.tingSearchCarouselAdmin.remove();
};

Drupal.tingSearchCarouselAdmin = {};

Drupal.tingSearchCarouselAdmin.remove = function () {
  $('.ting-search-carousel-search-wrap .remove').click(function () {
    $(this).parents('tr').remove();
    return false;
  });
};
