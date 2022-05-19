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

abstract class TingObjectSchemaWrapperBase {
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
   * \DingSEO\TingObjectSchemaWrapperBase constructor.
   */
  public function __construct(TingObjectInterface $ting_object) {
    $this->ting_object = $ting_object;
  }

  /**
   * Get the collection URL for the wrapped ting object.
   *
   * @return string
   *   The URL for the collection with this wrapped object as primary.
   */
  public function getCollectionURL() {
    $ting_collection = ting_collection_load($this->ting_object->getId());
    $collection_path = entity_uri('ting_collection', $ting_collection)['path'];
    return url($collection_path, [
      'absolute' => TRUE,
    ]);
  }

  /**
   * Get the object URL for the wrapped ting object.
   *
   * @return string
   *   The URL for the collection with this wrapped object as primary.
   */
  public function getObjectURL() {
    $object_path = entity_uri('ting_object', $this->ting_object)['path'];
    return url($object_path, [
      'absolute' => TRUE,
    ]);
  }

  /**
   * Get image URL for the wrapped ting object.
   *
   * @return string|FALSE
   *   URL to the cover image of the material. FALSE if no cover was found.
   */
  public function getImageURL() {
    if (isset($this->image_url)) {
      return $this->image_url;
    }
    $this->image_url = FALSE;

    $ting_object_id = $this->ting_object->getId();

    // First check if this is a known negative.
    if (cache_get('ting_covers:' . $ting_object_id)) {
      return $this->image_url;
    }

    $image_path = ting_covers_object_path($ting_object_id);
    // If the file already exists we can avoid asking cover providers. Note that
    // we only ask providers if it exists, and don't initiate any downloads.
    if (file_exists($image_path) || !empty(module_invoke_all('ting_covers', [$this->ting_object]))) {
      $this->image_url = file_create_url($image_path);
    }

    return $this->image_url;
  }

  /**
   * Get dimensions for the image for the wrapped ting object.
   *
   * @return int[]|FALSE
   *   And array with the dimensions of the image, with width at index 0 and
   *   height at index 1. FALSE if no valid cover image exists.
   */
  public function getImageDimensions() {
    $image_path = ting_covers_object_path($this->ting_object->getId());
    if (file_exists($image_path) && $size = getimagesize(drupal_realpath($image_path))) {
      return array_slice($size, 0, 2);
    }
    return FALSE;
  }

  /**
   * Get work examples (editions) of the wrapped ting object.
   *
   * @return static[]
   *   An array of work examples/editions of this book, which are opensearch
   *   ting object wrappers themselves.
   */
  public function getWorkExamples() {
    $work_examples = [];

    $collection = ting_collection_load($this->ting_object->getId());
    foreach ($collection->getEntities() as $ting_entity) {
      /** @var \TingEntity $ting_entity */
      $work_examples[] = new static($ting_entity->getTingObject());
    }

    return $work_examples;
  }

  /**
   * Get the name of the wrapped ting object.
   *
   * @return string
   *   The title of the material.
   */
  public function getName() {
    return $this->ting_object->getTitle();
  }

  /**
   * Get the description of the wrapped ting object.
   *
   * @return string|FALSE
   *   The description of the material or FALSE if not present.
   */
  public function getDescription() {
    return $this->ting_object->getAbstract();
  }

  /**
   * Get the Book edition.
   *
   * @return string|FALSE
   *   The edition of the material or FALSE if it was not present.
   */
  public function getBookEdition() {
    return reset($this->ting_object->getVersion());
  }

  /**
   * Get datePublished of the wrapped ting object.
   *
   * @return string|FALSE
   *   The year of the published date or FALSE if it was not present.
   */
  public function getDatePublished() {
    return $this->ting_object->getYear();
  }

  /**
   * Get the ISBN of the wrapped ting object.
   *
   * @return string|FALSE
   *   The ISBN of the Book or FALSE if none present.
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
}
