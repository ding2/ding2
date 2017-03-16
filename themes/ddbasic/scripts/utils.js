/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */
(function (scope, $) {
  'use strict';

  var
    /**
     * Holder for the breakpoint identifiers.
     */
    _bpi = {};

  if (scope.ddbasic === undefined) {
    scope.ddbasic = {};
  }

  /**
   * Helper for only running code once when entering or leaving a breakpoint.
   */
  scope.ddbasic.breakpoint = {
    /**
     * Moving into the breakpoint.
     */
    IN: true,

    /**
     * Moving out of the breakpoint.
     */
    OUT: false,

    /**
     * Breakpoint already tested.
     * Meaning it's not changing "state".
     */
    NOP: null,

    /**
     * Check if the specific breakpoint is activated.
     *
     * @param string breakpoint
     *   The breakpoint to check for.
     * @param string identifier
     *   The identifier/context.
     *
     * @return mixed
     *   Returns if the breakpoint is activated (IN), deactivated (OUT) or
     *   it hasn't changed (NOP), in reference to the identifier.
     */
    is: function (breakpoint, identifier) {
      var
        $checker = $('.is-' + breakpoint),
        result = $checker.is(':visible');

      if (identifier === undefined) {
        return result ? this.IN : this.OUT;
      }

      if (_bpi[identifier] !== result) {
        _bpi[identifier] = result;
        return result ? this.IN : this.OUT;
      }

      return this.NOP;
    },

    /**
     * Reset an identifier.
     *
     * @param string identifier
     *   The identifier/context.
     */
    reset: function (identifier) {
      delete _bpi[identifier];
    }
  };

})(this, jQuery);
