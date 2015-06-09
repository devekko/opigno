/**
 *
 */
;(function($, Drupal) {
Drupal.behaviors.initTFTNodeForm = {

  attach: function(context) {
    /**
     * Add event listeners for openening / closing each folder.
     * Will change the CSS classes of itself and the parent <li>
     */
    $('li.parent-folder span.closed-icon').each(function() {
      (function ($this) {
        $this.click(function(e) {
          var li = $this.parent(), ul = $this.next().next();
          
          // Change the CSS class of the parent <li>,
          // change own CSS class and
          // change the display of the sibling <ul>
          if (li.hasClass('closed')) {
            li.removeClass('closed');
            li.addClass('opened');
            
            $this.removeClass('closed-icon');
            $this.addClass('opened-icon');
            
            ul.css('display', 'block');
          }
          else {
            li.removeClass('opened');
            li.addClass('closed');
            
            $this.removeClass('opened-icon');
            $this.addClass('closed-icon');
            
            ul.css('display', 'none');
          }
        });
      })($(this));
    });
    
    /**
     *
     */
    $('a.folder-link').each(function() {
      (function($this) {
        $this.click(function(e) {
          var tid = $this.parent('span').parent('li').attr('id').replace('tid-', '');
          
          if (tid) {          
            setActiveFolder(tid);
          }
          
          return false;
        });
      })($(this));
    });
    
    setActiveFolder($('select[name="tft_folder[und]"]').val(), true);
  }
}

/**
 *
 */
function setActiveFolder(tid, scroll) {
  if ((!tid)||(tid=='_none')){return;}
  // Add CSS 'active' class to selected folder
  $('li.folder.active').each(function() {
    $(this).removeClass('active');
  });
  
  var $folder = $('#tid-' + tid);
  
  $folder.addClass('active');

  // Open the parent folders in the tree
  $('#tid-' + tid).parents('ul').each(function() {
    (function($this) {
      $this.css('display', 'block');
      $this.siblings('span').each(function() {
        $(this).removeClass('closed-icon').addClass('opened-icon');
      });
    })($(this));
  });
  
  $('select[name="tft_folder[und]"]').val(tid);
  
  if (scroll) {
    var amount = $folder.offset().top - $('#folder-explorer-container').offset().top - 100;
    
    setTimeout(function () {
      $('#folder-explorer-container').scrollTop(amount);
    }, 500);
  }
}
})(jQuery, Drupal);
