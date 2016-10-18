<?php
/**
 * @file
 * Represents configuratuin forms and logic.
 */

/**
 * Form handler for settings form of calendar.
 */
function ding_christmas_calendar_settings_form($form, $form_state) {
  $id = variable_get('ding_christmas_calendar_quiz_id');

  $quiz = node_load($id);
  if ($quiz) {
    $form['view'] = array(
      '#prefix' => '<strong>',
      '#suffix' => '</strong>',
      '#markup' => t('For !ph1 or !ph2 Christmas calendar page', array(
        '!ph1' => l(t('viewing'), 'ding-christmas-calendar'),
        '!ph2' => l(t('editing'), "node/{$id}/edit"),
      )),
    );

    $questions = ding_christmas_calendar_questions($quiz->nid, $quiz->vid, 'multichoice');
    if (count($questions) > 0) {
      $form['questions'] = array(
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#title' => t('Questions'),
      );

      $rows = array();
      foreach ($questions as $question) {
        $rows[] = array(
          'title' => $question->title,
          'url' => l(t('Edit'), "node/{$question->nid}/edit"),
        );
      }
      $form['questions']['table'] = array(
        '#rows' => $rows,
        '#header' => array(
          t('Title'),
          t('Operations'),
        ),
        '#theme' => 'table',
        '#sticky' => TRUE,
        '#weight' => 0,
      );

      $form['questions']['pager']['#theme'] = 'pager';

      $form['questions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete questions'),
        '#prefix' => '<p>' . t('At this moment already exists questions for christmas calendar. Calendar can purged by pressing this button.') . '</p>',
        '#submit' => array('ding_christmas_calendar_settings_form_remove_submit'),
        '#quiz' => $quiz,
        '#limit_validation_errors' => array(),
        '#weight' => 1,
      );
    }
    else {

      $form['dates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Dates:'),
        '#tree' => TRUE,
      );
      $date = new DateTime();
      $form['dates']['start'] = array(
        '#type' => 'date_popup',
        '#title' => t('Start date of Christmas calendar'),
        '#date_format' => 'd/m/Y',
        '#default_value' => $date->format('Y-m-d H:i:s'),
        '#weight' => 1,
      );

      $form['dates']['duration'] = array(
        '#type' => 'textfield',
        '#title' => t('Duration in days'),
        '#default_value' => variable_get('ding_christmas_calendar_duration', 24),
        '#weight' => 2,
        '#element_validate' => array('element_validate_integer_positive'),
      );

      $form['dates']['generate'] = array(
        '#type' => 'submit',
        '#prefix' => '<p>' . t('On pressing this button will be generated questions for XMas, starting from date which is defined above.') . '</p>',
        '#value' => t('Generate'),
        '#weight' => 3,
        '#name' => 'generate',
        '#validate' => array('ding_christmas_calendar_settings_form_validate'),
        '#submit' => array('ding_christmas_calendar_settings_generate_form_submit'),
      );
    }

    $form['quiz'] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#title' => t('Quiz:'),
    );

    $background = field_get_items('node', $quiz, 'field_background');
    $form['quiz']['background'] = array(
      '#type' => 'managed_file',
      '#title' => t('Background image'),
      '#description' => t('Background image for Christmas calendar.'),
      '#default_value' => isset($background[0]['fid']) ? $background[0]['fid'] : NULL,
    );

    $form['quiz']['save'] = array(
      '#type' => 'submit',
      '#prefix' => '<p>' . t('Allow to add background image for Xmas calendar.') . '</p>',
      '#value' => t('Save quiz settings'),
      '#name' => 'quiz_save',
      '#submit' => array('ding_christmas_calendar_settings_form_quiz_submit'),
      '#validate' => array('ding_christmas_calendar_settings_form_validate'),
    );

    $form['object'] = array(
      '#type' => 'value',
      '#value' => $quiz,
    );
  }
  else {
    $form['error'] = array(
      '#markup' => '<p>' . t('Something happened. Variable `ding_christmas_calendar_quiz_id` is empty. Reinstall module or create a quiz and initialize variable with actual value') . '</p>',
    );
  }
  return $form;
}

/**
 * Validate handler for calendar settings form.
 */
function ding_christmas_calendar_settings_form_validate($form, $form_state) {
  $values = $form_state['values'];
  $element = $form_state['triggering_element'];

  switch ($element['#name']) {
    case 'generate':
      list($start, $duration) = array_values($values['dates']);

      if (empty($start)) {
        form_set_error('dates][start', t('Please enter valid date.'));
      }

      if (empty($duration)) {
        form_set_error('dates][duration', t('Please enter valid duration.'));
      }
      break;

    case 'quiz_save':
      if (empty($values['background'])) {
        form_set_error('background', t('Please provide image.'));
      }
      break;
  }
}

/**
 * Submit handler for generating questions for calendar.
 */
function ding_christmas_calendar_settings_form_quiz_submit($form, $form_state) {
  $values = $form_state['values'];
  $quiz = $values['object'];
  $fid = $values['background'];
  if ($fid) {
    try {
      $file = file_load($fid);
      file_move($file, 'public://' . $file->filename);
      $file->display = 1;
      $quiz->field_background[LANGUAGE_NONE][0] = (array) $file;
      node_save($quiz);
      drupal_set_message(t('Image was successfully saved.'));
    }
    catch (Exception $ex) {
      watchdog_exception('ding_christmas_calendar', $ex);
      drupal_set_message(t('Error occurred. Check log for details.'), 'error');
    }
  }
}

/**
 * Submit handler for generating questions for calendar.
 */
function ding_christmas_calendar_settings_generate_form_submit($form, $form_state) {
  $values = $form_state['values'];
  unset($_SESSION['quiz']);
  list($start, $duration) = array_values($values['dates']);
  $quiz = $values['object'];
  quiz_delete($quiz);
  node_save($quiz);
  module_load_include('inc', 'multichoice', 'multichoice.classes');
  try {
    $current = DateTime::createFromFormat('Y-m-d', $start);
    $current->setTime(0, 0);
    $step = new DateInterval('P1D');
    $weight = 0;
    for ($i = 0; $i < $duration; $i++) {
      $current = !$i ? $current : $current->add($step);

      $page = _ding_christmas_calendar_page_stub();
      $page->title = $current->format('d F');
      $page->quiz_nid = $quiz->nid;
      $page->quiz_vid = $quiz->vid;
      node_save($page);
      $page_qnr_id = ding_christmas_get_question_id($page);

      $question = _ding_christmas_calendar_question_stub();
      $question->title = $current->format('d F');
      $question->field_quiz_date[LANGUAGE_NONE][0]['value'] = $current->getTimestamp();
      $question->quiz_nid = $quiz->nid;
      $question->quiz_vid = $quiz->vid;
      node_save($question);
      $question_qnr_id = ding_christmas_get_question_id($question);

      $data = new stdClass();
      $data->child_nid = $page->nid;
      $data->child_vid = $page->vid;
      $data->question_status = 1;
      $data->weight = $weight++;
      $data->max_score = 0;
      $data->auto_update_max_score = 0;
      $data->qnr_pid = NULL;
      $data->qnr_id = $page_qnr_id;
      $questions[] = $data;

      $data = new stdClass();
      $data->child_nid = $question->nid;
      $data->child_vid = $question->vid;
      $data->question_status = 1;
      $data->weight = $weight++;
      $data->max_score = 1;
      $data->auto_update_max_score = 0;
      $data->qnr_pid = $page_qnr_id;
      $data->qnr_id = $question_qnr_id;
      $questions[] = $data;
    }
    quiz_set_questions($quiz, $questions);
  }
  catch (Exception $ex) {
    watchdog_exception('ding_christmas_calendar', $ex);
    drupal_set_message(t('Error occurred. Check log for details.'), 'error');
  }
}

/**
 * Submit handler for removing questions.
 */
function ding_christmas_calendar_settings_form_remove_submit($form, $form_state) {
  $element = $form_state['triggering_element'];
  $quiz = $element['#quiz'];
  try {
    quiz_delete($quiz);
    $questions = ding_christmas_calendar_questions($quiz->nid, $quiz->vid);
    foreach ($questions as $question) {
      node_delete($question->nid);
    }
    unset($_SESSION['quiz']);
    drupal_set_message(t('Calendar was successfully cleared'));
  }
  catch (Exception $ex) {
    watchdog_exception('ding_christmas_calendar', $ex);
    drupal_set_message(t('Something goes wrong. Check reports.'), 'error');
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Support function for getting stub of question.
 *
 * @return object
 *   Stub of question object.
 */
function _ding_christmas_calendar_question_stub() {
  $question = new stdClass();
  $question->uid = '1';
  $question->title = "";
  $question->status = '1';
  $question->comment = '2';
  $question->promote = '0';
  $question->sticky = '0';
  $question->type = 'multichoice';
  $question->language = 'en';
  $question->is_quiz_question = TRUE;
  $question->choice_multi = '0';
  $question->choice_random = '1';
  $question->choice_boolean = '0';
  $question->alternatives = array();
  $question->name = 'admin';
  $question->menu = NULL;
  $question->state = 0;
  $question->weight = 0;
  $question->max_score = 1;
  $question->auto_update_max_score = 1;
  $question->refresh = 1;
  $question->alternatives = array(
    array(
      'id' => '1',
      'answer' => array(
        'value' => '<p>Answer stub1</p>',
        'format' => 'ding_wysiwyg',
      ),
      'feedback_if_chosen' => array(
        'value' => '',
        'format' => 'ding_wysiwyg',
      ),
      'feedback_if_not_chosen' => array(
        'value' => '',
        'format' => 'ding_wysiwyg',
      ),
      'score_if_chosen' => '1',
      'score_if_not_chosen' => '0',
      'weight' => '0',
    ),
    array(
      'id' => '2',
      'answer' => array(
        'value' => '<p>Answer stub2</p>',
        'format' => 'ding_wysiwyg',
      ),
      'feedback_if_chosen' => array(
        'value' => '',
        'format' => 'ding_wysiwyg',
      ),
      'feedback_if_not_chosen' => array(
        'value' => '',
        'format' => 'ding_wysiwyg',
      ),
      'score_if_chosen' => '0',
      'score_if_not_chosen' => '0',
      'weight' => '0',
    ),
  );

  $question->body[LANGUAGE_NONE][] = array(
    'value' => '<p>Question stub</p>',
    'format' => 'ding_wysiwyg',
  );

  return $question;
}

/**
 * Support function for getting stub of question.
 *
 * @return object
 *   Stub of question object.
 */
function _ding_christmas_calendar_page_stub() {
  $page = new stdClass();
  $page->uid = '1';
  $page->title = "";
  $page->status = '1';
  $page->comment = '2';
  $page->promote = '0';
  $page->sticky = '0';
  $page->type = 'quiz_page';
  $page->language = 'en';
  $page->is_quiz_question = TRUE;
  $page->alternatives = array();
  $page->name = 'admin';
  $page->menu = NULL;
  $page->state = 0;
  $page->weight = 0;
  $page->max_score = 1;
  $page->auto_update_max_score = 1;
  $page->refresh = 1;

  return $page;
}
