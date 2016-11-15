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
        out = {
          target: data.hits[i].location[0]['@name'],
          title: data.hits[i]['md-title'],
          author: data.hits[i]['md-author'],
          date: data.hits[i]['md-date']
        };
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
        out = {
          target: data.hits[i].location[0]['@name'],
          title: data.hits[i]['md-title'][0],
          author: data.hits[i]['md-author'],
          date: data.hits[i]['md-date']
        };
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
        "<div class='ding-mkws-left'>" +
          "<ul>{{for items.left}}" +
            "<li>" +
              "<div class='ding-mkws-header'>" +
                "{{if target}}" +
                  "<p class='ding-mkws-target'>" +
                    Drupal.t('Target') +
                  "</p>" +
                "{{/if}}" +
                "{{if title}}" +
                  "<p class='ding-mkws-title'>" +
                    Drupal.t('Title') +
                  "</p>" +
                "{{/if}}" +
                "{{if author}}" +
                  "<p class='ding-mkws-author'>" +
                    Drupal.t('Author') +
                  "</p>" +
                "{{/if}}" +
                "{{if data}}" +
                  "<p class='ding-mkws-date'>" +
                    Drupal.t('Date') +
                  "</p>" +
                "{{/if}}" +
              "</div>" +
              "<div class='ding-mkws-values'>" +
                "{{if target}}" +
                  "<p class='ding-mkws-target'>" +
                    '{{:target}}' +
                  "</p>" +
                "{{/if}}" +
                "{{if title}}" +
                  "{{if url}}" +
                    "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                      '{{:title}}' +
                    "</a>" +
                    "{{else}}" +
                    "<p class='ding-mkws-title'>" +
                      '{{:title}}' +
                    "</p>" +
                  "{{/if}}" +
                "{{/if}}" +
                "{{if author}}" +
                  "<p class='ding-mkws-author'>" +
                    '{{:author}}' +
                  "</p>" +
                "{{/if}}" +
                "{{if date}}" +
                  "<p class='ding-mkws-date'>" +
                    '{{:date}}' +
                  "</p>" +
                "{{/if}}" +
              "</div>" +
            "</li>"+
          "{{/for}}</ul>" +
        "</div>" +
        "<div class='ding-mkws-rigt'>" +
          "<ul>{{for items.right}}" +
            "<li>" +
              "<div class='ding-mkws-header'>" +
                "{{if target}}" +
                  "<p class='ding-mkws-target'>" +
                    Drupal.t('Target') +
                  "</p>" +
                "{{/if}}" +
                "{{if title}}" +
                  "<p class='ding-mkws-title'>" +
                    Drupal.t('Title') +
                  "</p>" +
                "{{/if}}" +
                "{{if author}}" +
                  "<p class='ding-mkws-author'>" +
                    Drupal.t('Author') +
                  "</p>" +
                "{{/if}}" +
                "{{if date}}" +
                  "<p class='ding-mkws-date'>" +
                    Drupal.t('Date') +
                  "</p>" +
                "{{/if}}" +
              "</div>" +
              "<div class='ding-mkws-values'>" +
                "{{if target}}" +
                  "<p class='ding-mkws-target'>" +
                    '{{:target}}' +
                  "</p>" +
                "{{/if}}" +
                "{{if title}}" +
                  "{{if url}}" +
                    "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                      '{{:title}}' +
                    "</a>" +
                  "{{else}}" +
                    "<p class='ding-mkws-title'>" +
                      '{{:title}}' +
                    "</p>" +
                  "{{/if}}" +
                "{{/if}}" +
                "{{if author}}" +
                  "<p class='ding-mkws-author'>" +
                    '{{:author}}' +
                  "</p>" +
                "{{/if}}" +
                "{{if date}}" +
                  "<p class='ding-mkws-date'>" +
                    '{{:date}}' +
                   "</p>" +
                "{{/if}}" +
              "</div>" +
            "</li>"+
          "{{/for}}</ul>" +
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
        "<ul>{{for items}}" +
          "<li>" +
            "<div class='ding-mkws-header'>" +
              "{{if target}}" +
                "<p class='ding-mkws-target'>" +
                  Drupal.t('Target') +
                "</p>" +
              "{{/if}}" +
              "{{if title}}" +
                "<p class='ding-mkws-name'>" +
                  Drupal.t('Title') +
                "</p>" +
              "{{/if}}" +
              "{{if author}}" +
                "<p class='ding-mkws-author'>" +
                  Drupal.t('Author') +
                "</p>" +
              "{{/if}}" +
              "{{if date}}" +
                "<p class='ding-mkws-date'>" +
                  Drupal.t('Date') +
                "</p>" +
              "{{/if}}" +
            "</div>" +
            "<div class='ding-mkws-values'>" +
              "{{if target}}" +
                "<p class='ding-mkws-target'>" +
                  '{{:target}}' +
                "</p>" +
              "{{/if}}" +
              "{{if title}}" +
                "{{if url}}" +
                  "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                    '{{:title}}' +
                  "</a>" +
                "{{else}}" +
                  "<p class='ding-mkws-title'>" +
                    '{{:title}}' +
                  "</p>" +
                "{{/if}}" +
              "{{/if}}" +
              "{{if author}}" +
                "<p class='ding-mkws-author'>" +
                  '{{:author}}' +
                "</p>" +
              "{{/if}}" +
              "{{if date}}" +
                "<p class='ding-mkws-date'>" +
                  '{{:date}}' +
                "</p>" +
              "{{/if}}" +
            "</div>" +
          "</li>"+
        "{{/for}}</ul>" +
      "</div>" +
      "<a href='/search/meta/{{:more_link}}'>{{:more_text}}</a>" +
    "</div>");
})(jQuery);
