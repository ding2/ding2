<?php
/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 * Preprocess variables for ting_relation.tpl.php.
 */
function template_preprocess_ting_relation(&$variables) {
  $all_relations = $variables['elements']['#relations'];
  foreach( $all_relations as $ns => $relations ) {
    switch( $ns  ) {
    case 'hasReview' :
      $variables['content'][$ns] = ting_relation_reviews( $relations );
      break;
    case 'hasSubjectDescription':
      $variables['content'][$ns] = ting_relation_subjects( $relations );
      break;
    case 'hasCreatorDescription':
      $variables['content'][$ns] = ting_relation_creator_description( $relations );
      break;
    case 'hasOnlineAccess':
      $variables['content'][$ns] = ting_relation_online( $relations );
      break;
    default:
      break;
    }
  }
}

/**
 * two variants(sofar) Ebrary and filmstriben
 */
function ting_relation_online( $relations ) {
  $ret = array();
  foreach( $relations as $relation ) {
    if( $relation['#ac_source'] == 'Ebrary' ) {
      $ret[] = ting_relation_online_ebrary( $relation );
    }
    elseif( $relation['#ac_source'] == 'Filmstriben (fjernlån)' ) {
      $ret[] = ting_relation_online_filmstriben( $relation );
    }
  }
  return $ret;
}

/**
 * a variant(Ebrary) of 'hasOnlineAccess'
 */
function ting_relation_online_ebrary( $relation ){
  $ebrary_url = variable_get('ting_ebrary_url');
  if( !isset($ebrary_url) ) {
    return;
  }

  $rel = $relation['#relation'];
   // simply set a button
  $url = str_replace('[URL]',$ebrary_url,$rel->uri);
  $content['online_url'] = array('#markup' => l($relation['#ac_source'], $url, array('attributes' => array('target'=>'_blank'))));

  return $content;
}

/**
 * a variant(filmstriben) of 'hasOnlineAccess'
 */
function ting_relation_online_filmstriben( $relation ) {
  $rel = $relation['#relation'];
  $content['type'] = $relation['#title'];
    // simply set a button
  $url = $rel->uri;
  $content['online_url'] = array('#markup' => l($relation['#ac_source'], $url, array('attributes' => array('target'=>'_blank'))));
  return $content;
}

function ting_relation_creator_description( $relations ) {
  foreach( $relations as $relation ) {
    $content = array();
    $ting = $relation['#object'];
    $rel = $relation['#relation'];

    $content['type'] = $relation['#title'];
    $content['title'] = $rel->object->title;

    if ( $ting->creators ) {
      $variables['content']['byline'] = ting_relation_array2names($ting->creators);
    }

    $content['abstract'] = filter_xss_admin($ting->abstract);

    // TODO online_url
    if( $url = $rel->object->online_url ) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target'=>'_blank'))));
    }

    $ret[] = $content;
  }
  return $ret;
}

function ting_relation_subjects( $relations ) {
  foreach( $relations as $relation ) {
    $content = array();
    $ting = $relation['#object'];
    $rel = $relation['#relation'];

    $content['type'] = $relation['#title'];
    $content['title'] = $rel->object->title;

    if( $ting->creators ) {
      $content['byline'] = t('by @author', array('@author' => ting_relation_array2names($ting->creators)));
    }

    $content['abstract'] = filter_xss_admin($ting->abstract);
    $content['text'] = filter_xss_admin($ting->description);

     if( $url = $rel->object->online_url ) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target'=>'_blank'))));
    }

    $ret[] = $content;
  }



  return $ret;
}

/**
 * two variants sofar - review(ac:source=Anmeldelser) and all the others (sofar only ac:source=bibliotekets materialer)
 */
function ting_relation_reviews( $relations ) {
  foreach( $relations as $relation ) {
    $ac_source = $relation['#relation']->object->ac_source;
    if( $ac_source == 'Anmeldelser' ) {
      $ret[] = ting_relation_review_other( $relation );
    }
    else {
      $ret[] = ting_relation_review( $relation );
    }
  }
  return $ret;
}

/**
 * a variant of a review (ac:source = 'bibliotekets materialer'
 */
function ting_relation_review_other( $relation ) {
  $ting = $relation['#object'];
  $rel = $relation['#relation'];
  //type title
  $content['type'] = $relation['#title'];
  //title
  $content['title'] = $rel->object->title;
  //creators
  if ($names = ting_relation_array2names($rel->object->creators)) {
    $content['byline'] = t('by @author', array('@author' => $names));
  }
  //ispartof
  if ($partOf = ting_relation_array2names($rel->object->isPartOf)) {
    $extent = $rel->object->extent;
    $content['isPartOf'] = filter_xss_admin($partOf . ', ' . $extent);
  }

  // TODO online_url
  if( $url = $rel->object->online_url ) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target'=>'_blank'))));
    }

  return $content;
}

/**
 * a variant of a review (ac:source = 'Anmeldelser'
 */
function ting_relation_review( $relation ) {
  $ting = $relation['#object'];
  $rel = $relation['#relation'];
  //type title ; generel
  $content['type'] = $relation['#title'];
  //title ; generel
  $content['title'] = $rel->object->title;
  //year
  $content['year'] = $rel->object->date;
  //creator
  $content['creator'] = ting_relation_array2names($ting->creators);
  //text
  $content['text'] = isset($ting->reply->record['dc:description'][''][0]) ? $ting->reply->record['dc:description'][''][0] : FALSE;



  if( $url = $rel->object->online_url ) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target'=>'_blank'))));
    }

  return $content;
}

/**
 * helper function
 */
function ting_relation_array2names($array) {
  if ( !isset($array) || empty($array)) {
    return false;
  }

  $ret = '';
  foreach($array as $key => $name) {
    if (strlen($ret) > 0) {
      $ret .= ', ';
    }
    $ret .= $name;
  }
  return $ret;
}
