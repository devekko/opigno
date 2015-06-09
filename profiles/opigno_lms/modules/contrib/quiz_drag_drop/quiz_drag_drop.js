/**
 * @file
 * Javascript functions for the quiz drag drop question type.
 * 
 */

var answerCount = 0;
var dragCount = 0;

(function($) {
  Drupal.behaviors.quiz_drag_drop = {
    attach: function(context) {
      $(".draggable").draggable({
        revert: 'invalid',
        snap: true,
        stop: function(event, ui) {}
      });
      $(".droppable").droppable({
        tolerance: 'fit',
        greedy: false,
        refreshPositions: true,
        drop: function(event, ui) {
          var placeholderId = this.id;
          var placeholderIdArray = placeholderId.split('_');
          var placeholderFid = placeholderIdArray[1];

          var imageId = ui.draggable.attr("id");
          var imageDraggedArray = imageId.split('_');
          var imageFid = imageDraggedArray[1];

          if(placeholderFid == imageFid) {
            answerCount++;
          }
          dragCount++;

          $("#" + imageId).draggable("option", "disabled", true);
          $('#' + placeholderId).droppable("option", "disabled", true);
          $('#dropCount').val(dragCount);
          $('#answerCount').val(answerCount);
        }
      });

      $("#btnReset").click(function() {
        $(".draggable").animate({
            "left": '',
            "top": ''
        });
        answerCount = 0;
        dragCount = 0;

        $('#dropCount').val(dragCount);
        $('#answerCount').val(answerCount);

        $("li[id^='placeholder_']").each(function(){
          var id = $(this).attr("id");
          var idArray = id.split('_');
          $('#' + id).droppable("option", "disabled", false);
          $('#image_' + idArray[1]).draggable("option", "disabled", false);
        });

        return false;
      });
      $(".ui-draggable").data("left", $(".ui-draggable").position().left).data("top", $(".ui-draggable").position().top);
    }
  };
})(jQuery);
