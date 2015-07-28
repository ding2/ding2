<?php

function wyrna_wayf_authenticate($name, $wayfid) { 
  $return = array('success'=>FALSE);
  
  if( DingWayfUser::instance()->loginWayf($name, $wayfid) ){
  $return['creds'] = array(
      'name' => $name,
      'pass' => $wayfid,
    );

    $return['user'] = array(
      'data' => array('display_name' => $name),
      'mail' => $name,
    );
    $return['success'] = TRUE;
    $return['messages'] = array('HEJ', 'notice');
  }
  return $return;
}

function wyrna_wayf_bind($name, $wayfid) {
  return DingWayfUser::instance()->bindWayf($name, $wayfid);
}

function wyrna_wayf_delete($name) {
  return DingWayfUser::instance()->deleteWayf($name);
}

/**
 * 
 */
function wyrna_wayf_accept_form(){
  return '_wyrna_wayf_accept_form';
}

function _wyrna_wayf_accept_form() {
  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('element-section', drupal_html_class('wayf_accept_form')),
    ),
  );
  $form['container']['accept_form'] = array(
    'messages' => array(
      'message' => array(
        '#markup' => t('You have been authenticated by wayf, but you have no account etc...'),
      ),
      'accept' => array(
        '#type' => 'checkbox',
        '#default_value' => FALSE,
        '#title' => t('accept_wayf_binding', array(), array('context' => 'ding_wayf')),
      ),
    ),
  );
  $form['container']['actions'] = array(
    'abort' => array(
      '#name' => 'abort',
      '#type' => 'submit',
      '#value' => t('abort', array(), array('context' => 'ding_wayf')),
    ),
    'submit' => array(
      '#name' => 'continue',
      '#type' => 'submit',
      '#value' => t('continue', array(), array('context' => 'ding_wayf')),
    ),
  );
  
  $form['#validate'][] = 'wyrna_accept_form_validate';
   $form['#submit'][] = 'wyrna_accept_form_submit';  
  
  return $form;
}

function wyrna_accept_form_submit($form, $form_state){
  if ($form_state['clicked_button']['#name'] == 'abort') {
    ding_wayf_user_logout(NULL, 'user');
  }
}

function wyrna_wayf_login_creds($authentication_attributes, $notify_by_mail) {
  // set authentication provider for ding_user (@see ding_user_user_login_validate)
  $form_state['values']['authentication_provider'] = 'wayf';
// set name and password for login
  $form_state['values']['name'] = $authentication_attributes['mail'][0];
  $form_state['values']['mail'] = $authentication_attributes['mail'][0];
  $form_state['values']['pass'] = $authentication_attributes['eduPersonTargetedID'][0];
  if (isset($notify_by_mail)) {
    $form_state['mail_me'] = $notify_by_mail;
  }
  
  return $form_state;
}

/** \brief validation handler for accept_form
 *
 * @param type $form
 * @param type $form_state 
 */
function wyrna_accept_form_validate($form, &$form_state) {

  // check if $_SESSION variables are set
  if (!isset($_SESSION['accept_wayf'])) {
    // @TODO .. log; this method is of no use in this case
    return;
  }

// continue button clicked
  if ($form_state['clicked_button']['#name'] == 'continue') {
    if ($form_state['values']['accept']) {

// get name and pass from session; create a user if accept is set
// $_SESSION variables are set in $provider_wayf_validate
// @see bibdk_provider_wayf_validate

      $name = $_SESSION['accept_wayf']['name'];
      $pass = $_SESSION['accept_wayf']['pass'];
      $status = $_SESSION['accept_wayf']['status'];
      // we don't need the session variables anymore
      unset($_SESSION['accept_wayf']);

// prepare an array for ding_wayf_login
      $authentication_attributes['mail'][0] = $name;
      $authentication_attributes['eduPersonTargetedID'][0] = $pass;

      switch ($status) {
        // first use case - no account with bibliotek.dk
        case 'no_user':
          if (ding_provider_implements('user', 'create_account')) {
            if (ding_provider_invoke('user', 'create_account', $name, $pass)) {
              // user has been created with mail, wayfid.
              if (ding_provider_implements('wayf', 'bind')) {
                ding_provider_invoke('wayf', 'bind', $name, $pass);
              }
              // pass key for email to login method
              $notify_by_mail->key = 'wayf_new_user';
              // if user wishes to change password later on he can do so
              ding_wayf_login($authentication_attributes,  $notify_by_mail);
            }
          }
          break;
        // next use case - user has an bibdk account, but no wayfid
        case 'bibdk_user':
          if (ding_provider_implements('wayf', 'bind')) {
            if (ding_provider_invoke('wayf', 'bind', $name, $pass)) {
              ding_wayf_login($authentication_attributes);
            }
          }
          break;
        default:
          drupal_set_message(t('wayf_could_not_login', array(), array('context' => 'ding_wayf')));
          drupal_goto('user');
          break;
      }
    }
    else {
// user clicked continue, but did not check accept. maybe user forgot to check the box
// tell him to either check the box or press abort
      form_set_error('accept', t('either check accept or press abort', array(), array('context' => 'ding_wayf')));
    }
  }
}

class DingWayfUser {
  private static $instance;
  protected $validUsers = array();

  private function __construct() {
    
    variable_set('wyrna_users',
        array('eduPersonTargetedID' => 'WAYF-1234567890', 'mail' => 'dummy@dbc.dk',));
    
    $this->validUsers = variable_get('wyrna_users', array());
  }

  public static function instance() {
    if (!isset(self::$instance)) {
      self::$instance = new DingWayfUser();
    }

    return self::$instance;
  }

  public function deleteWayf($name) {
    unset($this->validUsers[$name]);
    variable_set('wyrna_users', $this->validUsers);
  }

  public function loginWayf($name, $wayfid) {
    return isset($this->validUsers[$name]) && $this->validUsers[$name] == $wayfid;
  }

  public function bindWayf($name, $wayfid) {
    $this->validUsers[$name] = $wayfid;
    variable_set('wyrna_users', $this->validUsers);
    return TRUE;
  }
}
