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
  const _PREFIX = '_field_ting_search_';
  const AUTHOR = self::_PREFIX . 'author';
  const CATEGORY = self::_PREFIX . 'category';
  const SUBJECT = self::_PREFIX . 'subject';

  /**
   * Determines whether this field is a common field.
   *
   * @param string $fieldname
   *   Name of the field.
   *
   * @return bool
   *   Whether the field is a common field.
   */
  public static function isCommonField($fieldname) {
    return in_array($fieldname, [
      self::AUTHOR,
      self::CATEGORY,
      self::SUBJECT
    ]);
  }
}
