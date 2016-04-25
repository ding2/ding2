(function ($) {
  $(document).ready(function(){
    $('[id^=ding-item-viewer-]').each(function (index, element) {
      var container,// Ding Item Viewer container (main div).
        content, // Ding Item Viewer item container (div with items).
        settings,// Settings passed via Drupal.settings.
        tabs = [],// index => object_id mapping.
        items = [],// Items received from server.
        current_tab = 0,
        starting_item = 0,
        wait_time = 5000, // Time interval when to try to fetch data in ms.
        timeOut = null,
        uri = '',
        interval = 5000;

      // Convert seconds to miliseconds.
      interval = Drupal.settings.ding_item_viewer.interval * 1000;
      // Load data from server.
      container = $(element);
      uri = 'ding_item_viewer/' + container.attr('data-hash');
      $('a.tab', container).live('click', function(e) {
        // In case when user click to tab, stop sliding.
        clearTimeout(timeOut);
        tab_change(e, $(this));
        // And begin again.
        timeOut = setTimeout(slide, interval);
      });

      $('div.browsebar-inner', container).live('mouseover', function() {
        clearTimeout(timeOut);
      });

      $('div.browsebar-inner', container).live('mouseout', function() {
        timeOut = setTimeout(slide, interval);
      });

      fetch_data();

      /**
       * Slides ding item viewer.
       */
      function slide() {
        var tabs = $('li', container);
        if (tabs.length > 1) {
          var current = $('li.active a.tab', container);
          var next = $(current).parent().next();
          next = next.length > 0 ? next : $(current).parent().siblings().first();
          tab_change(null, next.children());
          timeOut = setTimeout(slide, interval);
        }
      }

      function fetch_data() {
        $.get(uri, container_callback);
      }

      /**
       * AJAX success callback function.
       *
       * @see jQuery.get()
       */
      function container_callback(response, textStatus, jqXHR) {
        if (response.status === 'OK') {
          container.html(response.data.content);
          container.append(response.data.tabs);
          items = response.data.items;
          container.find('.ui-tabs-nav li:first').addClass('active');

          prepare_data();
          show_items();
          // Begin slide.
          timeOut = setTimeout(slide, interval);
        }
        else {
          container.html(response.error);
        }
      }

      /**
       * Prepare data before viewing it.
       */
      function prepare_data() {
        var tab, i, id, ids = [];
        // Build index => object_id mapping for quick access (DingItemViewer.tabs).
        for (tab = 0; tab < items.length; tab++) {
          tabs[tab] = [];
          i = 0;
          for (id in items[tab]) {
            tabs[tab][i] = id;
            i++;
            ids.push(id);
          }
        }
        // Get settings.
        settings = Drupal.settings.ding_item_viewer;
        var path = Drupal.settings.basePath + 'ding_availability/items/' + ids.join(',');
        $.ajax({
          dataType: "json",
          url: path,
          success: function(data) {
            $.each(data, function(id, item) {
              // Update cache.
              Drupal.DADB[id] = item;
            });
            show_reservation_button();
          }
        });

        // Get item container.
        content = container.find('.browsebar-items-wrapper');
      }

      /**
       * Show initial items.
       */
      function show_items() {
        var i, item, id, index;

        // Reset content.
        content.html('');

        var visible = Math.min(settings.visible_items, tabs[current_tab].length);
        var big_item_positon = settings.big_item_positon;
        if (visible < settings.visible_items) {
          big_item_positon = Math.floor(visible / 2);
        }

        // Show specified number of items on screen.
        for (i = 0; i < visible; i++) {
          index = (i + starting_item) % tabs[current_tab].length;
          id = tabs[current_tab][index];

          // "Big" item.
          if (i === big_item_positon) {
            item = $(items[current_tab][id].big);
            item.addClass('active');
          }
          // "Small" items.
          else {
            item = $(items[current_tab][id].small);
            // Add even/odd class for proper positioning.
            if (i % 2 === 0) {
              item.addClass('even');
            }
            else {
              item.addClass('odd');
            }
            // Position on screen (helper info).
            item.data('position', i);

            // Attach onclick handler.
            item.click(item_click);
          }
          // Index in DingItemViewer.tabs (helper info).
          item.data('index', index);
          // Show item.
          item.addClass('browsebar-item');

          item.find('img').wrap("<div class='image-wrapper'></div>");
          content.append(item);
        }

        show_reservation_button();

        // Preload images for current tab.
        for (i = 0; i < tabs[current_tab].length; i++) {
          id = tabs[current_tab][i];
          preload_images(items[current_tab][id]);
        }

        // Add first/last classes.
        content.find(':first').addClass('first');
        content.find(':last').addClass('last');

        var ajax_ele = content.find('.use-ajax');
        ajax_ele.each(function() {
          ele = $(this);
          new Drupal.ajax('#' + ele.attr('id'), ele, {
            url: ele.attr('href'),
            effect: 'fade',
            settings: {},
            progress: {
              type: 'throbber'
            },
            event: 'click tap'
          });
        });

      }

      /**
       * Display the reservation button for items that can be reserved.
       */
      function show_reservation_button() {
        // Show reservation button.
        var r_button = container.find('.reserve-button');
        if (r_button.length > 0) {
          var id = r_button.attr('id').match(/reservation-[0-9]+-[\w]+:(\w+)/);
          if (typeof id[1] !== 'undefined' && typeof Drupal.DADB[id[1]] !== 'undefined') {
            if (Drupal.DADB[id[1]].reservable === true) {
              r_button.show();
            }
          }
        }
      }

      /**
       * Small item onclick event handler.
       *
       * Moves clicked item in "big" view and shifts all other items in "circle".
       */
      function item_click() {
        var item = $(this),
          position = item.data('position'),
          index = item.data('index'),
          rotation; // Shift and direction of rotation.

        // Recalculate starting_item index and redraw content.
        var visible = Math.min(settings.visible_items, tabs[current_tab].length);
        var big_item_positon = settings.big_item_positon;
        if (visible < settings.visible_items) {
          big_item_positon = Math.floor(visible / 2);
        }

        rotation = position - big_item_positon;
        starting_item = starting_item + rotation;
        // For negative value start from the tail of list.
        if (starting_item < 0) {
          starting_item = tabs[current_tab].length + starting_item;
        }
        show_items();

        return false;
      }

      /**
       * Tab click event handler.
       *
       * Changes shown tab.
       */
      function tab_change(e, obj) {
        if(e !== null) {
          e.preventDefault();
        }

        starting_item = 0;
        current_tab = $(obj).data('tab');
        container.find('.ui-tabs-nav li').removeClass('active');
        $(obj).parent().addClass('active');

        show_items();
      }

      function preload_images(item) {
        var $item, src, img;
        $item = $(item.big);
        src = $item.find('img').attr('src');
        img = new Image();
        img.src = src;

        $item = $(item.small);
        src = $item.find('img').attr('src');
        img = new Image();
        img.src = src;
      }
    });
  });
})(jQuery);

