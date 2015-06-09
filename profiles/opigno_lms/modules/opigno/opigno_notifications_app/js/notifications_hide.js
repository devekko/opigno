/**
 * @file
 * Opigno notifications app javascript file to hide/show elements in form.
 */

(function ($, Drupal) {
    Drupal.behaviors.opigno_notifications_app = {
        attach: function (context) { //its called when page load and ajax

            var calendar_field = $('#edit-notification-add-calendar-und');
            var calendar_span = $('#notifications_timespan-div');
            calendar_field.change(function () {
                if (!calendar_field.is(':checked')) {
                    calendar_span.hide();
                }
                else {
                    calendar_span.show();
                }
            }).change();

            var notification_field = $('#edit-notification-notify-everyone-und');
            var notification_span = $('#edit-og-group-ref');
            notification_field.change(function () {
                if (!notification_field.is(':checked')) {
                    notification_span.show();
                }
                else {
                    notification_span.hide();
                }
            }).change();
        }
    }
})(jQuery, Drupal);