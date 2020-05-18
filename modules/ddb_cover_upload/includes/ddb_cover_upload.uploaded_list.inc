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
    ))
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
    _ddb_cover_upload_delete_material($form_state['values']['material_id']);

    // Clear cover and materials cache.
    cache_clear_all('ddb_cover_upload', 'cache', TRUE);
  }

  drupal_set_message(t('The cover for the material has been deleted. It might take sometime before it is removed in all systems.'));
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
