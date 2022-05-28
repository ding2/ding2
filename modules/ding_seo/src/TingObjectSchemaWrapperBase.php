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
   * @var string|null
   */
  protected $imageUrl;

  /**
   * TingObjectSchemaWrapperBase constructor.
   */
  public function __construct(TingObjectInterface $ting_object) {
    $this->tingObject = $ting_object;
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
  public function getDateCreated() {
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

}
