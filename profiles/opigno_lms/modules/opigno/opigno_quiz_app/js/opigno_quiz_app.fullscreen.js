/**
 * @file
 * Module JS logic.
 */

;(function ($, Drupal) {

  window.opignoQuizApp = {};

  Drupal.behaviors.opignoQuizAppFullScreen = {

    attach: function(context, settings) {
      if (opignoQuizApp._initialized == null) {
        for (var i = 0, len = Drupal.settings.opignoQuizApp.fullScreen.length; i < len; i++) {
          var node = Drupal.settings.opignoQuizApp.fullScreen[i],
              $form = $('form[action="' + Drupal.settings.basePath + 'node/' + node.nid + '/take"]', context); // @todo no clean url ??

          if ($form.length && !$form.hasClass('opigno-quiz-app-js-processed')) {
            $form.addClass('opigno-quiz-app-js-processed');
            opignoQuizApp.addFullscreenLinks($form.parent(), node);
          }
        }

        if ($.cookie('opigno_quiz_app_fs') == 'true') {
          $('body').addClass('opigno-quiz-app-fullscreen');
        }

        opignoQuizApp._initialized = true;
      }
    }
  }

  /**
   * Add the fullscreen links to the quiz navigation.
   *
   * @param {jQuery} $content
   */
  opignoQuizApp.addFullscreenLinks = function($content, node) {
    var $openLink = $('<a class="opigno-quiz-app-fullscreen-link opigno-quiz-app-go-fullscreen-link">' + Drupal.t("Go fullscreen") + '</a>'),
        $closeLink = $('<a class="opigno-quiz-app-fullscreen-link opigno-quiz-app-exit-fullscreen-link">' + Drupal.t("Exit fullscreen") + '</a>');
    
    var $quizNavigation = $content.find('#quiz_progress');
    // Prevent duplicates.
    $quizNavigation.find('a.opigno-quiz-app-fullscreen-link').remove();
    $quizNavigation.append($openLink).append($closeLink);

    $openLink.click(function() {
      opignoQuizApp.goFullScreen();
    });

    $closeLink.click(function() {
      opignoQuizApp.exitFullScreen();
    });
  };

  /**
   * Take the content full screen.
   */
  opignoQuizApp.goFullScreen = function() {
    if (!$('body').hasClass('opigno-quiz-app-fullscreen')) {
      $('body').addClass('opigno-quiz-app-fullscreen');
      $.cookie('opigno_quiz_app_fs', true);
    }
  };

  /**
   * Exit the fullscreen. Optionally reload the page, if a refresh is required.
   *
   * @param {jQuery} $content
   * @param {Boolean} reload
   */
  opignoQuizApp.exitFullScreen = function() {
    $('body').removeClass('opigno-quiz-app-fullscreen');
    $.cookie('opigno_quiz_app_fs', false);
  };

})(jQuery, Drupal);