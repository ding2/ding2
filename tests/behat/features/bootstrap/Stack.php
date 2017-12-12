<?php

/**
 * @file
 * Implements a simple LIFO stack
 */

/**
 * Class Stack
 */
class Stack {

  /**
   * This is the stack variable
   *
   * @var $stack
   */
  private $stack;

  /**
   * Get the top of the stack, optionally clearing (popping) it
   *
   * @param bool $pop
   *   input is true if the value is popped, otherwise it will remain on stack
   * @return int
   *   this is the value returned from the stack
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
   *   This is the value from the stack which is returned
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
   * @param int $value
   *   This is the value being pushed onto the stack
   */
  public function set($value) {
    if (!is_numeric($value)) {
      $value = -1;
    }
    $this->stack[] = $value;
  }
}
