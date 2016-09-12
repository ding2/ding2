/**
 * @file
 * Represents core and access point of ding_mkws.
 */

/**
 * Default config.
 */
var ding_mkws = {
  active: false,
  sort: 'relevance',
  settings: {},
  spinner: '<div class="ispinner large gray animating">' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '<div class="ispinner-blade"></div>' +
  '</div>',
};

(function ($) {
  ding_mkws.search = function (query, amount, filter, limit) {
    ding_mkws.pz2.search(query, amount, ding_mkws.sort, filter, null, {limit: limit});
    ding_mkws.active = true;
  };

  ding_mkws.auth = function (successCb, failCb) {
    var user = ding_mkws.settings.user;
    var password = ding_mkws.settings.password;
    var params = {};
    params['command'] = 'auth';
    if (user && password) {
      params['action'] = 'login';
      params['username'] = user;
      params['password'] = password;
    }
    var authReq = new pzHttpRequest(ding_mkws.settings.proxy, failCb);
    authReq.get(params,
      function (data) {
        var s = data.getElementsByTagName('status');
        if (s.length && Element_getTextContent(s[0]) == "OK") {
          if (typeof successCb == "function") successCb();
        } else {
          if (typeof failCb == "function") failCb();
          else alert(Drupal.t("Failed to authenticate against the metasearch gateway"));
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
      "onshow": onShowCallback,
      "onstat": function (data) {
      },
      "onterm": function (data) {
      },
      "onrecord": function (data) {
      }
    };
    ding_mkws.pz2 = new pz2(pz2Params);
    ding_mkws.pz2.showFastCount = 1;

    ding_mkws.auth(function () {
        ding_mkws.search(settings.term, settings.amount, settings.resources, settings.limit)
      },
      failCallback
    );
  };

  Drupal.behaviors.ding_mkws = {
    attach: function (context) {
      $('.ding-mkws-widget', context).each(function () {
        var $this = $(this, context);
        $this.html(ding_mkws.spinner);
        // Gets settings.
        var hash = $this.data('hash');
        var process = $this.data('process');
        var template = $this.data('template');
        var settings = Drupal.settings[hash];
        if (settings.limit === undefined) {
          settings.limit = null;
        }
        else {
          var out = null;
          for (var key in settings.limit) {
            out = key + "=" + settings.limit[key];
          }
          settings.limit = out;
        }

        if (settings.resources.length == 0) {
          settings.resources = null;
        }
        ding_mkws.init(settings, function (data) {
            if (data.activeclients == 0) {
              /**
               * Process data from service and render template.
               *
               * @see ding_mkws.theme.js
               */
              var variables = ding_mkws_process[process](data);
              var html = $.templates[template](variables);
              $this.html(html);
            }
          },
          function () {
            $this.html(Drupal.t("Sorry, something goes wrong. Can't connect to server."));
          });
      });
    }
  };
})(jQuery);
