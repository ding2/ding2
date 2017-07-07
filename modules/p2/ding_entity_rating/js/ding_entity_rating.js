/**
 * @file
 * Rating jquery widget
 *
 * This widget allows users to rate library materials.
 */

(function ($) {
  "use strict";

  $.widget("ding.rating", {
    options: {
      'average': 1,
      'submitted': false,
    },

    /**
     * Constructor.
     */
    _create: function() {
      var self = this;

      this.element
        // Add a class for theming.
        .addClass('ding-rating')
        // Prevent double click to select text.
        .disableSelection();
      if(this.options.submitted === false) {
        $('.js-rating-symbol', this.element)
          .hover(this.starMouseIn, this.starMouseOut)
          .bind('click', function (evt) {
            evt.preventDefault();

            var $this = $(this);
            self.sendRating(
              $this.parent().attr('data-ding-entity-rating-path'),
              $this.index() + 1,
              function () {
                $this.addClass('submitted').parent('.ding-entity-rating').addClass('has-submission');
                $this.prevAll('.js-rating-symbol').addClass('submitted');
                $this.nextAll('.js-rating-symbol').removeClass('submitted has-sub');
              }
            );
          });

        $('.ding-entity-rating-clear', this.element).bind('click', function (evt) {
          evt.preventDefault();

          var $this = $(this);
          self.sendRating(
            $this.parent().attr('data-ding-entity-rating-path'),
            0,
            function () {
              $this.parent('.ding-entity-rating')
                .removeClass('has-submission')
                .children('.js-rating-symbol').removeClass('submitted has-sub');
            }
          );
        });
      }
      this._refresh();
    },

    /**
     * Called when created, and later when changing options.
     */
    _refresh: function() {
      this._trigger( "change" );
    },

    /**
     * On mouse in.
     */
    starMouseIn: function() {
      var $this = $(this);
      $this.parent().children('.submitted').addClass('has-sub').removeClass('submitted');
      $this.siblings().removeClass('active');
      $this.addClass('active');
      $this.prevAll().addClass('active');
    },

    /**
     * On mouse out.
     */
    starMouseOut: function() {
      var $this = $(this);
      $this.parent().children('.has-sub').addClass('submitted').removeClass('has-sub');
      $this.removeClass('active');
      $this.siblings().removeClass('active');
    },

    sendRating: function (path, index, callback) {
      var url = Drupal.settings.basePath + 'ding_entity_rating/' + path + '/' + index,
        $dummy = $('<a href="' + url + '"></a>'),
        drupal_ajax = new Drupal.ajax('fake', $dummy, {
          url: url,
          event: 'click',
          progress: { type: 'custom' },
        }),
        ofunc_complete = drupal_ajax.options.complete;

      drupal_ajax.options.complete = function (xmlhttprequest, status) {
        callback();
        return ofunc_complete(xmlhttprequest, status);
      };

      drupal_ajax.beforeSerialize(drupal_ajax.element, drupal_ajax.options);

      $.ajax(drupal_ajax.options);
    },

    /**
     * Events bound via _on are removed automatically revert other
     * modifications here.
     */
    _destroy: function() {
      this.element
        .removeClass( "ding-rating" )
        .enableSelection();
    },

    /**
     * _setOptions is called with a hash of all options that are changing.
     */
    _setOptions: function() {
      // _super and _superApply handle keeping the right this-context.
      if (this._superApply) {
        this._superApply( arguments );
      }
      this._refresh();
    },

    /**
     * _setOption is called for each individual option that is changing.
     */
    _setOption: function( key, value ) {
      this._super( key, value );
    }
  });

  // Drupal behavior.
  Drupal.behaviors.ding_entity_rating = {
    attach: function (context) {
      // Attach rating widget.
      $('.ding-entity-rating, .ding-entity-rating-submitted', context).rating();

      var rating_ids = [];
      $('.ding-entity-rating', context).each(function () {
        rating_ids.push($(this).attr('data-ding-entity-rating-id'));
      });

      if (rating_ids.length > 0) {
        $.ajax('/ding_entity_rating/get', {
          data: {ids: rating_ids},
          dataType: 'json',
          method: 'get',
          success: function (data) {
            for (var i in data) {
              if (data[i] !== false) {
                $('.ding-entity-rating[data-ding-entity-rating-id="' + i + '"] .js-rating-symbol')
                  .eq(data[i])
                  .removeClass('submitted')
                  .prevAll().addClass('submitted')
                  .end().nextAll().removeClass('submitted')
                  .end().parent().addClass('has-submission')
                  .find('.ding-entity-rating-avg').remove();
              }
            }
          }
        });
      }
    }
  };
})(jQuery);
