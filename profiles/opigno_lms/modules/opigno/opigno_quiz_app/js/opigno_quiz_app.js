/**
 * @file
 * Module JS logic.
 */

;(function ($, Drupal) {

  Drupal.behaviors.opignoQuizApp = {

    attach: function (context, settings) {

      var $collapsibleTables = $('table.opigno-quiz-app-results-collapsible-table:not(.js-processed)', context);
      if ($collapsibleTables.length) {
        $collapsibleTables.find('thead tr:eq(0)').each(function() {
          var $this = $(this);
          $this.click(function() {
            $this.parents('table:eq(0)').find('tbody').toggle();
          }).addClass('js-processed').click();
        });
      }

      var $shortAnswerFields = $('form.answering-form input[name="tries"].form-text:not(.js-processed)', context);
      if ($shortAnswerFields.length) {
        $shortAnswerFields.keydown(function(e) {
          // There is a bug in Quiz. When hitting Enter on a simple textfield, it submits
          // the Back button instead of the Next one. Correct this with JS.
          if (e.which === 13) {
            e.preventDefault();
            $('#edit-submit').click();
            return false;
          }
        });
      }
    }

  };

})(jQuery, Drupal);