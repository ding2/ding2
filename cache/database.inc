<?php

/**
 * @file
 *
 * Contains definition of TingFieldSearchDatabaseCache.
 */

/**
 * Defines a special extension of Drupal's database cache backend, which is
 * intended ONLY to be used with the cache_ting bin. It modifies the passed cid
 * from ting, if a special search profile setup in the Ting field search admin
 * UI is used. This enables ting to serve the correct cached response based on
 * the profile used in the request.
 */
class TingFieldSearchDatabaseCache extends DrupalDatabaseCache {

	function get($cid) {
		if ($profile = _ting_field_search_use_special_profile()) {
			$cid .= ':' . $profile;
		}
		return parent::get($cid);
	}

	function set($cid, $data, $expire = CACHE_PERMANENT) {
		if ($profile = _ting_field_search_use_special_profile()) {
			$cid .= ':' . $profile;
		}
		parent::set($cid, $data, $expire);
	}

}
