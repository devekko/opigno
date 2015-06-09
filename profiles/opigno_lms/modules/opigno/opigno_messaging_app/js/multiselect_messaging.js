/**
 * @file
 * Opigno messaging app javascipt file
 */

(function($,Drupal){
    Drupal.behaviors.opigno_messaging={
        attach:function(context){ //its called when page load and ajax
            var divs = document.getElementsByClassName('form-item-recipient');
            for(var i=0; i < divs.length; i++) {
                divs[i].style.visibility = 'hidden';
                divs[i].style.height = '0px';
            }

            var updateHidden=function(){
                var usernames= new Array();
                $('.multiselect_sel option').each(function(){
                    usernames.push(this.innerHTML);
                })
                $('#edit-recipient').val(usernames.join(','));
            }

            $('select.multiselect_unsel, select.multiselect_sel', context).dblclick(function() {
                setTimeout(function(){updateHidden()},10);
            });

            $('li.multiselect_add,li.multiselect_remove', context).click(function() {
                setTimeout(function(){updateHidden()},10);
            });
            console.log(context);

            if ($('.multiselect_sel',context).length>0)
            {
               var prevusers = $('#edit-recipient').val().split(',');
               var options='';
                for (var i=0;i<prevusers.length;i++)
                {
                    if (prevusers[i].length){
                    options+='<option>'+prevusers[i]+'</option>';
                    console.log($('option[value="'+prevusers[i]+'"]',context));
                    $('option[value="'+prevusers[i]+'"]',context).remove();
                    }



                }
               $('.multiselect_sel').html(options);
            }
        }
    }
})(jQuery,Drupal);

