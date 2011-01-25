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

  $creators = array();
  foreach ($object->creators as $i => $creator) {
    $creators[] = l($creator, 'ting/search/' . $creator, array('attributes' => array('class' => 'author')));
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

  // $items[] = array(
  //   '#type' => 'container',
  //   '#markup' => check_plain(implode(' ; ', ting_format_abstract($abstracts['']))),
  //   '#attributes' => array('class' => 'abstract'),
  // );
  $abstract = implode(' ; ', ting_format_abstract($abstracts['']));
  if (trim($abstract)){
    $items[] = array(
      'data' => check_plain($abstracts),
      'class' => array('abstract'),
    );
  }

  $items[] = array(
    'data' => '<h4>' . t('Type') . '</h4>',
    'children' => array($object->type),
    'class' => array('type'),
  );

  if (!empty($object->record['dc:format'][''])) {
    $items[] = array(
      'data' =>  '<h4>' . t('Format') . '</h4>',
      'children' => $object->record['dc:format'][''],
      'class' => array('dc-format'),
    );
  }

  if (!empty($object->record['dcterms:isPartOf'][''])) {
    $items[] = array(
     'data' => '<h4>' . t('Available in') . '</h4>',
     'children' => $object->record['dcterms:isPartOf'][''],
     'class' => array('is-part-of'),
   );
 }

  if (!empty($object->language)) {
    $items[] = array(
      'data' => '<h4>' . t('language') . '</h4>',
      'children' => array($object->language),
      'class' => array('language'),
    );
  }

  if (!empty($object->record['dc:language']['oss:spoken'])) {
    $items[] = array(
      'data' => '<h4>' . t('Speech') . '</h4>',
      'children' => $object->record['dc:language']['oss:spoken'],
      'class' => array('oss-spoken'),
    );
  }

  if (!empty($object->record['dc:language']['oss:subtitles'])) {
    $items[] = array(
      'data' => '<h4>' . t('Subtitles') . '</h4>',
      'children' => $object->record['dc:language']['oss:subtitles'],
      'class' => array('oss-subtitles'),
    );
  }

  if (!empty($object->record['dc:subject']['oss:genre'])) {
    $items[] = array(
      'data' => '</h4>' . t('Genre') . '</h4>',
      'children' => $object->record['dc:subject']['oss:genre'],
      'class' => array('oss-genre'),
    );
  }

  if (!empty($object->subjects)) {
    $items[] = array(
      'data' => '<h4>' . t('Subjects') . '</h4>',
      'children' => $object->subjects,
      'class' => array('subjects'),
    );
  }

  if (!empty($object->record['dc:subject']['dkdcplus:DK5'])) {
    $items[] = array(
      'data' => '<h4>' . t('Classification') . '</h4>',
      'children' => $object->record['dc:subject']['dkdcplus:DK5'],
      'class' => array('dkdcplus-dk5'),
    );
  }

  if (!empty($object->record['dcterms:spatial'][''])) {
    $items[] = array(
      'children' => $object->record['dcterms:spatial'][''],
      'class' => array('dcterms-spatial'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:dkind'])) {
    $items[] = array(
      'data' => '<h4>' . t('Reader') . '</h4>',
      'children' => $object->record['dc:contributor']['oss:dkind'],
      'class' => array('oss-dkind'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:act'])) {
    $items[] = array(
      'data' => '<h4>' . t('Actor') . '</h4>',
      'children' => $object->record['dc:contributor']['oss:act'],
      'class' => array('oss-act'),
    );
  }

  if (!empty($object->record['dc:contributor']['oss:mus'])) {
    $items[] = array(
      'data' => '<h4>' . t('Musician') . '</h4>',
      'children' => $object->record['dc:contributor']['oss:mus'],
      'class' => array('oss-mus'),
    );
  }

  if (!empty($object->record['dcterms:hasPart']['oss:track'])) {
    $items[] = array(
      'data' => '<h4>' . t('Contains') . '</h4>',
      'children' => $object->record['dcterms:hasPart']['oss:track'],
      'class' => array('oss-track'),
    );
  }

  // if (!empty($object->record['dcterms:isReferencedBy'][''])) {
  //   $items[] = array(
  //     '#theme' => 'item_list',
  //     '#title' => t('Referenced by'),
  //     '#items' => $object->record['dcterms:isReferencedBy'][''],
  //     '#attributes' => array('class' => 'referenced-by'),
  //   );
  // }

  // if (!empty($object->record['dc:description'])) {
  //   foreach ($object->record['dc:description'] as $type => $dc_description) {
  //     $items[] = array(
  //       '#theme' => 'item_list',
  //       '#title' => t('Description'),
  //       '#items' => $dc_description,
  //       '#attributes' => array('class' => 'description'),
  //     );
  //   }
  // }

  // if (!empty($object->record['dc:source'][''])) {
  //   $items[] = array(
  //     '#theme' => 'item_list',
  //     '#title' => t('Original title'),
  //     '#items' => $object->record['dc:source'][''],
  //     '#attributes' => array('class' => 'titles'),
  //   );
  // }

  // if (!empty($object->record['dcterms:replaces'][''])) {
  //   $items[] = array(
  //     '#theme' => 'item_list',
  //     '#title' => t('Previous title'),
  //     '#items' => $object->record['dc:source'][''],
  //     '#attributes' => array('class' => 'titles'),
  //   );
  // }

  // if (!empty($object->record['dcterms:isReplacedBy'][''])) {
  //   $items[] = array(
  //     '#theme' => 'item_list',
  //     '#title' => t('Later title'),
  //     '#items' => $object->record['dc:source'][''],
  //     '#attributes' => array('class' => 'titles'),
  //   );
  // }

  // if (!empty($object->record['dc:identifier']['dkdcplus:ISBN'])) {
  //   $items[] = array(
  //     '#theme' => 'item_list',
  //     '#title' => t('ISBN no.'),
  //     '#items' => $object->record['dc:identifier']['dkdcplus:ISBN'],
  //     '#attributes' => array('class' => 'identifier'),
  //   );
  // }

  if (!empty($object->record['dc:identifier']['dkdcplus:ISBN'])) {
    $items[] = array(
      'data' => '<h4>' . t('ISBN no.') . '</h4>',
      'children' => $object->record['dc:identifier']['dkdcplus:ISBN'],
      'class' => array('identifier'),
    );
  }

  if (!empty($object->record['dc:identifier']['dcterms:URI'])) {
    $uris = array();
    foreach ($object->record['dc:identifier']['dcterms:URI'] as $uri) {
      $uris[] = l($uri, $uri);
      }
    $items[] = array(
      'data' => '<h4>' . t('Host publication') . '</h4>',
      'children' => $uris,
      'class' => array('dcterms-uri'),
    );
  }

  if (!empty($object->record['dkdcplus:version'][''])) {
    $items[] = array(
      'data' => '<h4>' . t('Version') . '</h4>',
      'children' => $object->record['dkdcplus:version'][''],
      'class' => array('dkdcplus-version'),
    );
  }

  if (!empty($object->record['dcterms:extent'][''])) {
    $items[] = array(
      'data' => '<h4>' . t('Extent') . '</h4>',
      'children' => $object->record['dcterms:extent'][''],
      'class' => array('dcterms-extent'),
    );
  }

  if (!empty($object->record['dc:publisher'][''])) {
    $items[] = array(
      'data' => '<h4>' . t('Publisher') . '</h4>',
      'children' => $object->record['dc:publisher'][''],
      'class' => array('dc-publisher'),
    );
  }

  if (!empty($object->record['dc:rights'][''])) {
    $items[] = array(
      'data' => '<h4>' . t('Rights') . '</h4>',
      'children' => $object->record['dc:rights'][''],
      'class' => array('dc-rights'),
    );
  }

  $variables['content'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
  );
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