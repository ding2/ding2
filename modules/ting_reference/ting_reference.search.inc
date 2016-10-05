<?php
/**
 * @file
 * Helper search functions are defined.
 */


/**
 * Save relation between node id and ting object ids.
 *
 * @param int $nid
 *   Node id.
 * @param array $tids
 *   Array of ting object ids.
 */
function ting_reference_set_relation($nid, $field_name, $tids) {
  // Delete all records for current nid.
  db_delete('ting_reference')
    ->condition('nid', $nid)
    ->condition('field_name', $field_name)
    ->execute();

  $query = db_insert('ting_reference')->fields(array('nid', 'field_name', 'ting_object_id'));
  foreach ($tids as $tid) {
    if (!empty($tid['ting_object_id'])) {
      // Insert new record.
      $query->values(array('nid' => $nid, 'field_name' => $field_name,'ting_object_id' => $tid['ting_object_id']));
    }
  }
  $query->execute();
}

/**
 * Get all ting object materials related to node id.
 *
 * @param int $nid
 *   Node id.
 *
 * @return array
 *   Array of ting object ids.
 */
function ting_reference_get_relation($nid, $field_name) {
  $tids = array();
  $results = db_select('ting_reference', 'tr')
    ->fields('tr', array('ting_object_id'))
    ->condition('nid', $nid)
    ->condition('field_name', $field_name)
    ->execute();

  foreach ($results as $result) {
    $tids[] = $result->ting_object_id;
  }

  return $tids;
}


/**
 * Get ting objects.
 *
 * @param string $query
 *   Search query string.
 * @param int $count
 *   Number of objects to search.
 *
 * @return array
 *   Array of items.
 */
function ting_reference_get_search_objects($query = '', $count = 0, $sort = '') {
  $objects = array();
  $request = '(' . $query . ')';
  $page = 1;

  if (!empty($query) && !empty($count)) {
    module_load_include('client.inc', 'ting');
    // Search with portions of 10 items.
    while ($result = ting_reference_search_ting($request, $page++, $count, $sort)) {
      // This query is out of results OR we have needed amount of items.
      if ($result->numTotalCollections == 0 || count($objects) == $count) {
        break;
      }

      foreach ($result->collections as $collection) {
        // Whether we reached our item limit per query.
        if (count($objects) == $count) {
          // Stop fetching anything from Ting.
          break 2;
        }

        foreach ($collection->reply->objects as $search_item) {
          $objects[$search_item->localId] = $collection->primary_object;;

          break;
        }
      }
    }

    // Make an array of local id's, fetchable by voxb.
    // Take only items with ISBN code.
    if (module_exists('ding_voxb')) {
      $local_ids = array();
      foreach ($objects as $local_id => $v) {
        if (!empty($v->isbn)) {
          $local_ids[$local_id] = $v->isbn[0];
        }
      }

      // Fetch details from voxb.
      $voxb_details = new VoxbItems();
      $voxb_details->addReviewHandler('review', new VoxbReviews());
      $response = $voxb_details->fetchByISBN($local_ids);

      // Assign voxb details to items.
      if ($response && $voxb_details->getCount() > 0) {
        foreach ($local_ids as $local_id => $isbn) {
          $detail = $voxb_details->getItem($isbn);
          if ($detail) {
            $objects[$local_id]->rating = (int) round($detail->getRating() / 20);
            $objects[$local_id]->rating_count = $detail->getRatingCount();
            $objects[$local_id]->comment_count = $detail->getReviews('review')->getCount();
            $objects[$local_id]->has_rating = TRUE;
          }
        }
      }
    }
  }

  return $objects;
}

/**
 * Perform ting search.
 *
 * @param string $query
 *   Searched query string.
 * @param int $page
 *   Requested results page.
 * @param int $records
 *   Number of records to fetch.
 *
 * @return object
 *   Ting search result object.
 */
function ting_reference_search_ting($query = '', $page = 1, $records = 10, $sort = '') {
  if (!empty($query)) {
    $options = array(
      'allObjects' => FALSE,
      'enrich' => TRUE,
      'sort' => $sort,
    );

    $query = '(' . _ting_search_quote($query) . ')';
    $search_result = ting_do_search($query, $page, $records, $options);

    return $search_result;
  }

  return FALSE;
}

/**
 * Get objects according to passed search parameters.
 *
 * @param string $query
 *   Search query.
 * @param int $count
 *   Number of items to fetch.
 * @param string $sort
 *   Sort identifier
 *
 * @return string
 *   List markup.
 */
function ting_reference_get_objects($query, $count, $sort) {
  $cid = ting_reference_generate_cache_id(array($query, $count, $sort));
  $cache = cache_get($cid);

  if (!$cache) {
    $objects = ting_reference_get_search_objects($query, $count, $sort);

    cache_set($cid, $objects);
  }
  else {
    $objects = $cache->data;
  }
  return $objects;
}

/**
 * Generate markup according to passed ding objects and view mode.
 *
 * @param $objects
 *   Ding objects to be rendered.
 * @param $view_mode
 *   View mode of the ting object.
 *
 * @return string
 *   Rendered ding objects.
 */
function ting_reference_markup_content($view_mode, $objects) {
  $markup = '';
  foreach ($objects as $object) {
    $object_view = ting_object_view($object, $view_mode);
    $markup .= render($object_view);
  }

  return $markup;
}

/**
 * Generate a cache id, based on a keyword.
 *
 * @param array $keywords
 *   Set of keyword used for hash generating.
 *
 * @return string
 *   Hash string, meaning a certain cache id.
 */
function ting_reference_generate_cache_id($keywords) {
  return 'ting_reference-' . md5(implode('',$keywords));
}

/**
 * Get materials from widget formatter.
 *
 * @param string $entity_id
 *   Type of the saved entity.
 * @param string $widget_type
 *   Type of the processed widget.
 * @param array $items
 *   Items got from the widget form.
 *
 * @return array
 *   Array of the ting objects.
 */
function ting_reference_get_materials($entity_id, $widget_type, &$items) {
  $tids = array();

  if ($widget_type == 'ting_reference_search') {
    foreach ($items as $item) {
      $tid = reset($item['materials']);
      if (!empty($tid)) {
        $tids[] = $tid;
      }
    }
  }
  else {
    $settings = reset($items);
    if (!empty($settings['materials']) && is_array($settings['materials']) && $entity_id) {
      unset($settings['materials']['add']);
      $tids = $settings['materials'];
    }
  }

  return $tids;
}
