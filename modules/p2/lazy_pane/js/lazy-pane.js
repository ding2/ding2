
/**
 * @file
 * Responsible for tracking lazy panes and replacing them through AJAX
 *
 * @todo Horrible, horrible looking code. Improve me!
 */

(function ($) {
  "use strict";

  var lazyPaneAJAX = {},
      lazyPanes = [];

  // Register to events
  // --------------------------------------------------------------------------

  Drupal.behaviors.lazyPaneLoad = {
    attach: function () {

      var $lazy_panes = $('.lazy-pane-placeholder').not('.processed'),
          ids = [];

      if ($lazy_panes.length) {
        $.each($lazy_panes, function () {
          var id = $(this).data('lazy-pane-id');

          switch ($(this).data('lazy-pane-load-strategy')) {
            case 'page-loaded':
              ids.push(id);
              break;

            case 'pane-visible':
              lazyPanes.push(this);
              break;
          }

          $(this).addClass('processed');
        });

        lazyPaneAJAX.request(ids);
        lazyPaneAJAX.checkPanesVisibility();
      }
    }
  };

  $(window).scroll(function () {
    lazyPaneAJAX.checkPanesVisibility();
  });

  $(window).resize(function () {
    lazyPaneAJAX.checkPanesVisibility();
  });

  // lazyPaneAJAX
  // --------------------------------------------------------------------------

  /**
   * Checks if panes are visible on the viewport, and requests them if they are.
   */
  lazyPaneAJAX.checkPanesVisibility = function () {
    if (!lazyPanes.length) {
      return;
    }

    var ids = [],
        w_width = $(window).width(),
        w_height = $(window).height(),
        w_top = $(window).scrollTop(),
        w_left = $(window).scrollLeft(),
        visible_y = w_top + w_height,
        visible_x = w_left + w_width,
        lazyPanesCopy = lazyPanes.slice(0);

    $.each(lazyPanesCopy, function () {
      var request = false,
          offset = $(this).offset();

      if (visible_y >= offset.top && visible_x >= offset.left) {
        request = true;
      }

      if (request) {
        ids.push($(this).data('lazy-pane-id'));
        lazyPanes.splice($.inArray(this, lazyPanes), 1);
      }
    });

    if (ids.length) {
      lazyPaneAJAX.request(ids);
    }
  };

  /**
   * Makes an AJAX request to load the lazy panes.
   *
   * @param ids
   *  An array of lazy-pane ids.
   */
  lazyPaneAJAX.request = function (ids) {
    if (!ids.length) {
      return;
    }

    var url = Drupal.settings.basePath + Drupal.settings.pathPrefix + 'lazy-pane/ajax';
    var data = $.extend({'lazy_pane_ids[]': ids}, {'lazy_pane_get' : this.getURLParams()});

    data['ajax_page_state[theme]'] = Drupal.settings.ajaxPageState.theme;
    data['ajax_page_state[theme_token]'] = Drupal.settings.ajaxPageState.theme_token;
    data['lazy_pane_current_path'] = Drupal.settings.lazy_pane.current_path;

    for (var key in Drupal.settings.ajaxPageState.css) {
      data['ajax_page_state[css][' + key + ']'] = 1;
    }

    for (var key in Drupal.settings.ajaxPageState.js) {
      data['ajax_page_state[js][' + key + ']'] = 1;
    }

    $.post(url, data, function (response, status) {
      lazyPaneAJAX.success(response, status);
    }, 'json');
  };

  /**
   * Processes a successful lazy-pane AJAX response.
   */
  lazyPaneAJAX.success = function (response, status) {
    Drupal.freezeHeight();

    for (var i in response) {
      if (response[i]['command'] && this.commands[response[i]['command']]) {
        this.commands[response[i]['command']](response[i], status);
      }
    }

    Drupal.unfreezeHeight();
  };

  /**
   * An object that hosts execution commands supported by lazy-pane.
   */
  lazyPaneAJAX.commands = {

    insert: function (response, status) {
      var $wrappers = $(response.selector),
          method = response.method,
          settings = response.settings || Drupal.settings;

      $wrappers.each(function (index, el) {
        var $wrapper = $(el),
            $wrapped_contents = $('<div></div>').html(response.data).hide(),
            contents = $wrapped_contents.contents();

        $wrapper[method]($wrapped_contents);
        $wrapped_contents.fadeIn(600, function () {
          Drupal.attachBehaviors(contents, settings);
        });
      });
    },
    
    replacer: function (response, status) {
      var $wrappers = $(response.selector).closest('.panel-pane'),
          method = 'replaceWith',
          settings = response.settings || Drupal.settings;
          
      $wrappers.each(function (index, el) {
        var $wrapper = $(el),
            $wrapped_contents = $(response.data).hide(),
            contents = $wrapped_contents.contents();
            
        $wrapper[method]($wrapped_contents);
        $wrapped_contents.fadeIn(600, function () {
          Drupal.attachBehaviors(contents, settings);
        });
      });
    },

    settings: function (response, status) {
      if (response.merge) {
        $.extend(true, Drupal.settings, response.settings);
      }
    }
  };

  /**
   * Extracts GET params from the URL.
   */
  lazyPaneAJAX.getURLParams = function () {
    var location = document.location.search,
        params = {},
        tokens,
        regexp = /[?&]?([^=]+)=([^&]*)/g;

    while ((tokens = regexp.exec(location)) !== null) {
      params[decodeURIComponent(tokens[1])] = decodeURIComponent(tokens[2]);
    }

    return params;
  };

}(jQuery));
