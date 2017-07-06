<?php
/**
 * @file
 * ding_ting_frontend.ting_field_search_default_profiles.inc
 */

/**
 * Implements hook_ting_field_search_default_profiles().
 */
function ding_ting_frontend_ting_field_search_default_profiles() {
  $export = array();

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'artikler';
  $profile->title = 'Artikler';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.acsource any "ebsco masterfile tidsskriftsartikler biography in context avisartikler store danske science in context litteratursiden historiens verden 1001 fortællinger forfatterweb faktalink"',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 0,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '12',
      'term_count' => '12',
    ),
  );
  $profile->weight = 6;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '13',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.type',
      'pid' => '13',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.subject',
      'pid' => '13',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.creator',
      'pid' => '13',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.language',
      'pid' => '13',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.date',
      'pid' => '13',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.category',
      'pid' => '13',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-4',
    ),
  );
  $export['artikler'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'boeger';
  $profile->title = 'Bøger (skønlitteratur)';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.acsource=bibliotekskatalog and term.type=bog and (dk=sk or dk=82* or dk=83* or dk=84* or dk=85* or dk=86* or dk=87* or dk=88.4* or dk=88.6* or dk=88.7* or dk=88.8*)',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '12',
      'term_count' => '5',
    ),
  );
  $profile->weight = -1;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.category',
      'pid' => '7',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.creator',
      'pid' => '7',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.titleSeries',
      'pid' => '7',
      'title' => 'Serie (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.literaryForm',
      'pid' => '7',
      'title' => 'Form',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.subject',
      'pid' => '7',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.language',
      'pid' => '7',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.geographic',
      'pid' => '7',
      'title' => 'Handlingen forgår i:',
      'sorting' => 'default',
      'weight' => '-4',
    ),
    7 => array(
      'name' => 'facet.date',
      'pid' => '7',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-3',
    ),
    8 => array(
      'name' => 'facet.audience',
      'pid' => '7',
      'title' => 'Anvendelighed',
      'sorting' => 'default',
      'weight' => '-2',
    ),
    9 => array(
      'name' => 'facet.lix',
      'pid' => '7',
      'title' => 'Lixtal',
      'sorting' => 'default',
      'weight' => '-1',
    ),
    10 => array(
      'name' => 'facet.let',
      'pid' => '7',
      'title' => 'Lette bøger (Lettal)',
      'sorting' => 'default',
      'weight' => '0',
    ),
  );
  $export['boeger'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'boeger_fag';
  $profile->title = 'Bøger (faglitteratur)';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.acsource=bibliotekskatalog and term.type=bog not (dk=sk or dk=82* or dk=83* or dk=84* or dk=85* or dk=86* or dk=87* or dk=88.4* or dk=88.6* or dk=88.7* or dk=88.8*)',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '10',
      'term_count' => '5',
    ),
  );
  $profile->weight = 0;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.creator',
      'pid' => '8',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.subject',
      'pid' => '8',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.dk5',
      'pid' => '8',
      'title' => 'Klassemærke',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.language',
      'pid' => '8',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.category',
      'pid' => '8',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.level',
      'pid' => '8',
      'title' => 'Niveau',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.date',
      'pid' => '8',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-4',
    ),
  );
  $export['boeger_fag'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'cd';
  $profile->title = 'CD';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => '(ma=xc and ma=lm) or (ma=xc and ma=th) not (ma=mu or ma=ly or ma=xk or dk=sk)',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '5',
      'term_count' => '5',
    ),
  );
  $profile->weight = 8;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.primaryCreator',
      'pid' => '15',
      'title' => 'Hovedkunstner (vis kun hele cd\'er)',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.creator',
      'pid' => '15',
      'title' => 'Kunstner (vis også cd\'er med enkelte numre)',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.subject',
      'pid' => '15',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.date',
      'pid' => '15',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    4 => array(
      'name' => 'facet.category',
      'pid' => '15',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-5',
    ),
  );
  $export['cd'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'dvd_bluray';
  $profile->title = 'Film/DVD/Bluray/VHS';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.acsource=filmstriben or (term.acsource=bibliotekskatalog and term.workType=movie not (term.type=bog or term.type="film (net)" or ma=xc))',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '15',
      'term_count' => '5',
    ),
  );
  $profile->weight = 7;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '14',
      'title' => 'KIlde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.type',
      'pid' => '14',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.category',
      'pid' => '14',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.audience',
      'pid' => '14',
      'title' => 'Aldersgrænser (PEGI)',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.genre',
      'pid' => '14',
      'title' => 'Genre',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.geographic',
      'pid' => '14',
      'title' => 'Handlingen foregår i:',
      'sorting' => 'alphabetical',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.subject',
      'pid' => '14',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-4',
    ),
    7 => array(
      'name' => 'facet.date',
      'pid' => '14',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-3',
    ),
    8 => array(
      'name' => 'facet.language',
      'pid' => '14',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-2',
    ),
    9 => array(
      'name' => 'facet.nationality',
      'pid' => '14',
      'title' => 'Nationalitet',
      'sorting' => 'default',
      'weight' => '-1',
    ),
    10 => array(
      'name' => 'facet.titleSeries',
      'pid' => '14',
      'title' => 'Serie (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '0',
    ),
    11 => array(
      'name' => 'facet.creator',
      'pid' => '14',
      'title' => 'Skuespillere (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '1',
    ),
  );
  $export['dvd_bluray'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'eboeger_danske';
  $profile->title = 'Ebøger (sprog: dansk)';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'ma=xe and term.type=ebog and sp=dan',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '5',
      'term_count' => '5',
    ),
  );
  $profile->weight = 3;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '10',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.category',
      'pid' => '10',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.creator',
      'pid' => '10',
      'title' => 'Forfatter/Institution (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.genre',
      'pid' => '10',
      'title' => 'Genre',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.titleSeries',
      'pid' => '10',
      'title' => 'Serie (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.geographic',
      'pid' => '10',
      'title' => 'Handlingen foregår i:',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.subject',
      'pid' => '10',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-4',
    ),
    7 => array(
      'name' => 'facet.date',
      'pid' => '10',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-3',
    ),
    8 => array(
      'name' => 'facet.lix',
      'pid' => '10',
      'title' => 'Lixtal',
      'sorting' => 'default',
      'weight' => '-2',
    ),
    9 => array(
      'name' => 'facet.let',
      'pid' => '10',
      'title' => 'Lette ebøger (Lettal)',
      'sorting' => 'default',
      'weight' => '-1',
    ),
  );
  $export['eboeger_danske'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'eboeger_udenlandske';
  $profile->title = 'Ebøger (andre sprog)';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'ma=xe and term.type=ebog not sp=dan',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '7',
      'term_count' => '7',
    ),
  );
  $profile->weight = 4;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '11',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.creator',
      'pid' => '11',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.subject',
      'pid' => '11',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.language',
      'pid' => '11',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    4 => array(
      'name' => 'facet.category',
      'pid' => '11',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    5 => array(
      'name' => 'facet.date',
      'pid' => '11',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-4',
    ),
  );
  $export['eboeger_udenlandske'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'lydboeger';
  $profile->title = 'Lydbøger';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'ma=ly not (dk=78* or em=sprog*)',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '5',
      'term_count' => '5',
    ),
  );
  $profile->weight = 5;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '12',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.type',
      'pid' => '12',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.creator',
      'pid' => '12',
      'title' => 'Forfatter',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.titleSeries',
      'pid' => '12',
      'title' => 'Serie (alfabetisk)',
      'sorting' => 'alphabetical',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.literaryForm',
      'pid' => '12',
      'title' => 'Form',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.subject',
      'pid' => '12',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.geographic',
      'pid' => '12',
      'title' => 'Handlingen foregår i:',
      'sorting' => 'default',
      'weight' => '-4',
    ),
    7 => array(
      'name' => 'facet.language',
      'pid' => '12',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-3',
    ),
    8 => array(
      'name' => 'facet.category',
      'pid' => '12',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-2',
    ),
    9 => array(
      'name' => 'facet.date',
      'pid' => '12',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-1',
    ),
  );
  $export['lydboeger'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'noder';
  $profile->title = 'Noder';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'ma=mu',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '10',
      'term_count' => '5',
    ),
  );
  $profile->weight = 9;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.creator',
      'pid' => '16',
      'title' => 'Kunstner/komponist',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.subject',
      'pid' => '16',
      'title' => 'Emne',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.sheetMusic',
      'pid' => '16',
      'title' => 'Nodetype',
      'sorting' => 'default',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.type',
      'pid' => '16',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.language',
      'pid' => '16',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.date',
      'pid' => '16',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.category',
      'pid' => '16',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-4',
    ),
  );
  $export['noder'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'spil';
  $profile->title = 'Spil';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'ma=bg or term.type=spil',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '10',
      'term_count' => '10',
    ),
  );
  $profile->weight = 10;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.category',
      'pid' => '17',
      'title' => 'Målgruppe',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.gamePlatform',
      'pid' => '17',
      'title' => 'Platform',
      'sorting' => 'alphabetical',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.subject',
      'pid' => '17',
      'title' => 'Emne',
      'sorting' => 'alphabetical',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.date',
      'pid' => '17',
      'title' => 'Årstal',
      'sorting' => 'default',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.language',
      'pid' => '17',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.creator',
      'pid' => '17',
      'title' => 'Firma',
      'sorting' => 'default',
      'weight' => '-5',
    ),
  );
  $export['spil'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'tegneserier';
  $profile->title = 'Tegneserier';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.type=tegneserie or term.type="graphic novel"',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_descending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 0,
      'number_of_facets' => 25,
      'facet_count' => 5,
      'term_count' => 5,
    ),
  );
  $profile->weight = 11;
  $profile->facets = array();
  $export['tegneserier'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'tidsskrifter';
  $profile->title = 'Tidsskrifter';
  $profile->config = array(
    'search_request' => array(
      'agency' => '',
      'well_profile' => '',
      'query' => 'term.acsource any "pressreader zinio" or (term.acsource=bibliotekskatalog and ma=pe not ma=åp not ma=ms not ma=av not term.type=bog not term.type=spil not term.type=tegneserie not ma=tb not serie)',
      'new_materials' => '',
      'allow_empty' => 0,
    ),
    'user_interaction' => array(
      'exposed' => 1,
      'sticky' => 1,
      'alter_links' => 1,
    ),
    'search_result' => array(
      'results_per_page' => '10',
      'default_sort' => 'date_ascending',
      'ranking' => 'rank_frequency',
    ),
    'facets' => array(
      'use_facets' => 1,
      'number_of_facets' => '25',
      'facet_count' => '10',
      'term_count' => '25',
    ),
  );
  $profile->weight = 2;
  $profile->facets = array(
    0 => array(
      'name' => 'facet.acSource',
      'pid' => '9',
      'title' => 'Kilde',
      'sorting' => 'default',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.type',
      'pid' => '9',
      'title' => 'Materialetype',
      'sorting' => 'default',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.language',
      'pid' => '9',
      'title' => 'Sprog',
      'sorting' => 'default',
      'weight' => '-8',
    ),
  );
  $export['tidsskrifter'] = $profile;

  return $export;
}
