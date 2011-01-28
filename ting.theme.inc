<?php

/**
 * @file
 * Theming functions for ting.
 */

/**
 * Template preprocessor for ting objects.
 */
function template_preprocess_ting_object(&$variables) {
  $variables['object'] = $variables['elements']['#object'];

  $variables['page'] = $variables['elements']['#view_mode'] == 'full';
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

}

/**
 * Template preprocessor for ting object overview.
 */
function template_preprocess_ting_object_overview(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];

  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  $variables['page'] = $variables['elements']['#view_mode'] == 'full';
  $variables['search_result'] = $variables['elements']['#view_mode'] == 'search_result';
  $variables['title'] = check_plain($object->title);

  $variables['alternative_titles'] = array();
  $variables['other_titles'] = "";
  $variables['url'] = $object->url;
  if (isset($object->record)){
    // $variables['ting_url'] = url('ting/' . (isset($object->entities) ? 'collection' : 'object') . '/' . $object->id);
    $titles = $object->record['dc:title'];
    unset($titles['']);
    $titles = array_values(array_map('array_shift', $titles));

    $variables['other_titles'] = check_plain(implode(', ', $titles));
    if (!empty($object->record['dcterms:alternative'][''])) {
      $titles = array_values($object->record['dcterms:alternative']['']);
      $variables['alternative_titles'] = array_map('check_plain', $titles);
    }
  }

  $subjects = array();

  if ($object->subjects) {
    foreach ($object->subjects as $s) {
      $subjects[] = $s;
    }
  }

  $variables['subjects'] = implode(', ', $subjects);

  $creators = array();
  foreach ($object->creators as $i => $creator) {
    $creators[] = l($creator, 'search/ting/' . $creator, array('attributes' => array('class' => 'author')));
  }
  $variables['creators'] = implode(', ', $creators);

  if (!empty($object->date)) {
    $variables['date'] = check_plain($object->date);
  }

  $variables['abstract'] = check_plain($object->abstract);
}

/**
 * Template preprocessor for ting object details.
 */
function template_preprocess_ting_object_details(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];

  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }

  $abstracts = (array) $object->record['dcterms:abstract'];
  // Was printed in ting_object_overview
  unset($abstracts[''][0]);

  $variables['content']['abstract'] = array(
    '#type' => 'container',
    '#markup' => check_plain(implode(' ; ', ting_format_abstract($abstracts['']))),
    '#attributes' => array('class' => 'abstract'),
  );

  $variables['content']['type'] = array(
    '#theme' => 'item_list',
    '#title' => t('Type'),
    '#items' => array($object->type),
    '#attributes' => array('class' => 'type'),
  );

  if (!empty($object->record['dc:format'][''])) {
    $variables['content']['type'] = array(
      '#theme' => 'item_list',
      '#title' => t('Format'),
      '#items' => $object->record['dc:format'][''],
      '#attributes' => array('class' => 'format'),
    );
  }

  if (!empty($object->record['dcterms:isPartOf'][''])) {
    $variables['content']['is-part-of'] = array(
      '#theme' => 'item_list',
      '#title' => t('Available in'),
      '#items' => $object->record['dcterms:isPartOf'][''],
      '#attributes' => array('class' => 'is-part-of'),
    );
  }

  if (!empty($object->language)) {
    $variables['content']['language'] = array(
      '#theme' => 'item_list',
      '#title' => t('language'),
      '#items' => array($object->language),
      '#attributes' => array('class' => 'is-part-of'),
    );
  }

  if (!empty($object->record['dc:language']['oss:spoken'])) {
    $variables['content']['spoken-language'] = array(
      '#theme' => 'item_list',
      '#title' => t('Speech'),
      '#items' => $object->record['dc:language']['oss:spoken'],
      '#attributes' => array('class' => 'language'),
    );
  }

  if (!empty($object->record['dc:language']['oss:subtitles'])) {
    $variables['content']['subtitles-language'] = array(
      '#theme' => 'item_list',
      '#title' => t('Subtitles'),
      '#items' => $object->record['dc:language']['oss:subtitles'],
      '#attributes' => array('class' => 'language'),
    );
  }

  if (!empty($object->record['dc:subject']['oss:genre'])) {
    $variables['content']['genre'] = array(
      '#theme' => 'item_list',
      '#title' => t('Genre'),
      '#items' => $object->record['dc:subject']['oss:genre'],
      '#attributes' => array('class' => 'subject'),
    );
  }

  if (!empty($object->subjects)) {
    $variables['content']['subjects'] = array(
      '#theme' => 'item_list',
      '#title' => t('Subjects'),
      '#items' => $object->subjects,
      '#attributes' => array('class' => 'subject'),
    );
  }

  if (!empty($object->record['dc:subject']['dkdcplus:DK5'])) {
    $variables['content']['classification'] = array(
      '#theme' => 'item_list',
      '#title' => t('Classification'),
      '#items' => $object->record['dc:subject']['dkdcplus:DK5'],
      '#attributes' => array('class' => 'subject'),
    );
  }

  if (!empty($object->record['dcterms:spatial'][''])) {
    $variables['content']['spatial'] = array(
      '#theme' => 'item_list',
      '#items' => $object->record['dcterms:spatial'][''],
      '#attributes' => array('class' => 'spatial'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:dkind'])) {
    $variables['content']['reader'] = array(
      '#theme' => 'item_list',
      '#title' => t('Reader'),
      '#items' => $object->record['dc:contributor']['oss:dkind'],
      '#attributes' => array('class' => 'contributor'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:act'])) {
    $variables['content']['actor'] = array(
      '#theme' => 'item_list',
      '#title' => t('Actor'),
      '#items' => $object->record['dc:contributor']['oss:act'],
      '#attributes' => array('class' => 'contributor'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:mus'])) {
    $variables['content']['musician'] = array(
      '#theme' => 'item_list',
      '#title' => t('Musician'),
      '#items' => $object->record['dc:contributor']['oss:mus'],
      '#attributes' => array('class' => 'contributor'),
    );
  }

  if (!empty($object->record['dcterms:hasPart']['oss:track'])) {
    $variables['content']['tracks'] = array(
      '#theme' => 'item_list',
      '#title' => t('Contains'),
      '#items' => $object->record['dcterms:hasPart']['oss:track'],
      '#attributes' => array('class' => 'contains'),
    );
  }

  if (!empty($object->record['dcterms:isReferencedBy'][''])) {
    $variables['content']['referenced-by'] = array(
      '#theme' => 'item_list',
      '#title' => t('Referenced by'),
      '#items' => $object->record['dcterms:isReferencedBy'][''],
      '#attributes' => array('class' => 'referenced-by'),
    );
  }

  if (!empty($object->record['dc:description'])) {
    foreach ($object->record['dc:description'] as $type => $dc_description) {
      $variables['content']['description'][] = array(
        '#theme' => 'item_list',
        '#title' => t('Description'),
        '#items' => $dc_description,
        '#attributes' => array('class' => 'description'),
      );
    }
  }

  if (!empty($object->record['dc:source'][''])) {
    $variables['content']['original-title'] = array(
      '#theme' => 'item_list',
      '#title' => t('Original title'),
      '#items' => $object->record['dc:source'][''],
      '#attributes' => array('class' => 'titles'),
    );
  }

  if (!empty($object->record['dcterms:replaces'][''])) {
    $variables['content']['replaces'] = array(
      '#theme' => 'item_list',
      '#title' => t('Previous title'),
      '#items' => $object->record['dc:source'][''],
      '#attributes' => array('class' => 'titles'),
    );
  }

  if (!empty($object->record['dcterms:isReplacedBy'][''])) {
    $variables['content']['replaced-by'] = array(
      '#theme' => 'item_list',
      '#title' => t('Later title'),
      '#items' => $object->record['dc:source'][''],
      '#attributes' => array('class' => 'titles'),
    );
  }

  if (!empty($object->record['dc:identifier']['dkdcplus:ISBN'])) {
    $variables['content']['isbn'] = array(
      '#theme' => 'item_list',
      '#title' => t('ISBN no.'),
      '#items' => $object->record['dc:identifier']['dkdcplus:ISBN'],
      '#attributes' => array('class' => 'identifier'),
    );
  }

  if (!empty($object->record['dc:identifier']['dcterms:URI'])) {
    $uris = array();
    foreach ($object->record['dc:identifier']['dcterms:URI'] as $uri) {
      $uris[] = l($uri, $uri);
      }
    $variables['content']['links'] = array(
      '#theme' => 'item_list',
      '#title' => t('Host publication'),
      '#items' => $uris,
      '#attributes' => array('class' => 'identifier'),
    );
  }

  if (!empty($object->record['dkdcplus:version'][''])) {
    $variables['content']['isbn'] = array(
      '#theme' => 'item_list',
      '#title' => t('Version'),
      '#items' => $object->record['dkdcplus:version'][''],
      '#attributes' => array('class' => 'version'),
    );
  }

  if (!empty($object->record['dcterms:extent'][''])) {
    $variables['content']['extent'] = array(
      '#theme' => 'item_list',
      '#title' => t('Extent'),
      '#items' => $object->record['dcterms:extent'][''],
      '#attributes' => array('class' => 'version'),
    );
  }

  if (!empty($object->record['dc:publisher'][''])) {
    $variables['content']['publisher'] = array(
      '#theme' => 'item_list',
      '#title' => t('Publisher'),
      '#items' => $object->record['dc:publisher'][''],
      '#attributes' => array('class' => 'publisher'),
    );
  }

  if (!empty($object->record['dc:rights'][''])) {
    $variables['content']['rights'] = array(
      '#theme' => 'item_list',
      '#title' => t('Rights'),
      '#items' => $object->record['dc:rights'][''],
      '#attributes' => array('class' => 'rights'),
    );
  }
}


/**
 * Helper function to format abstracts from ting.
 */
function ting_format_abstract($string) {
  $string = str_replace('Indhold:','',$string);
  $string = str_replace(' ; ','<br/>',$string);
  $string = str_replace(' / ','<br/>',$string);

  return $string;
}
