<?php

/**
 * @file
 * List display of uploaded covers from this library.
 */

use CoverServiceUpload\Api\MaterialApi;
use GuzzleHttp\Client;

/**
 * Display list of covers uploaded by the library.
 *
 * @return array
 *   A themed list.
 *
 * @throws \CoverServiceUpload\ApiException
 */
function ddb_cover_upload_list() {
  $rows = array();

  $materials = _ddb_cover_upload_get_materials();
  foreach ($materials as $material) {
    $cover = $material->getCover();
    $image = array(
      '#theme' => 'image',
      '#path' => $cover->getImageUrl(),
      '#width' => '120px',
    );

    /** @var \Ting\TingObject $object */
    $object = ding_entity_load($material->getIsIdentifier(), 'ting_object');
    $title = t('Not found');
    $link = $material->getIsIdentifier();
    if (FALSE !== $object) {
      $uri = ding_entity_uri('ding_entity', $object);
      $title = $object->getTitle() . ' (' . $object->getType() . ')';
      $link = l($material->getIsIdentifier(), $uri['path'], array('html' => TRUE));
    }

    $rows[] = [
      $material->getId(),
      render($image),
      $title,
      $link,
      l(t('Delete'), 'admin/config/ddb_cover_upload/upload/list/delete/' . $material->getId(), array('html' => TRUE)),
    ];
  }

  drupal_set_title(t('List uploaded covers'));
  $header = array(
    t('Id'),
    t('Image'),
    t('Title'),
    t('Material'),
    t('Actions'),
  );

  return array(
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $rows,
    )),
  );
}

/**
 * Menu callback for deleting an uploaded cover.
 */
function ddb_cover_upload_delete($form, &$form_state, $id) {
  $form['material_id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete the cover for this item?'),
    'admin/config/ddb_cover_upload/upload/list',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Confirm form submit handler for delete above.
 */
function ddb_cover_upload_delete_submit($form, &$form_state) {
  if (isset($form_state['values']['material_id'])) {
    $id = $form_state['values']['material_id'];

    try {
      $material = _ddb_cover_upload_get_material($id);
      _ddb_cover_upload_delete_material($id);
      watchdog('ddb_cover_upload', 'Cover have been deleted at DDB upload service for %pid', array('%pid' => $material->getIsIdentifier()), WATCHDOG_INFO);

      // Clear cover and materials cache.
      cache_clear_all('ddb_cover_upload', 'cache', TRUE);

      drupal_set_message(t('The cover for %pid has been deleted. It might take sometime before it is removed in all systems.', array('%pid' => $material->getIsIdentifier())));
    }
    catch (\CoverServiceUpload\ApiException $exception) {
      watchdog_exception('ddb_cover_upload', $exception, $exception->getMessage(), array(), WATCHDOG_CRITICAL);
      drupal_set_message(t('Unknown error happen at the service. Please try aging later.'));
    }
  }
  else {
    drupal_set_message(t('Error the id for the cover was missing'));
  }

  $form_state['redirect'] = 'admin/config/ddb_cover_upload/upload/list';
}

/**
 * Get materials from the service.
 *
 * @return CoverServiceUpload\Model\MaterialRead
 *   Array of materials found at the service.
 *
 * @throws \CoverServiceUpload\ApiException
 */
function _ddb_cover_upload_get_materials() {
  $materials = &drupal_static(__FUNCTION__);
  if (!isset($materials)) {
    $cache = cache_get('ddb_cover_upload_materials');
    if ($cache && $cache->expire > REQUEST_TIME) {
      $materials = $cache->data;
    }
    else {
      $config = ddb_cover_upload_client_config();
      $apiInstance = new MaterialApi(
        new Client(),
        $config
      );

      $materials = $apiInstance->getMaterialCollection();

      // Expire after one day (will be cleared after uploading new covers).
      $expire = REQUEST_TIME + 86400;
      cache_set('ddb_cover_upload_materials', $materials, 'cache', $expire);
    }
  }

  return $materials;
}

/**
 * Get single material from the service.
 *
 * @param string $id
 *   The material ID (at the service).
 *
 * @return \CoverServiceUpload\Model\MaterialRead
 *   The material if found.
 *
 * @throws \CoverServiceUpload\ApiException
 *   If there is an error at the service or the material don't exists.
 */
function _ddb_cover_upload_get_material($id) {
  $materials = &drupal_static(__FUNCTION__);
  if (!isset($materials)) {
    $cache = cache_get('ddb_cover_upload_materials_id');
    if ($cache && $cache->expire > REQUEST_TIME) {
      $materials = $cache->data;
    }
    else {
      $config = ddb_cover_upload_client_config();
      $apiInstance = new MaterialApi(
        new Client(),
        $config
      );

      $materials[$id] = $apiInstance->getMaterialItem($id);

      $expire = REQUEST_TIME + 86400;
      cache_set('ddb_cover_upload_materials_id', $materials, 'cache', $expire);
    }
  }

  return $materials[$id];
}

/**
 * Delete material.
 *
 * @param int $id
 *   The id of the material to delete.
 *
 * @throws \CoverServiceUpload\ApiException
 */
function _ddb_cover_upload_delete_material($id) {
  $config = ddb_cover_upload_client_config();
  $apiInstance = new MaterialApi(
    new Client(),
    $config
  );

  $apiInstance->deleteMaterialItem($id);
}
