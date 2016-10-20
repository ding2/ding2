<?php
/**
 * @file
 * Code for the Alma mockup feature.
 */

/**
 * Class AlmaMockup
 */
class AlmaMockup {

  protected $path;
  protected $params;
  protected $drupal_path;
  protected $request_data;

  public function __construct($path, $params, $drupal_path) {
    $this->path = $path;
    $this->params = $params;
    $this->drupal_path = $drupal_path;
    $this->request_data = NULL;
  }
  
  public function get() {
	$this->log('Get file: ' . $this->filename());
	$filename = $this->filename();
	if (file_exists($filename)) {
		$handle = fopen($filename, "r");
		$contents = fread($handle, filesize($filename));
		fclose($handle);
		print_r($contents);
	}
	else {
		throw new AlmaMockupException("Undefined method: " . request_uri());
    }
  }

  public function pass_through($url, $ssl_version) {
	$url .= '/' . implode('/', $this->path);
	$url = url($url, array('query' => $this->params));
    $request = drupal_http_request($url, array('secure_socket_transport' => $ssl_version));
	$this->request_data = $request->data;
	$this->log($url);
	$this->log($request->data);
	print_r($this->request_data);
  }

  public function record() {
	$this->log('Record file: ' . $this->filename());
	$filename = $this->filename();
	if (empty($this->request_data)) {
		$this->log('Failed to save mockup:' . $filename . " is empty");
		throw new AlmaMockupException("Failed to save record: " . $filename);
	}
	if ($f = fopen($filename, 'x')) {
	  fwrite($f, $this->request_data . "\n");
	  fclose($f);
	} else {
	  $this->log('Failed to save mockup:' . $filename . " is not writeable");
	  throw new AlmaMockupException("Failed to save record: " . $filename);
	}
  }

  private function filename() {
	$params = array_map(function($val) { return urlencode($val); }, $this->params);
	$filename = $this->drupal_path . '/' . implode('/', $this->path) . '/' .  implode('.', $params) . '.xml';
	if (empty($this->params)) {
	  $filename = $this->drupal_path . '/' . implode('/', $this->path) . '.xml';
	}
	return $filename;
  }

  private function log($text) {
	$f = fopen('/tmp/alma_mockup_log.txt', 'a');
	fwrite($f, date('Ymd H:i:s - ') . "\n" . print_r($text,1) . "\n\n");
	fclose($f);
  }

}

class AlmaMockupException extends Exception {}

?>