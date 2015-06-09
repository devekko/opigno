(function ($) {

Drupal.behaviors.cloze = {
  attach: function (context, settings) {
    // We get the answer from the drupal setting
    var answer = Drupal.settings.answer;
    /* The answer has been converted to upper case becaue the keys entered are displayed as upper case*/
    /* Hence to avoid case insensitive part, I have made it to upper case*/

    jQuery('.answering-form .cloze-question input').keyup(function(e) {
      var id = this.id;
      var present_class =  jQuery('#'+id).attr('class');
      present_class = present_class.replace('form-text','');
      present_class = present_class.trim();
      var field_answer = answer[present_class].toUpperCase();
      /*Get the position of cursor in the input field*/
      /*This denotes how many letters has been entered in the input field*/
      var count = jQuery('#'+id).val().length;
      /*Get the letter that is being entered in the input field*/
      var value = String.fromCharCode(e.keyCode);
      if(value == field_answer.charAt(count-1)) {
        e.preventDefault();
        return false;
      }
      else {
        jQuery('#'+id).val(
        function(index,value){
          return value.substr(0,value.length-1);
        })
      }
    });
  }
};

})(jQuery);

