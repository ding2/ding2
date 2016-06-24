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
  module_load_include('inc', 'quiz', 'plugins/page_manager/tasks/quiztake');
  $output = quiz_quiztake($quiz);
  return $output;
}
