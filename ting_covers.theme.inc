<?php

function template_preprocess_ting_object_cover(&$variables) {
  $variables['classes'] = array('ting-cover', 
  															'ting-cover-object-id-'.$variables['object']->localId,
  															'ting-cover-style-'.$variables['image_style']);

  $variables['image'] = '';
  
  //If we already have the image available locally then just use it
  $path = ting_covers_object_path($variables['object']->localId);
  if (file_exists($path)) {
    //Generate an alt tag
    $alt = implode(', ', $variables['object']->creators).': '.$variables['object']->title;
    
    $variables['image'] = theme('image_style', array('style_name' => $variables['image_style'], 'path' => $path, 'alt' => $alt));

    //Avoid further javascript processing
    $variables['classes'] = 'ting-cover-processed';
  } elseif (cache_get('ting_covers:' . $local_id, FALSE)) {
    //We know that there is no cover available for this object so avoid
    //further javascript processing
    $variables['classes'] = 'ting-cover-processed';
  }
}

function theme_ting_object_cover($variables) {
  return '<div class="' . implode(' ', $variables['classes']) . '">' . $variables['image'] . '</div>';
}
