/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */

(function (scope, $) {
  'use strict';

  var
    POPUPBAR_CLASS_OPEN = 'popupbar-is-open',
    POPUPBAR_CLASS_SELECTED = 'selected',

    /**
     * The jQuery popupbar object.
     */
    _$popupbar = null,

    /**
     * The jQuery container object.
     */
    _$container = null;

  if (scope.ddbasic === undefined) {
    scope.ddbasic = {};
  }

  /**
   * The popupbar object.
   */
  scope.ddbasic.popupbar = {
    /**
     * Get the popupbar jQuery object.
     */
    bar: function () {
      if (_$popupbar === null) {
        _$popupbar = $('#popupbar');

        if (_$popupbar.length === 0) {
          _$popupbar = $('<div id="popupbar" class="popupbar" />').appendTo($('body'));
        }
      }

      return _$popupbar;
    },

    /**
     * Get the popupbar container jQuery object.
     */
    container: function () {
      if (_$container === null) {
        _$container = this.bar().children('popupbar-container');

        if (_$container.length === 0) {
          _$container = $('<div class="popupbar-container" />').appendTo(this.bar());

          var self = this;
          $('<a href="#" class="popupbar-close">' + Drupal.t('Close') + '</a>')
            .on('click', function (evt) {
              evt.preventDefault();
              self.close();
            })
            .appendTo(_$container);
        }
      }

      return _$container;
    },

    /**
     * Set the content of the popupbar.
     *
     * This actually sets the content of a specific popupbar-content element
     * keyed by it's name.
     *
     * @param {string} name
     *   Identifier of the popup content.
     * @param {jQuery} $element
     *   The content of the popup.
     * @param {boolean} dont_open [description]
     *   Automatically open upthe popupbar.
     * @param {function} onclose   [description]
     *   function to be called when popupbar is closed while displaying this
     *   specific content.
     *
     * @return {jQuery}
     *   The popupbar content jQuery object.
     */
    set: function (name, $element, dont_open, onclose) {
      var
        $container = this.container(),
        $content = $('#popupbar-' + name);

      if ($content.length === 0) {
        $content = $('<div id="popupbar-' + name + '" class="popupbar-content" />').appendTo($container);
      }

      if ($element !== null) {
        $content.children().remove().end().append($element);
      }

      $container.children('.' + POPUPBAR_CLASS_SELECTED).removeClass(POPUPBAR_CLASS_SELECTED);
      $content.addClass(POPUPBAR_CLASS_SELECTED);

      this.bar().height($content.outerHeight(true));

      if (dont_open !== true) {
        var self = this;
        setTimeout(function () {
          self.open();
        }, 16);
      }

      $content.data('onclose', onclose);

      return $content;
    },

    /**
     * Close the popupbar.
     */
    close: function () {
      var
        $content = this.container().children('.' + POPUPBAR_CLASS_SELECTED),
        onclose = $content.data('onclose');

      if (typeof onclose === 'function' && onclose() === false) {
        return this;
      }

      $('body')
        .removeClass(POPUPBAR_CLASS_OPEN)
        .unbind('click.popupbar');

      $(window).trigger('dingpopup-close');

      return this;
    },

    /**
     * Open the popupbar.
     */
    open: function () {
      var self = this;

      $('body')
        .addClass(POPUPBAR_CLASS_OPEN)
        .bind('click.popupbar', function (evt) {
          if ($(evt.target).closest('#popupbar').length === 0) {
            self.close();
          }
        });

      return this;
    },

    /**
     * Toggle the popupbar.
     */
    toggle: function () {
      if (!$('body').hasClass(POPUPBAR_CLASS_OPEN)) {
        this.open();
      } else {
        this.close();
      }

      return this;
    }
  };

})(this, jQuery);
