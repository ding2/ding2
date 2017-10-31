<?php
/**
 * @file
 * The TingSearchCommonFields class
 */

namespace Ting\Search;

/**
 * Class TingSearchCommonFields
 *
 * Fields that are expected to be common across search providers.
 *
 * TODO: This is a good candidate for an enum.
 *
 * @package Ting\Search
 */
class TingSearchCommonFields {
  const _PREFIX = '_field_ting_search_common_field_';

  /**
   * The date the material was added to the library.
   */
  const ACQUISITION_DATE = self::_PREFIX . 'acquisition_date';

  /**
   * The author of the material.
   */
  const AUTHOR = self::_PREFIX . 'author';

  /**
   * The audience of the materiale. Eg. for open search "børnematerialer" or
   * "voksenmateriale".
   */
  const CATEGORY = self::_PREFIX . 'category';

  /**
   * The date the material was published.
   */
  const DATE = self::_PREFIX . 'date';

  /**
   * Language the material is in.
   */
  const LANGUAGE = self::_PREFIX . 'language';

  /**
   * Type of material, eg "Bog" or "Avisartikel" for Open Search.
   */
  const MATERIAL_TYPE = self::_PREFIX . 'material_type';

  /**
   * Subject tag for the material.
   */
  const SUBJECT = self::_PREFIX . 'subject';

  /**
   * Title of the materials
   */
  const TITLE = self::_PREFIX . 'title';

  /**
   * Returns all valid values.
   *
   * @return string[]
   *   List of all field names.
   */
  public static function getAll() {
    return [
      self::ACQUISITION_DATE,
      self::AUTHOR,
      self::CATEGORY,
      self::DATE,
      self::LANGUAGE,
      self::MATERIAL_TYPE,
      self::SUBJECT,
      self::TITLE,
    ];
  }
}
