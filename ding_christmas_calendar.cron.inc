<?php
/**
 * @file
 * Represents cron hooks declarations.
 */

// Cron interval set to 1 day.
define('DING_CHRISTMAS_CRON_INTERVAL', 1);

/**
 * Implements hook_cron_queue_info().
 */
function ding_christmas_calendar_cron_queue_info() {
  $queue['ding_christmas_calendar_queue'] = array(
    'worker callback' => '_ding_christmas_calendar_queue_worker',
  );
  return $queue;
}

/**
 * Implements hook_cron().
 */
function ding_christmas_calendar_cron() {
  $ding_christmas_calendar_last_cron = variable_get('ding_christmas_calendar_cron', 0);
  if ((REQUEST_TIME - $ding_christmas_calendar_last_cron) > DING_CHRISTMAS_CRON_INTERVAL) {
    variable_set('ding_christmas_calendar_last_cron', REQUEST_TIME);
    $id = variable_get('ding_christmas_calendar_quiz_id');
    $quiz_result = quiz_result_load($id);
    $quiz = node_load($quiz_result->nid, $quiz_result->vid);

    $questions = ding_christmas_calendar_questions($quiz->nid, $quiz->vid, 'quiz_page');
    if (!empty($questions)) {
      $queue = DrupalQueue::get('ding_christmas_calendar_queue');
      foreach ($questions as $node) {
        if ($node->publish_on == NULL && $node->unpublish_on == NULL) {
          $item = new stdClass();
          $item->nid = $node->nid;
          $item->vid = $node->vid;
          $queue->createItem($item);
        }
      }
    }
  }
}

/**
 * Worker callback.
 *
 * @see ding_christmas_calendar_cron_queue_info()
 */
function _ding_christmas_calendar_queue_worker($item) {
variable_set('ding_christmas_calendar_last_cron', REQUEST_TIME);
  $id = variable_get('ding_christmas_calendar_quiz_id');
  $quiz_result = quiz_result_load($id);
  $questions = $quiz_result->getLayout();
  // Find the correct revision.
  $question = NULL;
  foreach ($questions as $question_array) {
    if ($question_array['nid'] == $item->nid) {
      $question = node_load($question_array['nid'], $question_array['vid']);
      break;
    }
  }
  if (!empty($question)) {
    $qra = quiz_result_answer_load($quiz_result->result_id, $question->nid, $question->vid);
    if (!empty($qra)) {
      $qra->result_id = $quiz_result->result_id;
      $qra->question_nid = $item->nid;
      $qra->question_vid = $item->vid;
      $qra->is_skipped = 1;
      $qra->is_correct = 0;
      $qra->points_awarded = 0;
      $qra->answer_timestamp = REQUEST_TIME;
      entity_save('quiz_result_answer', $qra);
    }
  }
}
