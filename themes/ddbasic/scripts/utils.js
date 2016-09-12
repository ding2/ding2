/*jshint forin:false, jquery:true, browser:true, indent:2, trailing:true, unused:false */

(function (scope, $) {
  'use strict';

  var
    /** Breakpoint identifiers. */
    _bpi = {};

  if (scope.ddbasic === undefined) {
    scope.ddbasic = {};
  }

  /**
   * Helper for only running code once when entering or leaving a breakpoint.
   */
  scope.ddbasic.breakpoint = {
    /** Moving into the breakpoint. */
    IN: true,

    /** Moving out of the breakpoint. */
    OUT: false,

    /** Breakpoint already tested. */
    NOP: null,

    /** Check if  */
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
     *
     */
    reset: function (identifier) {
      delete _bpi[identifier];
    }
  }

})(this, jQuery);
