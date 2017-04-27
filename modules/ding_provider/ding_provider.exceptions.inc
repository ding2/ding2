<?php

/**
 * @file
 * Ding provider exception classes.
 */

/**
 * Exception that is thrown by providers when the given operation
 * cannot be completed until the user authenticates.
 */
class DingProviderAuthException extends Exception { }

/**
 * Thrown when no provider is configured for the given provider.
 */
class DingProviderNoProvider extends Exception { }

/**
 * Thrown when provider doesn't implement the given function.
 */
class DingProviderDoesntImplement extends Exception { }

/**
 * Exception class that can provide a translated and substituted
 * message. Exceptions that is instanceof DingProviderUserException is
 * errors appropriate for displaying to the end user. Internal errors
 * not suitable for end users should not be implemented as as subclass
 * of this class.
 *
 * When instantiating this class or subclasses, you should give a
 * translated string as message, like so:
 * @code
 *   throw new DingProviderUserException(t('Internal error on @title'));
 * @endcode
 *
 * Which replacements are available should be documented in the
 * Exception or one of it's parents.
 */
class DingProviderUserException extends Exception {
  /**
   * Return the error message with replacements substituted just like
   * t(). NOTE: The message returned by getMessage is already
   * translated, this methods only takes care of replacements.
   *
   * @param $args
   *   Array of replacements, just like the second argument to t().
   * @return
   *   The translated string.
   */
  public function getMessageT($args) {
    $string = $this->getMessage();
    if (empty($args)) {
      return $string;
    }
    else {
      // Allow subclasses to add in default args.
      if (property_exists($this, 'args')) {
        $args += $this->args;
      }
      // Transform arguments before inserting them.
      foreach ($args as $key => $value) {
        switch ($key[0]) {
          case '@':
            // Escaped only.
            $args[$key] = check_plain($value);
            break;

          case '%':
          default:
            // Escaped and placeholder.
            $args[$key] = drupal_placeholder($value);
            break;

          case '!':
            // Pass-through.
        }
      }
      return strtr($string, $args);
    }
  }
}
