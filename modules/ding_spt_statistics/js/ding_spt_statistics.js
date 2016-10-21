/**
 * @file
 * Perform redirect functionality
 */
'use strict';

/**
 * Preprocess url before attach to template.
 *
 * @param data
 */
function dingSPTStatisticsUrlPreprocess(data) {
  var url = document.createElement("a");
  url.href = data;
  var params = {path: url.href};

  var hostname = url.hostname;
  if (url.href.indexOf('hostname') !== -1) {
    hostname = url.href.split('hostname=')[1];
  }
  params.hostname = hostname;

  return '/spt/redirect?' + jQuery.param(params);
}
