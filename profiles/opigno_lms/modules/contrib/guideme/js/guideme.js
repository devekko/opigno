/**
 * @file
 * Defines the client side logic for Guideme.
 */

;(function($, Drupal, window, undefined) {
  
  Drupal.behaviors.guideMe = {

    attach: function(context, settings) {
      console.log(settings);
      var $guideMeSteps = $('#guideme-steps', context);
      if (!$guideMeSteps.length) {
        var html = '<ol id="guideme-steps">';

        for (var i = 0, len = settings.guideMe.steps.length; i < len; i++) {
          var attributes = '';
          if (settings.guideMe.steps[i].target !== undefined) {
            attributes += ' data-selector="' + settings.guideMe.steps[i].target.replace(/"/g, "\'") + '"';
          }

          if (settings.guideMe.steps[i].button_label !== undefined) {
            attributes += ' data-button="' + settings.guideMe.steps[i].button_label + '"';
          }

          html += '<li' + attributes + '><div class="guideme-modal-wrapper">';
          if (settings.guideMe.steps[i].title !== undefined) {
            html += '<div class="guideme-modal-title">' + settings.guideMe.steps[i].title + '</div>';
          }

          html += '<div class="guideme-modal-content">' + settings.guideMe.steps[i].description + '</div></div></li>';
        }

        html += '</ol>';
        $guideMeSteps = $(html);
        $guideMeSteps.appendTo('body');
        $guideMeSteps.joyride({
          autoStart: true,
          postStepCallback: function(index, element, closed) {
            if (closed) {
              if (confirm(Drupal.t("Do you want to mark this step-by-step guide as done, or do you want to see it again later ?"))) {
                $.ajax({
                  url: Drupal.settings.basePath + '?q=guideme/mark-done/' + settings.guideMe.id,
                  type: 'post',
                  data: { token: settings.guideMe.token }
                });
              }
            }
          }
        });
      }
    }

  };

})(jQuery, Drupal, window);