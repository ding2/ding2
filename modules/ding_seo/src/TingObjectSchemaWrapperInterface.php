<?php
/**
 * @file
 * Defines \DingSEO\TingObjectSchemaWrapperInterface.
 *
 * Implemented by search providers to provide a compatible data interface for
 * producing JSON-LD for ting objects.
 */

namespace DingSEO;

interface TingObjectSchemaWrapperInterface {
  /**
   * https://schema.org/Book.
   */
  const SCHEMA_BOOK = 'Book';
  /**
   * https://schema.org/Movie.
   */
  const SCHEMA_MOVIE = 'Movie';

  /**
   * https://schema.org/bookFormat.
   */
  const SCHEMA_BOOK_FORMAT_EBOOK = 'http://schema.org/EBook';
  const SCHEMA_BOOK_FORMAT_PAPERBACK = 'http://schema.org/Paperback';
  const SCHEMA_BOOK_FORMAT_HARDCOVER = 'http://schema.org/Hardcover';
  const SCHEMA_BOOK_FORMAT_AUDIOBOOK = 'http://schema.org/AudiobookFormat';

  /**
   * Get the schema.org @id of the wrapped ting object.
   *
   * @return string
   */
  public function getId();

  /**
   * Get the URL of the wrapped ting object.
   *
   * @return string
   */
  public function getUrl();

  /**
   * Get work examples (editions) of the wrapped ting object.
   *
   * @return \DingSEO\TingObjectSchemaWrapperInterface[]
   *   An array of work examples/editions of this book, which are opensearch
   *   ting object wrappers themselves.
   */
  public function getWorkExamples();

  /**
   * Get image URL for the wrapped ting object.
   *
   * @return string|FALSE
   *   URL to the cover image of the material. FALSE if no cover was found.
   */
  public function getImageURL();

  /**
   * Get dimensions for the image for the wrapped ting object.
   *
   * @return int[]|FALSE
   *   And array with the dimensions of the image, with width at index 0 and
   *   height at index 1. FALSE if no valid cover image exists.
   */
  public function getImageDimensions();

  /**
   * Get the schema type for the wrapped ting object.
   *
   * @return string|FALSE
   *   A string with one of the supported schema types for ting objects:
   *    - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_BOOK.
   *    - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_MOVIE.
   *   FALSE if schema type could not be determined for the ting object.
   */
  public function getSchemaType();

  /**
   * Get the name of the wrapped ting object.
   *
   * @return string
   *   The title of the material.
   */
  public function getName();

  /**
   * Get the author(s) of the wrapped ting object.
   *
   * @return string[]
   *   Array of author names with surname last. Empty if none was found.
   */
  public function getAuthors();

  /**
   * Get the director(s) of the wrapped ting object.
   *
   * @return string[]
   *   Array of director names with surname last. Empty if none was found.
   */
  public function getDirectors();

  /**
   * Get the actors of the wrapped ting object.
   *
   * @return string[]
   *   Array of actor names with surname last. Empty if none was found.
   */
  public function getActors();

  /**
   * Get the producer(s) of the wrapped ting object.
   *
   * @return string[]
   *   Array of producer names with surname last. Empty if none was found.
   */
  public function getProducers();

  /**
   * Get the composer(s) of the wrapped ting object.
   *
   * @return string[]
   *   Array of composer names with surname last. Empty if none was found.
   */
  public function getComposers();

  /**
   * Get the description of the wrapped ting object.
   *
   * @return string|FALSE
   *   The description of the material or FALSE if not present.
   */
  public function getDescription();

  /**
   * Get the Book edition.
   *
   * @return string|FALSE
   *   The edition of the material or FALSE if it was not present.
   */
  public function getBookEdition();

  /**
   * Get datePublished of the wrapped ting object.
   *
   * @return string|FALSE
   *   The year of the published date or FALSE if it was not present.
   */
  public function getDatePublished();

  /**
   * Get the ISBN of the wrapped ting object.
   *
   * @return string|FALSE
   *   The ISBN of the Book or FALSE if none present.
   */
  public function getISBN();

  /**
   * Get the Schema.org bookFormat of the wrapped ting object.
   *
   * @return string|FALSE
   *   A string with one of the possible bookFormat values:
   *     - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_EBOOK
   *     - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_PAPERBACK
   *     - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_HARDCOVER
   *     - \DingSEO\TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_AUDIOBOOK
   *   FALSE if bookFormat could not be determined.
   */
  public function getBookFormat();

  /**
   * Get the ISO 639-1 two-letter language code of the material.
   *
   * @return string|FALSE
   */
  public function getInLanguage();

  /**
   * Get duration of the wrapped ting object.
   *
   * @return string|FALSE
   *   The duration in ISO 8601 date format or FALSE if it could not be
   *   determined.
   */
  public function getDuration();

  /**
   * Whether the wrapped ting_object has borrow action.
   *
   * @return bool
   */
  public function hasBorrowAction();

  /**
   * The @id of the Library to use as "lender" on borrow actions.
   *
   * @return string
   */
  public function getLenderLibraryId();

  /**
   * Get target URL for the material's borrow action.
   *
   * @return string
   */
  public function getBorrowActionTargetUrl();

  /**
   * Get array of target action platforms for the material's borrow action.
   *
   * @return array
   */
  public function getBorrowActionTargetPlatform();

  /**
   * URL of a reference page that identifies the material.
   *
   * @return string|FALSE
   */
  public function getSameAs();
}
