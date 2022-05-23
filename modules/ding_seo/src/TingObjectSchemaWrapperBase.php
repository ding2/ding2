<?php

namespace DingSEO;

use Ting\TingObjectInterface;

/**
 * Class TingObjectSchemaWrapperBase.
 *
 * A base class with common functionality across search providers that can be
 * extended by provider specific implementations of schema wrappers.
 */
abstract class TingObjectSchemaWrapperBase implements TingObjectSchemaWrapperInterface {
  /**
   * The wrapped ting object.
   *
   * @var \Ting\TingObjectInterface
   */
  protected $tingObject;

  /**
   * The URL to the cover image of the material (static cache).
   *
   * @var string
   */
  protected $imageUrl;

  /**
   * Whether the work example has borrow action.
   *
   * @var bool|null
   */
  protected $hasBorrowAction;

  /**
   * TingObjectSchemaWrapperBase constructor.
   */
  public function __construct(TingObjectInterface $ting_object, $has_borrow_action = NULL) {
    $this->tingObject = $ting_object;
    $this->hasBorrowAction = $has_borrow_action;
  }

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->getObjectUrl();
  }

  /**
   * {@inheritdoc}
   */
  public function getUrl() {
    return $this->getObjectUrl();
  }

  /**
   * Get the absolute URL of the ting object.
   *
   * @return string
   *   The URL of the ting object.
   */
  protected function getObjectUrl() {
    $object_path = entity_uri('ting_object', $this->tingObject)['path'];
    return url($object_path, [
      'absolute' => TRUE,
    ]);
  }

  /**
   * {@inheritdoc}
   */
  public function getImageUrl() {
    if (isset($this->imageUrl)) {
      return $this->imageUrl;
    }
    $this->imageUrl = FALSE;

    $ting_object_id = $this->tingObject->getId();
    $covers = ting_covers_get([$ting_object_id]);

    if (isset($covers[$ting_object_id])) {
      // The return value is a public:// URI.
      $this->imageUrl = file_create_url($covers[$ting_object_id]);
    }

    return $this->imageUrl;
  }

  /**
   * {@inheritdoc}
   */
  public function getImageDimensions() {
    $image_path = ting_covers_object_path($this->tingObject->getId());
    if (file_exists($image_path) && $size = getimagesize(drupal_realpath($image_path))) {
      return array_slice($size, 0, 2);
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getWorkExamples() {
    $collection = ting_collection_load($this->tingObject->getId());
    /** @var \TingEntity[] $ting_entities */
    $ting_entities = $collection->getEntities();

    // Instead of deferring reservability check, use the opportunity now to
    // check reservability for all 'library_material' work examples at once.
    $local_ids = array_map(function ($ting_entity) {
      if ($ting_entity->is('library_material')) {
        return $ting_entity->localId;
      }
    }, $ting_entities);
    $local_ids = array_filter($local_ids);

    $reservability = [];
    if (!empty($local_ids)) {
      $reservability = ding_provider_invoke('reservation', 'is_reservable', $local_ids);
    }

    $work_examples = array_map(function ($ting_entity) use ($reservability) {
      $local_id = $ting_entity->localId;
      $has_borrow_action = isset($reservability[$local_id]) ? $reservability[$local_id] : FALSE;
      return new static($ting_entity->getTingObject(), $has_borrow_action);
    }, $ting_entities);

    return $work_examples;
  }

  /**
   * {@inheritdoc}
   */
  public function getName() {
    return $this->tingObject->getTitle();
  }

  /**
   * {@inheritdoc}
   */
  public function getDescription() {
    return $this->tingObject->getAbstract();
  }

  /**
   * {@inheritdoc}
   */
  public function getBookEdition() {
    return reset($this->tingObject->getVersion());
  }

  /**
   * {@inheritdoc}
   */
  public function getDatePublished() {
    return $this->tingObject->getYear();
  }

  /**
   * {@inheritdoc}
   */
  public function getIsbn() {
    $isbn_list = $this->tingObject->getIsbn();

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
    if (isset($this->hasBorrowAction)) {
      return $this->hasBorrowAction;
    }

    $this->hasBorrowAction = FALSE;

    /** @var \TingEntity $ting_entity */
    $ting_entity = ding_entity_load($this->ting_object->getId());
    if ($ting_entity->is('library_material')) {
      $local_id = $this->ting_object->getSourceId();
      $reservability = ding_provider_invoke('reservation', 'is_reservable', [$local_id]);
      $this->hasBorrowAction = $reservability[$local_id];
    }

    return $this->hasBorrowAction;
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
    return $this->getObjectUrl();
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
