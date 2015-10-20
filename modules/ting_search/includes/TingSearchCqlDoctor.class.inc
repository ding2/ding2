<?php

/**
 * @file
 *
 * File holds class to convert not valid searchphrases to valid cql.
 * Private membet cql_string holds an internal reprensation of the original search string. All parts of the string
 * is examined to check for healthy cql.
 *
 * Enqouted parts of the string stays the same. Parantheses are enqouted if content is not healthy. Blanks are
 * replaced by 'and'. Mulitple whitespaces are removed. Reserved characters are enqouted.
 *
 * Examples not valid:
 * portland (film) => portland and (film)
 * henning mortensen (f. 1939) => henning and mortensen and "(f. 1939)"
 * harry and (White night) = harry and "(White night)"
 *
 *
 * Valid cql stays the same eg.
 * dkcclterm.sf=v and dkcclterm.uu=nt and (term.type=bog) not term.literaryForm=fiktion
 */

/**
 * Class TingSearchCqlDoctor.
 *
 * An attempt to convert non cql search phrases to valid cql.
 */
class TingSearchCqlDoctor {

  /**
   * @var string cql_string.
   *   Internael representation of the searchphtrase.
   */
  private $cql_string;
  /**
   * @var array pattern.
   *   The pattern to replace in searchstring.
   */
  private $pattern = array();
  /**
   * @var array replace.
   *   The string to replace with.
   */
  private $replace=array();
  /**
   * @var int replace_key.
   *   Used to prepend key - @see $this->get_replace_key().
   */
  private static $replace_key = 10;

  /**
   * Constructor,Escape reserved characters, remove multiple whitespaces
   * and sets private member $cql_string with trimmed string.
   *
   * @param string $string
   *   The search phrase to cure.
   */
  public function __construct($string) {
    $this->cql_string = trim($string);
    // Remove multiple whitespaces.
    $this->cql_string = preg_replace('/\s+/', ' ', $this->cql_string);
  }

  /**
   * Method to convert a string to strict cql.
   *
   * Basically this method adds quotes when needed.
   *
   * @param string $string
   *   The search query.
   * @return string
   *   Cql compatible string.
   */
  public function string_to_cql() {

    // Handle qoutes.
    $this->fix_qoutes();
    // Hendle parantheses.
    $this->fix_paranthesis();
    // Handle reserved characters.
    $this->escape_reserved_characters();
    // Format the string.
    return $this->format_cql_string();
  }

  /**
   * Format cql string.
   *
   * Use private members $pattern and $replace to replace not valid cql phrases with valid.
   *
   * @return string
   *   string in valid cql (hopefully)
   *
   */
  private function format_cql_string() {
    // Last check. All parts of cql string must be valid.
    $valid = TRUE;
    $parts = preg_split($this->get_cql_operators_regexp(), $this->cql_string);
    foreach ($parts as $part) {
      if (!$this->string_is_cql($part)) {
        $valid = FALSE;
        break;
      }
    }
    // Explode string by whitespace.
    $expressions = explode(' ', $this->cql_string);

    // Replace keys with phrases,
    if (!empty($this->pattern)) {
      $expressions = preg_replace($this->pattern, $this->replace, $expressions);
    }

    $done = FALSE;
    do {
      $expressions = $this->replace_inline($expressions, $done);
    }
    while(!$done);

    // Remove empty elements.
    $empty_slots = array_keys($expressions,'');
    foreach($empty_slots as $slot){
      unset($expressions[$slot]);
    }

    if ($valid) {
      // Implode by blank.
      return implode(' ', $expressions);
    }

    // String is not valid; implode by and.
    return implode(' and ', $expressions);
  }


  /**
   * Some replacements are nested in paranthesis and/or qoutes
   * eg. (hund and "("hest")") which is perfectly legal.
   * Cql doctor first handles the qoutes and then the
   * paranthesis ; thus (hund and "("hest")")  becomes encoded multiple times.
   * This method runs through all parts to fix it
   *
   * @param array $expressions;
   *  The parts of the searchquery to be cured.
   * @param $done;
   *  Flag indicating whether all parts has been handled.
   * @return array;
   *  Decoded expressions.
   */
  private function replace_inline($expressions, &$done) {
    foreach ($expressions as $key_exp => $expression) {
      foreach ($this->pattern as $key_pat => $regexp) {
        if (preg_match($regexp, $expression)) {
          $expressions[$key_exp] = preg_replace($regexp, $this->replace[$key_pat], $expression);
          return $expressions;
        }
      }
    }
    $done = TRUE;
    return $expressions;
  }


  /**
   * Enqoute forward slashes and '-'.
   *
   * @return nothing
   *   Alters private member cql_string.
   */
  private function escape_reserved_characters() {
    $this->cql_string = str_replace('/', ' "/" ', $this->cql_string);
  }

  /**
   * Get a key for replacement in string.
   *
   * @return string
   */
  private function get_replace_key() {
    $key_prefix = 'zxcv';
    return $key_prefix . self::$replace_key++;
  }

  /**
   * Handle parantheses.
   *
   * Look lace parantheses in string. If any found and content is not
   * strict cql; enqoute the lot.
   *
   * @return nothing.
   *   Alters private member cql_string.
   *
   */
  private function fix_paranthesis() {
    //Grab content in paranthesis.
    preg_match_all('$\(([^\(\)]*)\)$', $this->cql_string, $phrases);

    if (empty($phrases[1])) {
      // No matching paranthesis.
      return;
    }

    foreach ($phrases[1] as $key => $phrase) {
      if (!$this->string_is_cql($phrase)) {
        $this->set_replace_pattern($phrases[0][$key], TRUE);
      }
      else{
        $this->set_replace_pattern($phrase);
      }
    }
  }

  /**
   * Handle qoutes.
   *
   * Look for qouted content. Qouted content is replaced in searchstring.
   */
  private function fix_qoutes() {
    // Greab qouted content.
    preg_match_all('$"([^"]*)"$', $this->cql_string, $phrases);
;
    if (!empty($phrases[0])) {
      foreach ($phrases[0] as $phrase) {
        $this->set_replace_pattern($phrase);
      }
    }
  }

  /**
   * Helper function to set a single replacement key and phrase.
   *
   * Adds given phrase to private member $replace. Retrieve a key for the replacement and replace given phrase in
   * internal representation of search string with the key.
   *
   * @param string $phrase.
   *   The phrase to add to private member $replace.
   * @param bool $qoute_me.
   *   If TRUE phrase is enqouted.
   * @return nothing
   *   Alters private member cql_string
   */
  private function set_replace_pattern($phrase, $qoute_me = FALSE) {
    if ($qoute_me) {
      $this->replace[] = '"' . $phrase . '"';
    }
    else {
      $this->replace[] = $phrase;
    }
    $replace_key = $this->get_replace_key();
    $this->pattern[] = '/' . $replace_key . '/';

    $this->cql_string = str_replace($phrase, $replace_key, $this->cql_string);
  }


  /**
   * Tests if a string is cql.
   *
   * If string contains a cql operator it is assumed that an attempt to write cql is done.
   *
   * @param string $string
   *   The search query
   * @return bool|int
   *   Whether the string is valid cql(TRUE) or not(FALSE)
   */
  private function string_is_cql($string) {
    // Single word is valid (no whitespaces).
    if (strpos(trim($string), ' ') === FALSE) {
      return TRUE;
    }
    return preg_match($this->get_cql_operators_regexp(), $string);
  }

  /**
   * Get reqular expression to ideniify cql operators.
   *
   * @return string.
   *   Reqular expression to identify cql operators.
   */
  private function get_cql_operators_regexp() {
    return '@ and | any | all | adj | or | not |=|\(|\)@i';
  }
}
