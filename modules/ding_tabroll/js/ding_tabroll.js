/**
 * @file
 * Enables the tabs to change automatically and add handler to capture click
 * events on the tabs.
 */
(function ($) {
  'use strict';

  Drupal.behaviors.ding_tabroll = {
    attach: function (context) {
      $('.ding-tabroll-wrapper', context).once('ding-tabroll-processed', function () {
        var tabroll_wrapper = $(this);
        var tabroll = $('.ding-tabroll', tabroll_wrapper);
        var switch_speed = Drupal.settings.ding_tabroll.switch_speed;

        // Check if the tabs lib is loaded before trying to call it.
        if ($.fn.tabs) {
          tabroll.tabs({
            // The jQuery UI tabs adds a negative tabindex on the tab anchors
            // which we are not interested in having.
            // We'll remove them when the tab is created.
            create: function() {
              var tab_anchors = $('.ui-tabs-anchor', $(this));

              $(tab_anchors).each(function() {
                $(this).removeAttr('tabindex');
              });
            }
          });

          var mouseIn = false;
          var focusIn = false;
          var stopped = false;

          var interval;
          var tab_num = $('.ui-tabs-nav-item', tabroll_wrapper).length;
          interval = setInterval(function() {
            if (!focusIn && !mouseIn && !stopped) {
              var current_tab = tabroll.tabs('option', 'active');
              tabroll.tabs('option', 'active', ++current_tab < tab_num ? current_tab : 0);
            }
          }, switch_speed);

          // Stop tabs rotate when mouse is over the tab roll.
          tabroll_wrapper.mouseenter(function() {
            mouseIn = true;
          });

          // Start tabs rotate when mouse is out.
          tabroll_wrapper.mouseleave(function () {
            mouseIn = false;
          });

          // Stops tabs rotation when an element within it is in focus.
          tabroll_wrapper.focusin(function () {
            focusIn = true;
          });

          // Starts tabs rotation when an element within it is out of focus.
          tabroll_wrapper.focusout(function () {
            focusIn = false;
          });

          // Add a button to pause/play.
          var button_wrapper = $('<div class="play-toggle-wrapper clearfix"><button class="play-toggle"><span class="element-invisible">' +
                                 Drupal.t('Stop animation') + '</span></button></div>');
          var button = button_wrapper.find('button').click(function (e) {
            stopped = !stopped;
            updateButton();
          });

          var updateButton = function () {
            button.toggleClass('stopped', stopped);
          };

          tabroll_wrapper.append(button_wrapper);

          // Add click event to select tabs options.
          $('.ui-tabs-nav-item a', tabroll).click(function(e) {
            e.preventDefault();
            stopped = true;
            updateButton();
            return false;
          });
        }
      });
    }
  };

})(jQuery);
