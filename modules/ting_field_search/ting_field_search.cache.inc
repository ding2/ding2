<?php

/**
 * @file
 *
 * Contains the definitions of the module's cache backends that is used on the
 * cache_ting bin, to overcome the limitations of hook_ting_pre_execute caused
 * by Ting client's timing of setting the cache.
 */


class TingFieldSearchDatabaseCache extends DrupalDatabaseCache {

  function get($cid) {
    return parent::get(_ting_field_search_cache_get_cid($cid));
  }

  function set($cid, $data, $expire = CACHE_PERMANENT) {
    parent::set(_ting_field_search_cache_get_cid($cid), $data, $expire);
  }

}

if (module_exists('memcache')) {
  class TingFieldSearchMemCache extends MemCacheDrupal {

    function get($cid) {
      return parent::get(_ting_field_search_cache_get_cid($cid));
    }

    function set($cid, $data, $expire = CACHE_PERMANENT, array $headers = NULL) {
      parent::set(_ting_field_search_cache_get_cid($cid), $data, $expire, $headers);
    }

  }
}

/**
 * Private wrapper function for shared functionality between the two backends.
 */
function _ting_field_search_cache_get_cid($cid) {
  $profile = ting_field_search_get_active_profile();

  // Only alter the cache key when both a profile and context is active.
  if ($profile && ting_field_search_get_context()) {
    $cid .= ':' . $profile->name;
  }

  return $cid;
}
