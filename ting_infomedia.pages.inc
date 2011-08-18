<?php

/**
 * @file ting_infomedia_pages.inc 
 * provide functionality and page callbacks for viewing articles and reviews from infomedia
 */

/**
 * Page callbacks return a renderable array with the CONTENT area of the page.
 * The theme system will later render and surround the content in the
 * appropriate blocks, navigation, and styling.
 *
 * If you do not want to use the theme system (for example for outputting an
 * image or XML), you should print the content yourself and not return anything.
 */

/**
 * Implent page callback function
 */
function ting_infomedia_article_view(){
  //return array('#markup' => '<p>' . t('Simple page: The quick brown fox jumps over the lazy dog.') . '</p>');
   $render_array = array();
  
  // simple render array for testing
  // $render_array['#markup'] = '<div style="color:red">'.t(' this is an article from infomedia').'</div>';
  // other options:
  // #items - items to pass to theme function
  // #theme - The theme function; e.g theme_infomedia_view_articles()
  // #title - title of page
   
   //$render_array['#markup'] = ting_infomedia_get_article();
   $render_array['#hest'] = ting_infomedia_get_article();
   $render_array['#theme'] = 'ting_infomedia_hest';  
   //$render_array['render element'] = 'element';
   
  return $render_array;
}

function ting_infomedia_get_article() {
  try{ $infomedia = new TingClientInfomediaRequest('getArticleRequest');  }
  catch(TingClientException $e){watchdog('infomedia', $e->message());}
  //krumo($request);
  return $infomedia->html(); 
}

function theme_ting_infomedia_hest($variables) {
  krumo($variables);
  return '<div style="color:blue">RENDER_KO</div>';
}

/*function ting_infomedia_hest_theme() {
return '<div style="color:blue">RENDER_KO</div>';
}*/


