<?php
/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 * Preprocess variables for ting_relation.tpl.php.
 */
function template_preprocess_ting_relation(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);
  //  $variables['type_title'] = $variables['elements']['#title'];
  $variables['title'] = check_plain($object->title);
  if ($relation->type == 'dbcbib:isPartOfManifestation') {
    $variables['content']['body'] = ting_object_view($object, 'teaser');
  }
  elseif ($relation->type == 'dbcaddi:hasReview') {

     $variables['content']['contributor'] =
	array(
	      '#markup' => t('relation_contributor : ').filter_xss_admin( ($names = ting_relation_get_contributors($relation)) ? $names : '' ),
	      '#prefix' => '<div class="ting-relation-meta">',
	      '#suffix' => '</div>',
	      );

     $variables['content']['date'] =
	array(
	      '#markup' => t('relation_date : ').filter_xss_admin( $relation->object->date ),
	      '#prefix' => '<div class="ting-relation-meta">',
	      '#suffix' => '</div>',
	      );

    if (!empty($object->reply->record['dc:description'][''][0])) {
      $variables['content']['body'] = array(
        '#markup' => filter_xss_admin($object->reply->record['dc:description'][''][0]),
      );
      
     
      
    }
  }
  elseif ($relation->type == 'dbcaddi:hasSubjectDescription') {
    if ($object->creators){
      $variables['content']['byline'] = array(
        '#markup' => t('by @author', array('@author' => $object->creators)),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
      );
    }
    $variables['content']['body'] = array(
      '#markup' => filter_xss_admin($object->abstract),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
    );
    $variables['content']['description'] = array(
      '#markup' => filter_xss_admin($object->description),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
    );
  }
  else {
    $variables['content']['body'] = array(
      '#markup' => filter_xss_admin($object->abstract),
    );
  }

  $variables['online_url'] = $object->online_url ? l($object->online_url, $object->online_url) : FALSE;
}
