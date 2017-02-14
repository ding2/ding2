/**
 * @file
 * Represents core and access point of ding_mkws.
 */

/* global pz2, pzHttpRequest, Element_getTextContent, ding_mkws_process */

/**
 * Default config.
 */
var ding_mkws = {
  active: false,
  sort: 'retrieval',
  settings: {},
  spinner: '<div class="icon-spinner icon-spin"></div>'
};

// Wrapper for storing requests.
var ding_mkws_queue = {
  requests: [],
  processing: false
};

(function ($) {
  "use strict";

  ding_mkws_queue.add = function (key, value) {
    ding_mkws_queue.requests[key] = value;
    if (Object.keys(ding_mkws_queue.requests).length === 1 && !ding_mkws_queue.processing) {
      $(document).trigger('ding_mkws_request_added', key);
    }
  };

  ding_mkws_queue.remove = function (key) {
    ding_mkws_queue.processing = false;
    delete ding_mkws_queue.requests[key];
  };

  ding_mkws_queue.next = function () {
    return Object.keys(ding_mkws_queue.requests)[0];
  };

  function _query_normalizer(str) {
    var query;
    var matches = [];
    var newarray= [];
    var splited = str.split(" ");
    var get_cql_operators_regexp = '@ and | any | all | adj | or | not |=|\(|\)@i';

    if (str.match(get_cql_operators_regexp)) {
      splited.forEach(function (item) {
        // Matching possible term arguments.
        if (item.match(/"([^"]+)"/)) {
          matches.push(item.match(/"([^"]+)"/)[1]);
        }
        else {
          matches.push(item);
        }
      });

      // Filtering duplications.
      var unique = matches.filter(function (item, i, allItems) {
        return i === allItems.indexOf(item);
      });

      unique.forEach(function(item, i) {
        if (item.match(/\d+/)) {
          delete unique[i];

          newarray.push(item);
        }
      });

      unique = unique.concat(newarray.pop());
      unique = unique.filter(function (item) { return item !== undefined; });
      query = unique.join(' ');
     }
    else {
      query = str;
    }

    return query;
  }

  ding_mkws.search = function (query, amount, filter, params) {
    query = _query_normalizer(query);
    ding_mkws.pz2.search(query, amount, ding_mkws.sort, filter, null, params);
    ding_mkws.active = true;
  };

  ding_mkws.auth = function (successCb, failCb) {
    var user = ding_mkws.settings.user;
    var password = ding_mkws.settings.password;
    var params = {};
    params.command = 'auth';
    if (user && password) {
      params.action = 'login';
      params.username = user;
      params.password = password;
    }

    var authReq = new pzHttpRequest(ding_mkws.settings.proxy, failCb);
    authReq.get(params,
      function (data) {
        var s = data.getElementsByTagName('status');
        var getTextContent = Element_getTextContent(s[0]);
        if (s.length && getTextContent === "OK") {
          if (typeof successCb === "function") {
            successCb();
          }
        } else {
          if (typeof failCb === "function") {
            failCb();
          }
          else {
            window.alert(Drupal.t("Failed to authenticate against the metasearch gateway"));
          }
        }
      }
    );
  };

  ding_mkws.init = function (settings, onShowCallback, failCallback) {
    ding_mkws.settings = Drupal.settings.ding_mkws;

    var pz2Params = {
      "pazpar2path": ding_mkws.settings.proxy,
      "usesessions": false,
      "autoInit": false,
      "showtime": 500,
      "onshow": onShowCallback
    };
    ding_mkws.pz2 = new pz2(pz2Params);
    ding_mkws.pz2.showFastCount = 1;

    ding_mkws.auth(function () {
        ding_mkws.search(settings.term, settings.amount, settings.filter, settings.parameters);
      },
      failCallback
    );
  };

  Drupal.behaviors.ding_mkws = {
    attach: function (context) {
      // Represents callback for handling errors.
      function OnFailCallback() {
        var $this = $(this);
        $this.html(Drupal.t("Sorry, something goes wrong. Can't connect to server."));
      }

      // Handling result which returns remote service.
      function OnShowCallback(data) {
        /**
         * Process data from service and render template.
         *
         * @see ding_mkws.theme.js
         */
        var params = {
          title: Drupal.t(settings.title),
          query: _query_normalizer(settings.term)
        };

        var variables = ding_mkws_process[settings.process](data, params);
        var html = $.templates[settings.template](variables);
        settings.element.html(html);

        if (data.activeclients === 0) {
          $(document).trigger('ding_mkws_request_finished', settings.hash);
        }
      }

      var settings = null; // jshint ignore:line
      $(document).on('ding_mkws_request_finished', function (event, key) {
        ding_mkws_queue.remove(key);
        key = ding_mkws_queue.next();

        if (key !== undefined) {
          settings = ding_mkws_queue.requests[key];
          ding_mkws.init(settings, OnShowCallback, OnFailCallback);
        }
      });

      $(document).on('ding_mkws_request_added', function (event, key) {
        settings = ding_mkws_queue.requests[key];
        ding_mkws_queue.processing = true;
        ding_mkws.init(settings, OnShowCallback, OnFailCallback);
      });

      $('.ding-mkws-widget', context).each(function () {
        // Collection data and processing data.
        var $this = $(this, context);
        $this.html(ding_mkws.spinner);
        // Gets settings.
        var hash = $this.data('hash');
        var process = $this.data('process');
        var template = $this.data('template');
        var settings = Drupal.settings[hash];

        settings.process = process;
        settings.template = template;
        settings.element = $this;
        settings.hash = hash;

        // Processing resources.
        if (settings.resources === undefined || settings.resources.length === 0) {
          settings.resources = null;
        }
        else {
          var out = 'pz:id=';
          for (var key in settings.resources) {
            out += settings.resources[key];
            if (key !== settings.resources.length - 1) {
              out += '|';
            }
          }
          settings.filter = out;
        }

        // Processing query.
        var query = '';
        if (settings.term.type) {
          query = settings.term.type + '=' + settings.term.query;
        }
        else {
          query = (settings.term.query !== undefined) ? settings.term.query : settings.term;
        }
        settings.term = query;

        //Processing parameters.
        settings.parameters = {};
        if (settings.maxrecs !== "") {
          settings.parameters.maxrecs = settings.maxrecs;
        }

        // Adds to queue.
        ding_mkws_queue.add(hash, settings);
      });

    }
  };
})(jQuery);
