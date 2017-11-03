<?php
/**
 * Created by PhpStorm.
 * User: caf
 * Date: 11/3/17
 * Time: 3:29 PM
 */

class Stack
{

  private $stack;


  public function get($pop = false)
  {
    if (count($this->stack) == 0) {
      return -1;
    }
    if ($pop) {
      return $this->pop();
    } else {
      return $this->stack[count($this->stack) - 1];
    }
  }

  public function pop() {
    if (count($this->stack) == 0) {
      return -1;
    }
    $result = $this->stack[count($this->stack)-1];
    array_splice($this->stack, count($this->stack)-1, 1);

    return $result;
  }

  public function set($value) {
    if (!is_numeric($value)) {
      $value = -1;
    }
    $this->stack[] = $value;
  }


}