<?php
/**
 * @file
 * Represents callbacks for custom pages.
 */

/**
 * Wrapper for calling quiz_quiztake function.
 *
 * @param string $quiz_id
 *   Id on quiz node.
 * @param string $number
 *   Number of question.
 *
 * @return string
 *   Output of quiz_quiztake function.
 */
function ding_christmas_calendar_take_wrapper($quiz_id, $number) {
  $quiz = node_load($quiz_id);
  $_SESSION['quiz'][$quiz->nid]['current'] = $number;
  $quiz_result = quiz_take_quiz($quiz);
  if (!$quiz_result) {
    $quiz_result = entity_create('quiz_result', array(
      'nid' => $quiz->nid,
      'vid' => $quiz->vid,
      'uid' => $GLOBALS['user']->uid,
      'type' => $quiz->quiz->result_type,
    ));

    $quiz_result->save();
    $_SESSION['quiz'][$quiz_result->nid]['result_id'] = empty($quiz_result->result_id) ? 1 : $quiz_result->result_id;
    $_SESSION['quiz'][$quiz_result->nid]['current'] = 1;
    quiz_take_quiz($quiz);
  }


  module_load_include('inc', 'quiz', 'plugins/page_manager/tasks/quiztake');
  $output = quiz_take_question($quiz, $number);
  return $output;
}

/**
 * Form handler for showing login for in popup.
 *
 * @param bool $ajax
 *
 * @return mixed
 */
function ding_christmas_login_popup($ajax) {
  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Login form')
  );
  $form = 'user_login';
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $commands = ctools_modal_form_wrapper($form, $form_state);

    if ($form_state['executed']) {
      $commands = array();
      $commands[] = ctools_modal_command_dismiss();
      $commands[] = ctools_ajax_command_redirect('ding-christmas-calendar');
    }
    print ajax_render($commands);
    drupal_exit();
  }
  else {
    return drupal_get_form($form);
  }
}
