<?php

/**
 * @file
 * Ding wishlist pages.
 */

/**
 * Menu callback; Display user wishlist items.
 */
function ding_wishlist_user_wishlist_page($account) {
  $content_ids = flag_load('wishlist')->get_user_content_ids($account->uid);
  return theme('ding_wishlist_content', array('entity_ids' => array_keys($content_ids)));
}
