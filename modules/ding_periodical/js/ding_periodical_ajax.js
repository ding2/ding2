(function ($) {
  $(document).ready(function(){
    var ids = Drupal.settings.ding_periodical;
    $(ids).each(function (index, info){
      // Make ajax call to get holdings table (opt. use the information fetched
      // by availability for the entity).
      $.ajax({
        type: 'GET',
        url: '/ding_periodical/issues/' + info.ding_entity_id
      }).done(function(data) {
        var div = $('.ding-periodical-issues-ajax.' + info.id);
        if (!data.html || 0 === data.html.length) {
          // No informtion found.
          div.html('<p class="error">' + Drupal.t('No periodical issue information found.') + '</p>');
        }
        else {
          // Insert the information.
          div.parent().html(data.html);

          // Hide all elements.
          $('.ding-periodical-issues li').children('.item-list').hide();

          // Add class to style the list as being expandable.
          $('.ding-periodical-fold').addClass('expand expand-more');
        }
      });

      // Insert tabelles on succes and hide label on failure.
    });
  });
}(jQuery));
