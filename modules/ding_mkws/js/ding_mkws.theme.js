/**
 * @file
 * Represents functionality which relates to theme.
 */
'use strict';
var ding_mkws_process = {};

/**
 * Function designed to call functions in given order.
 * @param url
 * @returns {*}
 */
Drupal.mkwsProcessExternalUrl = function (url, target) {
  var process_callbacks = Drupal.settings.mkwsPreprocessExternalUrlCallbacks;
  process_callbacks.forEach(function(item, i, process_callbacks) {
    var urlCallback = window[item];

    if (typeof urlCallback === 'function') {
      url = urlCallback(url, target);
    }
  });

  return url;
};

/**
 * URL processing.
 * @param data
 * @param target
 * @returns {URL}
 */
function ting_proxy(data, target) {
  var url = document.createElement("a");
  url.href = data;

  var ting_proxy = Drupal.settings.ding_mkws.proxy_settings;
  if (ting_proxy.hostnames !== undefined && ting_proxy.hostnames.length > 0) {
    for (var i = 0; i < ting_proxy.hostnames.length; i++) {
      if (ting_proxy.hostnames[i].hostname === url.hostname && ting_proxy.hostnames[i].disable_prefix === 0) {
        var regexp = ting_proxy.hostnames[i].expression.regex;
        var replacement = ting_proxy.hostnames[i].expression.replacement;
        url.href = ting_proxy.prefix + url + '&hostname=' + url.hostname;

        if (regexp.length > 0 && replacement.length > 0) {
          url.href = url.replace(new RegExp(regexp), replacement);
        }
      }
    }
  }

  return url;
}

(function ($) {

  ding_mkws_process.ProcessDataForNodeWidget = function(data, params) {
    var variables = {
      title: params.title,
      items: {left: [], right: []},
      more_text: Drupal.t('See all results'),
      more_link: params.query
    };
    for (var i = 0; i < data.hits.length; i++) {
      var idx = (i % 2) ? 'left' : 'right';
      var out = {};
      var url = '';
      try {
        if (typeof data.hits[i].location !== 'undefined' && data.hits[i].location.length > 1) {
          var temp_location = [];
          for (var j = 0; j < data.hits[i].location.length; j++) {
            temp_location.push(data.hits[i].location[j]['@name']);
          }
          out.target = temp_location.join(', ');
        }
        else {
          out.target = data.hits[i].location[0]['@name'];
        }

        out.title = (data.hits[i]['md-title'].length > 1) ?
          data.hits[i]['md-title'].join(', ') :
          data.hits[i]['md-title'];

        // Concatenate author names if more than one.
        out.author = (typeof data.hits[i]['md-author'] !== 'undefined' && data.hits[i]['md-author'].length > 1) ?
          data.hits[i]['md-author'].join(', ') :
          data.hits[i]['md-author'];

        out.date = (typeof data.hits[i]['md-date'] !== 'undefined' && data.hits[i]['md-date'].length > 1) ?
          data.hits[i]['md-date'].join(', ') :
          data.hits[i]['md-date'];

        if (data.hits[i]['md-electronic-url'] !== undefined) {
          url = data.hits[i]['md-electronic-url'][0];
        }
        else if (data.hits[i]['md-bibliofil-url'] !== undefined) {
          url = data.hits[i]['md-bibliofil-url'][0];
        }
        else {
          url = false;
        }
      }
      catch (e){
        console.log(e);
      }
      finally {
        if (url !== false) {
          out.url = Drupal.mkwsProcessExternalUrl(url, out.target);
        }
        variables.items[idx].push(out);
      }
    }

   return variables;
  };

  ding_mkws_process.ProcessDataForPaneWidget = function(data, params) {
    var variables = {
      title: params.title,
      items: [],
      more_text: Drupal.t('See all results'),
      more_link: params.query
    };

    for (var i = 0 ; i < data.hits.length; i++) {
      var out = {};
      var url = '';

      try {
        if (typeof data.hits[i].location !== 'undefined' && data.hits[i].location.length > 1) {
          var temp_location = [];
          for (var j = 0; j < data.hits[i].location.length; j++) {
            temp_location.push(data.hits[i].location[j]['@name']);
          }
          out.target = temp_location.join(', ');
        }
        else {
          out.target = data.hits[i].location[0]['@name'];
        }

        out.title = (data.hits[i]['md-title'].length > 1)
          ? data.hits[i]['md-title'].join(', ')
          : data.hits[i]['md-title'];

        // Concatenate author names if more than one.
        out.author = (typeof data.hits[i]['md-author'] !== 'undefined' && data.hits[i]['md-author'].length > 1)
          ? data.hits[i]['md-author'].join(', ')
          : data.hits[i]['md-author'];

        out.date = (typeof data.hits[i]['md-date'] !== 'undefined' && data.hits[i]['md-date'].length > 1)
          ? data.hits[i]['md-date'].join(', ')
          : data.hits[i]['md-date'];

        if (data.hits[i]['md-electronic-url'] !== undefined) {
          url = data.hits[i]['md-electronic-url'][0];
        }
        else if (data.hits[i]['md-bibliofil-url'] !== undefined) {
          url = data.hits[i]['md-bibliofil-url'][0];
        }
        else {
          url = false;
        }
      }
      catch (e){
        console.log(e);
      }
      finally {
        if (url !== false) {
          out.url = Drupal.mkwsProcessExternalUrl(url, out.target);
        }
        variables.items.push(out);
      }
    }

    if (data.hits.length === 0) {
      variables.title = "";
    }

    return variables;
  };

  $.templates("dingMkwsNodeWidget", "" +
    "<div class='ding-mkws-widget ding-mkws-widget-node'>" +
      "{{if title}}" +
      "<div class='ding-mkws-title'>{{:title}}</div>" +
      "{{/if}}"+
      "<div class='ding-mkws-content'>" +
        "<div class='ding-mkws-rows'>" +
          "<div class='row'>" +
            "{{if target}}" +
              "<div class='left-label'>" +
                "<p class='ding-mkws-target'>" +
                  Drupal.t('Target') +
                "</p>" +
              "</div>" +
            "{{/if}}" +
            "{{if target}}" +
            "<div class='right-value'>" +
                "<p class='ding-mkws-target'>" +
                  '{{:target}}' +
                "</p>" +
              "</div>" +
            "{{/if}}" +
          "</div>" +

          "<div class='row'>" +
            "{{if title}}" +
              "<div class='left-label'>" +
                "<p class='ding-mkws-title'>" +
                  Drupal.t('Title') +
                  "</p>" +
              "</div>" +
            "{{/if}}" +
            "{{if title}}" +
              "<div class='right-value'>" +
                "{{if url}}" +
                  "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                    '{{:title}}' +
                  "</a>" +
                  "{{else}}" +
                    "<p class='ding-mkws-title'>" +
                      '{{:title}}' +
                    "</p>" +
                "{{/if}}" +
              "</div>" +
            "{{/if}}" +
          "</div>" +

          "<div class='row'>" +
            "{{if author}}" +
              "<div class='left-label'>" +
                "<p class='ding-mkws-author'>" +
                  Drupal.t('Author') +
                  "</p>" +
              "</div>" +
            "{{/if}}" +
            "{{if author}}" +
              "<div class='right-value'>" +
                  "<p class='ding-mkws-author'>" +
                    '{{:author}}' +
                  "</p>" +
              "</div>" +
            "{{/if}}" +
          "</div>" +

          "<div class='row'>" +
            "{{if date}}" +
              "<div class='left-label'>" +
                "<p class='ding-mkws-date'>" +
                  Drupal.t('Date') +
                "</p>" +
              "</div>" +
            "{{/if}}" +
            "{{if date}}" +
              "<div class='right-value'>"+
                "<p class='ding-mkws-date'>" +
                  '{{:date}}' +
                "</p>" +
              "</div>"+
            "{{/if}}" +
          "</div>" +
        "</div>" +
      "</div>" +
      "<a class='ding-mkws-more-link' href='/search/meta/{{:more_link}}'>{{:more_text}}</a>" +
    "</div>");

  $.templates("dingMkwsPaneWidget", "" +
    "<div class='ding-mkws-widget ding-mkws-widget-node'>" +
      "{{if title}}" +
        "<div class='ding-mkws-title'>{{:title}}</div>" +
      "{{/if}}"+
      "<div class='ding-mkws-content'>" +
        "<div>{{for items}}" +
          "<div class='ding-mkws-rows'>" +
            "<div class='row'>" +
              "{{if target}}" +
                "<div class='left-label'>" +
                  "<p class='ding-mkws-target'>" +
                    Drupal.t('Target') +
                  "</p>" +
                "{{/if}}" +
              "</div>" +
              "{{if target}}" +
                "<div class='right-value'>" +
                  "<p class='ding-mkws-target'>" +
                    '{{:target}}' +
                  "</p>" +
                "</div>" +
              "{{/if}}" +
            "</div>" +

            "<div class='row'>" +
              "{{if title}}" +
                "<div class='left-label'>" +
                  "<p class='ding-mkws-title'>" +
                    Drupal.t('Title') +
                  "</p>" +
                "</div>" +
              "{{/if}}" +
              "{{if title}}" +
                "<div class='right-value'>" +
                  "{{if url}}" +
                    "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                      '{{:title}}' +
                    "</a>" +
                    "{{else}}" +
                      "<p class='ding-mkws-title'>" +
                        '{{:title}}' +
                      "</p>" +
                  "{{/if}}" +
                "</div>" +
              "{{/if}}" +
            "</div>" +

            "<div class='row'>" +
              "{{if author}}" +
                "<div class='left-label'>" +
                  "<p class='ding-mkws-author'>" +
                    Drupal.t('Author') +
                    "</p>" +
                "</div>" +
              "{{/if}}" +
              "{{if author}}" +
                "<div class='right-value'>" +
                    "<p class='ding-mkws-author'>" +
                      '{{:author}}' +
                    "</p>" +
                "</div>" +
              "{{/if}}" +
            "</div>" +

            "<div class='row'>" +
              "{{if date}}" +
                "<div class='left-label'>" +
                  "<p class='ding-mkws-date'>" +
                    Drupal.t('Date') +
                  "</p>" +
                "</div>" +
              "{{/if}}" +
              "{{if date}}" +
                "<div class='right-value'>"+
                  "<p class='ding-mkws-date'>" +
                    '{{:date}}' +
                  "</p>" +
                "</div>"+
              "{{/if}}" +
            "</div>" +
          "</div>" +
        "{{/for}}</div>" +
      "</div>" +
      "<a href='/search/meta/{{:more_link}}'>{{:more_text}}</a>" +
    "</div>");
})(jQuery);
