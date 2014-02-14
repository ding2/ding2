<?php

/**
 * @file
 *
 * Contains admin page callback for ting search context module.
 */

/**
 * Form builder (admin/content/ting-search-context)
 */
function ting_search_context_admin_overview() {
	$header = array(
	  // creating array that contains data from first cell
	  array('data' => t('Header cell1')),  
	  // second cell
	  array('data' => t('Header cell2')),  
	  // and third cell
	  array('data' => t('Header cell3'))  
	);
	// creating first row
  $rows[] = array(
    // output of first cell in 1 row
    array('data' => t('Row 1 – Cell 1')), 
    // second cell
    array('data' => t('Row 1 – Cell 2')), 
    // third cell 
    array('data' => t('Row 1 – Cell 3'))  
  );
  //second row output
  $rows[] = array( 
    array('data' => t('Row 2 – Cell 1')), 
    array('data' => t('Row 2 – Cell 2')),
    array('data' => t('Row 2 – Cell 3'))
  ); 
  return array(
  	'#theme' => 'table',
  	'#header' => $header,
  	'#rows' => $rows,
  );
}