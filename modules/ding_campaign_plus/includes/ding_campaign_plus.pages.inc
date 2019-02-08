<?php

/**
 * @file
 * Page callbacks for ding_campaign_plus.
 */

/**
 * Page callback, returns rendered campaign.
 *
 * @param string $cid
 *   The cache id of the campaign.
 */
function ding_campaigns_plus_campaign_ajax($cid) {
  $cache_context = cache_get($cid . '-context');
  // If context not found, or no campaignfound, we'll return no campaign.
  $content = '';
  if ($cache_context && isset($cache_context->data)) {
    $cache = cache_get($cid);
    // Check if we already have a cached campagin.
    if (isset($cache->data) && REQUEST_TIME < $cache->expire) {
      $content = $cache->data;
    }
    else {
      $content = _ding_campaign_plus_render_campaign($cache_context->data[0], $cache_context->data[1]);
      cache_set($cid, $content, 'cache', REQUEST_TIME + variable_get('ding_campaign_plus_expire', 900));
    }
  }
  echo $content;
  drupal_exit();
}
