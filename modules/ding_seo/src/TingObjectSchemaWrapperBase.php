<?php
/**
 * @file
 * Defines \DingSEO\TingObjectSchemaWrapperBase.
 *
 * A base class with common functionality across search providers that can be
 * extended by provider specific implementations of schema wrappers.
 */

namespace DingSEO;

use Ting\TingObjectInterface;

abstract class TingObjectSchemaWrapperBase implements TingObjectSchemaWrapperInterface {
  /**
   * @var \Ting\TingObjectInterface.
   *   The wrapped ting object.
   */
  protected $ting_object;

  /**
   * @var string
   *   The URL to the cover image of the material (static cache).
   */
  protected $image_url;

  /**
   * @var bool|null
   *   Whether the work example has borrow action.
   */
  protected $has_borrow_action;

  /**
   * TingObjectSchemaWrapperBase constructor.
   */
  public function __construct(TingObjectInterface $ting_object, $has_borrow_action = NULL) {
    $this->ting_object = $ting_object;
    $this->has_borrow_action = $has_borrow_action;
  }

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->getObjectURL();
  }

  /**
   * {@inheritdoc}
   */
  public function getUrl() {
    return $this->getObjectURL();
  }

  /**
   * Get the absolute URL of the ting object.
   *
   * @return string
   */
  protected function getObjectURL() {
    $object_path = entity_uri('ting_object', $this->ting_object)['path'];
    return url($object_path, [
      'absolute' => TRUE,
    ]);
  }

  /**
   * {@inheritdoc}
   */
  public function getImageURL() {
    if (isset($this->image_url)) {
      return $this->image_url;
    }
    $this->image_url = FALSE;

    $ting_object_id = $this->ting_object->getId();
    $covers = ting_covers_get([$ting_object_id]);

    if (isset($covers[$ting_object_id])) {
      // The return value is a public:// URI.
      $this->image_url = file_create_url($covers[$ting_object_id]);
    }

    return $this->image_url;
  }

  /**
   * {@inheritdoc}
   */
  public function getImageDimensions() {
    $image_path = ting_covers_object_path($this->ting_object->getId());
    if (file_exists($image_path) && $size = getimagesize(drupal_realpath($image_path))) {
      return array_slice($size, 0, 2);
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getWorkExamples() {
    $collection = ting_collection_load($this->ting_object->getId());
    /** @var \TingEntity[] $ting_entities */
    $ting_entities = $collection->getEntities();

    // Instead of deferring reservability check, use the opportunity now to
    // check reservability for all 'library_material' work examples at once.
    $localIds = array_map(function ($ting_entity) {
      if ($ting_entity->is('library_material')) {
        return $ting_entity->localId;
      }
    }, $ting_entities);
    $localIds = array_filter($localIds);

    $reservability = [];
    if (!empty($localIds)) {
      $reservability = ding_provider_invoke('reservation', 'is_reservable', $localIds);
    }

    $work_examples = array_map(function ($ting_entity) use ($reservability) {
      $localId = $ting_entity->localId;
      $has_borrow_action = isset($reservability[$localId]) ? $reservability[$localId] : FALSE;
      return new static($ting_entity->getTingObject(), $has_borrow_action);
    }, $ting_entities);

    return $work_examples;
  }

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return $this->ting_object->getTitle();
  }

  /**
   * {@inheritdoc}
   */
  public function getDescription() {
    return $this->ting_object->getAbstract();
  }

  /**
   * {@inheritdoc}
   */
  public function getBookEdition() {
    return reset($this->ting_object->getVersion());
  }

  /**
   * {@inheritdoc}
   */
  public function getDatePublished() {
    return $this->ting_object->getYear();
  }

  /**
   * {@inheritdoc}
   */
  public function getISBN() {
    $isbn_list = $this->ting_object->getIsbn();

    // Prefer 13 digit ISBN-13 nunbers.
    $isbn13_list = array_filter($isbn_list, function ($isbn) {
      $isbn_cmp = str_replace([' ', '-'], '', $isbn);
      if (strlen($isbn_cmp) === 13) {
        return $isbn;
      }
    });

    if (!empty($isbn13_list)) {
      return reset($isbn13_list);
    }
    return reset($isbn_list);
  }

  /**
   * {@inheritdoc}
   */
  public function hasBorrowAction() {
    if (isset($this->has_borrow_action)) {
      return $this->has_borrow_action;
    }

    $this->has_borrow_action = FALSE;

    /** @var \TingEntity $ting_entity */
    $ting_entity = ding_entity_load($this->ting_object->getId());
    if ($ting_entity->is('library_material')) {
      $local_id = $this->ting_object->getSourceId();
      $reservability = ding_provider_invoke('reservation', 'is_reservable', [$local_id]);
      $this->has_borrow_action = $reservability[$local_id];
    }

    return $this->has_borrow_action;
  }

  /**
   * {@inheritdoc}
   */
  public function getLenderLibraryId() {
    $lender_library_id = variable_get('ding_seo_lender_library', NULL);
    if (!isset($lender_library_id)) {
      // Fallback to picking first library. This should be the correct in most
      // cases since it will be the first created.
      $library_nodes = ding_seo_get_library_nodes();
      $lender_library_id = reset(array_keys($library_nodes));
    }

    return url("node/$lender_library_id", ['absolute' => TRUE]);
  }

  /**
   * {@inheritdoc}
   */
  public function getBorrowActionTargetUrl() {
    return $this->getObjectURL();
  }

  /**
   * {@inheritdoc}
   */
  public function getBorrowActionTargetPlatform() {
    return [
      'https://schema.org/DesktopWebPlatform',
    ];
  }
}
