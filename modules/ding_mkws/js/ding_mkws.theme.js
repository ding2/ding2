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
Drupal.mkwsProcessExternalUrl = function (url) {
  var process_callbacks = Drupal.settings.mkwsPreprocessExternalUrlCallbacks;

  process_callbacks.forEach(function(item, i, process_callbacks) {
    var urlCallback = window[item];

    if (typeof urlCallback === 'function') {
      url = urlCallback(url);
    }
  });

  return url;
};

/**
 * URL processing.
 * @param data
 * @returns {URL}
 */
function ting_proxy(data) {
  var url = new URL(data);
  var ting_proxy = Drupal.settings.ding_mkws.proxy_settings;
  if (ting_proxy.hostnames !== undefined && ting_proxy.hostnames.length > 0) {
    for (var i = 0; i < ting_proxy.hostnames.length; i++) {
      if (ting_proxy.hostnames[i].hostname === url.hostname && ting_proxy.hostnames[i].disable_prefix === 0) {
        var regexp = ting_proxy.hostnames[i].expression.regex;
        var replacement = ting_proxy.hostnames[i].expression.replacement;

        url = ting_proxy.prefix + url;

        if (regexp.length > 0 && replacement.length > 0) {
          var url = url.replace(new RegExp(regexp), replacement);
        }
      }
    }
  }

  return url;
}

(function ($) {

  ding_mkws_process.ProcessDataForNodeWidget = function(data) {
    var variables = {title: "", items: {left: [], right: []}};
    for (var i = 0; i < data.hits.length; i++) {
      var idx = (i % 2) ? 'left' : 'right';
      var out = {};
      var url = '';
      try {
        out = {
          target: data.hits[i].location[0]['@name'],
          title: data.hits[i]['md-title']
        };
        url = data.hits[i]['md-electronic-url'][0];
      }
      catch (e){
        url = data.hits[i]['md-bibliofil-url'][0];
      }
      finally {
        out['url'] = Drupal.mkwsProcessExternalUrl(url);
        variables.items[idx].push(out);
      }
    }

   return variables;
  };

  ding_mkws_process.ProcessDataForPaneWidget = function(data) {
    var variables = {title: Drupal.t('Content for LBR'), items: []};
    for (var i = 0 ; i < data.hits.length; i++) {
      var out = {};
      var url = '';

      try {
        out = {
          target: data.hits[i].location[0]['@name'],
          title: data.hits[i]['md-title'][0]
        };
        url = data.hits[i]['md-electronic-url'][0];
      }
      catch (e){
        url = data.hits[i]['md-bibliofil-url'][0];
      }
      finally {
        out['url'] = Drupal.mkwsProcessExternalUrl(url);
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
                "<p class='ding-mkws-target'>" +
                  Drupal.t('Target') +
                "</p>" +
                "<p class='ding-mkws-title'>" +
                  Drupal.t('Title') +
                "</p>" +
              "</div>" +
              "<div class='ding-mkws-values'>" +
                "<p class='ding-mkws-target'>" +
                  '{{:target}}' +
                "</p>" +
                "<a class='ding-mkws-title' href='{{:url}}' target='_blank'>" +
                  '{{:title}}' +
                "</a>" +
              "</div>" +
            "</li>"+
          "{{/for}}</ul>" +
        "</div>" +
        "<div class='ding-mkws-rigt'>" +
          "<ul>{{for items.right}}" +
            "<li>" +
              "<div class='ding-mkws-header'>" +
                "<p class='ding-mkws-target'>" +
                  Drupal.t('Target') +
                "</p>" +
                "<p class='ding-mkws-title'>" +
                  Drupal.t('Title') +
                "</p>" +
              "</div>" +
              "<div class='ding-mkws-values'>" +
                "<p class='ding-mkws-target'>" +
                  '{{:target}}' +
                "</p>" +
                "<a class='ding-mkws-title'  href='{{:url}}' target='_blank'>" +
                '{{:title}}' +
                "</a>" +
              "</div>" +
            "</li>"+
          "{{/for}}</ul>" +
        "</div>" +
      "</div>" +
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
              "<p class='ding-mkws-target'>" +
                Drupal.t('Target') +
              "</p>" +
              "<p class='ding-mkws-name'>" +
                Drupal.t('Title') +
              "</p>" +
            "</div>" +
            "<div class='ding-mkws-values'>" +
              "<p class='ding-mkws-target'>" +
                '{{:target}}' +
              "</p>" +
              "<a class='ding-mkws-title'  href='{{:url}}' target='_blank'>" +
                '{{:title}}' +
              "</a>" +
            "</div>" +
          "</li>"+
        "{{/for}}</ul>" +
      "</div>" +
    "</div>");
})(jQuery);
