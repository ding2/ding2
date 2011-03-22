<?php

/**
 * @brief Implementation of hook_menu()
 *
 * Felter: Forfatter, titel, emneord,
 */
function searchextendform_admin_settings() {
  $form['searchextendform_creator_index'] = 
    array('#type' => 'textfield',
	  '#title' => t('Forfatter'),
	  '#description' => t('Angiv navn på det register, som indeholder forfatternavn. F.eks. dc.creator'),
	  '#default_value' => variable_get('searchextendform_creator_index', 'dc.creator')
	  );
	  
  $form['searchextendform_title_index'] = 
    array('#type' => 'textfield',
	  '#title' => t('Titel'),
	  '#description' => t('Angiv navn på det register, som indeholder titler. F.eks. dc.title'),
	  '#default_value' => variable_get('searchextendform_title_index', 'dc.title')
	  );

  $form['searchextendform_subject_index'] = 
    array('#type' => 'textfield',
	  '#title' => t('Emneord'),
	  '#description' => t('Angiv navn på det register, som indeholder emneord. F.eks. dc.subject'),
	  '#default_value' => variable_get('searchextendform_subject_index', 'dc.subject')
	  );

  $form['#submit'][] = 'searchextendform_admin_settings_submit';
  return system_settings_form($form);
}

function searchextendform_admin_settings_validate($form, &$form_state) {
  dpm($form); 
  dpm($form_state);

  $s = '';
  if(isset($form_state['values']['searchextendform_creator_index'])) {
    $s = $form_state['values']['searchextendform_creator_index'];
  }
  
  if($s == '') {
    form_set_error('searchextendform_creator_index', t('Et register skal angives.'));
  }
}

function searchextendform_admin_settings_submit($form, $form_state) {
  variable_set('searchextendform_creator_index', $form['values']['searchextendform_creator_index']);
}
