/**
 * @file
 * Perform redirect functionality
 */
'use strict';

/**
 * Preprocess url before attach to template.
 * @param data
 * @param target
 */
function dingSPTStatisticsUrlPreprocess(data, target) {
  var url = new URL(data);
  return url.href = '/spt/redirect?path=' + url.href + '&hostname=' + target;
}
