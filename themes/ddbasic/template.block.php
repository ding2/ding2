<?php

/**
 * @file
 * Block related preprocessors.
 */

/**
 * Implements hook_block_view_alter().
 */
function ddbasic_block_view_alter(&$data, $block) {

  switch ($block->module . '__' . $block->delta) {
    case 'ting__ting_object_types':
      $object = menu_get_object('ting_object', 2);

      if ($object && $collection = ting_collection_load($object->id)) {
        $items = array();

        foreach ($collection->entities as $entity) {
          $item = ting_object_view($entity, 'teaser');
          $items[] = render($item);
        }

        // Only display block if there are more than on item.
        if (count($items) > 1) {
          $data->content = array(
            '#theme' => 'item_list',
            '#items' => $items,
          );
        }
        else {
          $data = FALSE;
        }
      }
      break;

    case 'ding_user_frontend__ding-user-loan-number':
      if (empty($data['content'])) {
        $data['content'] = t('You do not currently have any loans, reservations or debts.');
      }
      break;
  }
}
