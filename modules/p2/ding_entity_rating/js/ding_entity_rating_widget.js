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
          .focusin(this.starMouseIn)
          .focusout(this.starMouseOut)
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
          })
          .parent().children('.submitted').addClass('js-default-sub');

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
     * Reset the stars.
     */
    reset: function () {
      this.element.removeClass('has-submission')
        .children().removeClass('submitted')
        .filter('.js-default-sub').addClass('submitted');
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
      var current_path = window.location.pathname;
      var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ding_entity_rating/' + path + '/' + index + '?destination=' + current_path,
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

  /**
   * Command to reset the stars on a rating.
   */
  Drupal.ajax.prototype.commands.ding_entity_rating_reset = function (ajax, response) {
    var $element = $('.ding-entity-rating[data-ding-entity-rating-id="' + response.entity_id + '"]');

    if (response.on_popup_close) {
      $(window).one('dingpopup-close', function () {
        $element.rating('reset');
      });
      return;
    }

    $element.rating('reset');
  };
})(jQuery);
