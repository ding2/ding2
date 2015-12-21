(function($) {
    "use strict";

    $(document).ready(function() {
        // Focus on username form field when entering login form.
        $('#user-login-form #edit-name').focus();

        // Focus on username form field when clicking login tab.
        $('.topbar-link-user').bind('click', function(event) {
            $('#user-login-form #edit-name').focus();
        });

        // Unfocus login form when user wants to scroll with key buttons (i.e. clicks the up or down button).
        $('#user-login-form').bind('keydown', function(event) {
            var keymap = {
                up: 38,
                down: 40
            };

            // Only unfocus if we press the up or down key.
            if (keymap.up == event.which || keymap.down == event.which) {
                document.activeElement.blur();
            }
        });
    });
}(jQuery));
