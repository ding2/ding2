<?php

/**
 * @file
 * Implements a simple LIFO stack
 */

class Stack {

  /**
   * @var $stack
   */
  private $stack;

  /**
   * Get the top of the stack, optionally clearing (popping) it
   *
   * @param bool $pop
   * @return int
   */
  public function get($pop = false) {
    if (count($this->stack) == 0) {
      return -1;
    }
    if ($pop) {
      return $this->pop();
    }
    else {
      return $this->stack[count($this->stack) - 1];
    }
  }

  /**
   * Pop and return the top of the stack
   *
   * @return int
   */
  public function pop() {
    if (count($this->stack) == 0) {
      return -1;
    }
    $result = $this->stack[count($this->stack) - 1];
    array_splice($this->stack, count($this->stack) - 1, 1);

    return $result;
  }

  /**
   * Insert a new value on the stack
   *
   * @param $value
   */
  public function set($value) {
    if (!is_numeric($value)) {
      $value = -1;
    }
    $this->stack[] = $value;
  }
}
