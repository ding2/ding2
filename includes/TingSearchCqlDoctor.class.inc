<?php

/**
 * @file
 * Class TingSearchCqlDoctor
 * An attempt to convert non cql search phrases to valid cql.
 *
 * examples not valid:
 * portland (film) => portland and (film)
 * henning mortensen (f. 1939) => henning and mortensen and "(f. 1939)"
 * harry and (White night) = harry and "(White night)"
 *
 *
 * valid cql stays the same eg.
 * dkcclterm.sf=v and dkcclterm.uu=nt and (term.type=bog) not term.literaryForm=fiktion
 */

class TingSearchCqlDoctor {

  private $cql_string;
  private $pattern;
  private $replace;
  private static $replace_key = 10;

  /**
   * constructor,
   * @param $string
   * sets private member $cql_string with trimmed string
   */
  public function __construct($string) {
    $this->cql_string = trim($string);
    // handle reserved characters
    $this->escape_reserved_characters();
    // remove multiple whitespaces
    $this->cql_string = preg_replace('/\s+/', ' ', $this->cql_string);
  }

  /**
   * Method to convert a string to strict cql (Basically by adding quotes when needed)
   * @param string $string
   *   The search query
   * @return string
   *   cql compatible string
   */
  public function string_to_cql() {
    // hendle parantheses
    $this->fix_paranthesis();
    // handle qoutes
    $this->fix_qoutes();
    // format the string
    $return = $this->format_cql_string();
    dpm($return);
    return $return;
  }

  /**
   * Format cql string.
   * @return string; if string is not valid cql it is and'ed
   */
  private function format_cql_string(){
    // last check. All parts of cql string must be valid
    $valid = TRUE;
    $parts = preg_split($this->get_cql_operators_regexp(), $this->cql_string);
    foreach($parts as $part){
      if(!$this->string_is_cql($part)){
        $valid = FALSE;
        break;
      }
    }

    // Explode string by whitespace.
    $expressions = explode(' ', $this->cql_string);
    // replace keys with phrases
    if(!empty($this->pattern)){
      $expressions = preg_replace($this->pattern, $this->replace, $expressions);
    }

    if($valid){
      // implode by blank
      return implode(' ', $expressions);
    }

    //string is not valid; implode by and
    return implode(' and ', $expressions);
  }

  /**
   * For now enqoute forward slashes and '-'
   * @return nothing; alters private member cql_string
   */
  private function escape_reserved_characters() {
    //$this->cql_string = str_replace('/', ' "/" ', $this->cql_string);
    //$this->cql_string = str_replace('-', ' "-" ', $this->cql_string);
  }

  private function get_replace_key(){
    $key_prefix = 'zxcv';
    return $key_prefix. self::$replace_key++;
  }

  /**
   * Look for parantheses in string. If any found and content is not
   * strict cql; enqoute the lot
   * @param $string
   * @return nothing; alters private member cql_string
   *
   */
  private function fix_paranthesis() {
    $valid_cql = TRUE;
    //grab content in paranthesis
    preg_match_all('$\(([^\(\)]*)\)$', $this->cql_string, $phrases);

    if (empty($phrases[1])) {
      // no matching paranthesis
      return;
    }
    foreach ($phrases[1] as $phrase) {
      if (!$this->string_is_cql($phrase)) {
        $valid_cql = FALSE;
        break;
      }
    }
    if ($valid_cql) {
      foreach ($phrases[0] as $phrase) {
        $this->set_replace_pattern($phrase);
      }
    }
    else {
      // one or more of the parenthesis holds invalid cql; quote the lot
      foreach ($phrases[0] as $phrase) {
        $this->set_replace_pattern($phrase, TRUE);
      }
    }
  }

  /**
   * grab content between qoutes
   */
  private function fix_qoutes() {
    preg_match_all('$["|\)]([^"]*)["\)]$', $this->cql_string, $phrases);
    if (!empty($phrases[0])) {
      foreach ($phrases[0] as $phrase) {
        $this->set_replace_pattern($phrase);
      }
    }
  }

  /**
   * helper function to set a single replacement key and phrase
   * @param $phrase
   * @return nothing; alters private member cql_string
   */
  private function set_replace_pattern($phrase, $qoute_me = FALSE){
    if($qoute_me) {
      $this->replace[] = '"'.$phrase.'"';
    }
    else{
      $this->replace[] = $phrase;
    }
    // generate a replacement key. We need the key to maintain order of phrases and strings in search string
    // replace phrases in search string with the replacement key
    $replace_key = $this->get_replace_key();
    $this->pattern[] = '/' . $replace_key . '/';
    $this->cql_string = str_replace($phrase, $replace_key, $this->cql_string);
  }


  /**
   * Tests if a string is cql
   * @param string $string
   *   The search query
   * @return bool|int
   *   Whether the string is valid cql(TRUE) or not(FALSE)
   */
  private function string_is_cql($string){
    // single word is valid (no whitespaces)
    if(strpos($string, ' ') === FALSE){
      return TRUE;
    }
    return preg_match($this->get_cql_operators_regexp(), $string);
  }

  /**
   * Get reqular expression to ideniify cql operators
   * @return string
   */
  private function get_cql_operators_regexp(){
   return '@ and | or | not |=|\(|\)@';
  }
}
