<?php
/**
 * @file
 * Search API filter to use on roles.
 */

/**
 * Represents a data alteration that restricts entity indexes to some bundles.
 */
class DingFrontendUserRoleFilter extends SearchApiAbstractAlterCallback {

  /**
   * Implements SearchApiAlterCallbackInterface::alterItems().
   */
  public function alterItems(array &$items) {
    $roles = $this->options['roles'];
    $default = (bool) $this->options['default'];
    foreach ($items as $id => $item) {
      if ($item->item_type == 'user') {
        $account = $item->user;
        switch ($this->options['match_type']) {
          case 'partial':
            $keys = array_keys($account->roles);
            $t = array_intersect_key($roles, $account->roles);
            $role_match = (count(array_intersect_key($roles, $account->roles)) === count($roles));
            break;

          default:
            $role_match = (count(array_diff_key($account->roles, $roles)) !== count($account->roles));
            break;
        }

        if ($role_match === $default) {
          unset($items[$id]);
        }
      }
    }
  }

  /**
   * Overrides SearchApiAbstractAlterCallback::configurationForm().
   *
   * Add option for the roles to include/exclude.
   */
  public function configurationForm() {
    $options = array_map('check_plain', user_roles());
    $form = array(
      'default' => array(
        '#type' => 'radios',
        '#title' => t('Which users should be indexed?'),
        '#default_value' => isset($this->options['default']) ? $this->options['default'] : 1,
        '#options' => array(
          1 => t('All but those from one of the selected roles'),
          0 => t('Only those from the selected roles'),
        ),
      ),
      'match_type' => array(
        '#type' => 'radios',
        '#title' => t('Which users should be indexed?'),
        '#default_value' => isset($this->options['match_type']) ? $this->options['match_type'] : 'partial',
        '#options' => array(
          'all' => t('Should match roles (user only has selected roles)'),
          'partial' => t('Should have roles (may have other roles as well)'),
        ),
      ),
      'roles' => array(
        '#type' => 'select',
        '#title' => t('Roles'),
        '#default_value' => isset($this->options['roles']) ? $this->options['roles'] : array(),
        '#options' => $options,
        '#size' => min(4, count($options)),
        '#multiple' => TRUE,
      ),
    );
    return $form;
  }
}
