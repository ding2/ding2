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
  const AUTHOR = self::_PREFIX . 'author';
  const CATEGORY = self::_PREFIX . 'category';
  const LANGUAGE = self::_PREFIX . 'language';
  const SUBJECT = self::_PREFIX . 'subject';

  /**
   * Returns all valid values.
   *
   * @return string[]
   *   List of all field names.
   */
  public static function getAll() {
    return [
      self::AUTHOR,
      self::CATEGORY,
      self::LANGUAGE,
      self::SUBJECT
    ];
  }
}
