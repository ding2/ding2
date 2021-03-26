<?php

/**
 * @file
 * Represents definition of custon view handler.
 */

/**
 * Custom view handler for generation answer for CSV file.
 */
class ding_christmas_calendar_views_handler_field_quiz_question_result_answer extends quiz_views_handler_field_quiz_question_result_answer {

  /**
   * Preprocess method which is called before render.
   *
   * @param $values
   */
  public function pre_render(&$values) {
    $this->items = array();
    $result_ids = array();
    foreach ($values as $value) {
      $result_ids[] = $value->result_id;
    }

    $nid = $this->options['question_nid'];
    $vid = $this->options['question_vid'];
    $this->items = array();
    if ($result_ids) {
      $raids = db_query('SELECT result_answer_id
        FROM {quiz_node_results_answers} qnra
        LEFT JOIN {quiz_node_results} qnr ON (qnra.result_id = qnr.result_id)
        WHERE question_nid = :nid
          AND question_vid = :vid
          AND qnr.result_id IN (:result_id)',
        array(
          ':nid' => $nid,
          ':vid' => $vid,
          ':result_id' => $result_ids,
        ))->fetchCol();

      $sql = "SELECT * FROM {quiz_node_results_answers} qnra
        INNER JOIN {quiz_multichoice_user_answers} qmua on (qnra.result_answer_id = qmua.result_answer_id)
        INNER JOIN {quiz_multichoice_user_answer_multi} uam ON (uam.user_answer_id = qmua.id)
        INNER JOIN {quiz_multichoice_answers} ma ON (ma.id = uam.answer_id)
        WHERE qnra.result_answer_id IN (:result_answer_id)";
      if (!empty($raids)) {
        $result = db_query($sql, array(':result_answer_id' => $raids));

        foreach ($result as $item) {
          $status = $item->is_correct ? t('correct') : t('wrong');
          $this->items[$item->result_id][] = array('answer' => "{$item->answer}({$status})");
        }
      }
    }
  }

}
