<?php

namespace OpenSearch;

use DingSEO\TingObjectSchemaWrapperBase;
use DingSEO\TingObjectSchemaWrapperInterface;

/**
 * Class OpenSearchTingObjectSchemaWrapper.
 *
 * Opensearch provider implementaion of ting ojbect Schema.org wrapper.
 */
class OpenSearchTingObjectSchemaWrapper extends TingObjectSchemaWrapperBase {

  /**
   * {@inheritdoc}
   */
  public function getSchemaType() {
    // Use simple material type checking for now to decide a ting objects schema
    // type. We will have to get more complex in the future, when we have to
    // distinguish between movies and tv-series for example.
    // For now this is opensearch speficic anb based and DKABM types:
    // http://www.danbib.dk/docs/abm/types.xml.
    $material_type = drupal_strtolower($this->tingObject->getType());

    $schema_type_mapping = [
      TingObjectSchemaWrapperInterface::SCHEMA_BOOK => [
        'bog',
        'bog stor skrift',
        'billedbog',
        'ebog',
        'lydbog (bånd)',
        'lydbog (cd)',
        'lydbog (net)',
        'lydbog (cd-mp3)',
        'årbog',
      ],
      TingObjectSchemaWrapperInterface::SCHEMA_MOVIE => [
        'dvd',
        'dvd (film)',
        'blu-ray',
        'blu-ray 4k',
        'blu-ray 3d',
        'film',
        'film (net)',
        'video',
      ],
    ];

    foreach ($schema_type_mapping as $schema_type => $material_types) {
      if (in_array($material_type, $material_types)) {
        return $schema_type;
      }
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getAuthors() {
    $contributers = $this->getCreatorsContributorsCombined();
    return isset($contributers['dkdcplus:aut']) ? $contributers['dkdcplus:aut'] : [];
  }

  /**
   * {@inheritdoc}
   */
  public function getDirectors() {
    $contributers = $this->getCreatorsContributorsCombined();
    return isset($contributers['dkdcplus:drt']) ? $contributers['dkdcplus:drt'] : [];
  }

  /**
   * {@inheritdoc}
   */
  public function getActors() {
    $contributers = $this->getCreatorsContributorsCombined();
    return isset($contributers['dkdcplus:act']) ? $contributers['dkdcplus:act'] : [];
  }

  /**
   * {@inheritdoc}
   */
  public function getProducers() {
    $contributers = $this->getCreatorsContributorsCombined();
    return isset($contributers['dkdcplus:pro']) ? $contributers['dkdcplus:pro'] : [];
  }

  /**
   * {@inheritdoc}
   */
  public function getComposers() {
    $contributers = $this->getCreatorsContributorsCombined();
    return isset($contributers['dkdcplus:cmp']) ? $contributers['dkdcplus:cmp'] : [];
  }

  /**
   * {@inheritdoc}
   */
  public function getBookFormat() {
    // Not possible to map anything to SCHEMA_BOOK_FORMAT_PAPERBACK.
    $book_format_mapping = [
      TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_EBOOK => [
        'ebog',
      ],
      TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_HARDCOVER => [
        'bog',
        'bog stor skrift',
        'billedbog',
      ],
      TingObjectSchemaWrapperInterface::SCHEMA_BOOK_FORMAT_AUDIOBOOK => [
        'lydbog (bånd)',
        'lydbog (cd)',
        'lydbog (net)',
        'lydbog (cd-mp3)',
      ],
    ];

    $material_type = drupal_strtolower($this->tingObject->getType());
    foreach ($book_format_mapping as $book_format => $material_types) {
      if (in_array($material_type, $material_types)) {
        return $book_format;
      }
    }
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getInLanguage() {
    // Returns language in full name in danish e.g. "Dansk", "Spansk".
    $language = $this->tingObject->getLanguage();
    $language = drupal_strtolower($language);

    // Drupal maintains a list of languages keyed by ISO 639-1 language codes,
    // which we need to return.
    include_once DRUPAL_ROOT . '/includes/iso.inc';
    $languages = _locale_get_predefined_list();

    foreach ($languages as $code => $names) {
      // The first entry in $names array is language full name in english.
      // Attempt to translate it to danish and compare with the danish value
      // returned from opensearch.
      $translated_name = t($names[0]);

      if (drupal_strtolower($translated_name) == $language) {
        return $code;
      }
    }

    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getDuration() {
    $extent = $this->tingObject->getExtent();

    if (empty($extent)) {
      return FALSE;
    }
    // Should return string|FALSE but appears sometimes it's an array.
    if (is_array($extent)) {
      $extent = reset($extent);
    }

    // The format is "<hh> t. <mm> min.", but can have variations:
    // - 2 t. 26 min.
    // - 88 min.
    // - 82 min.
    // - ca. 3 t., 15 min.
    // - 2 t., 10 min.
    // - Ca. 97 min.
    // We use two capture groups to capture the value and unit separately.
    $pattern = '/(\d+)\s*(t|min)/';
    if (preg_match_all($pattern, $extent, $matches)) {
      $hours = 0;
      $minutes = 0;
      foreach ($matches[1] as $key => $value) {
        $unit = $matches[2][$key];
        if ($unit == 't') {
          $hours += $value;
        }
        else {
          $minutes += $value;
        }
      }
      $hours += floor($minutes / 60);
      $minutes = $minutes % 60;

      // ISO 8601 duration.
      // See: https://en.wikipedia.org/wiki/ISO_8601#Durations
      return "PT{$hours}H{$minutes}M";
    }
    return FALSE;
  }

  /**
   * Get all creators and contributors combined.
   *
   * Helper function to get all creators and contributors combined and preserve
   * DKABM function codes. Some function codes can be on both dc:creator and
   * dc:contributor, so this is useful to ensure we don't miss any.
   *
   * @return string[]
   *   An array of creators and contributor names keyed by DKABM function codes.
   */
  private function getCreatorsContributorsCombined() {
    $record = $this->tingObject->record;
    $creators = isset($record['dc:creator']) ? $record['dc:creator'] : [];
    $contributers = isset($record['dc:contributor']) ? $record['dc:contributor'] : [];
    // We don't know if a given function code can be on both so merge them
    // recursively to ensure we don't miss any.
    return array_merge_recursive($creators, $contributers);
  }

  /**
   * {@inheritdoc}
   */
  public function getSameAs() {
    // Link to work on bibliotek.dk using basis namespace.
    $id = "870970-basis:{$this->tingObject->getSourceId()}";
    return url("https://bibliotek.dk/work/$id", ['external' => TRUE]);
  }

}
