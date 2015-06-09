var $folderName, $folderMenu, $folderContainer, $folderMenuContainer, $tacLink, $reorderLink, $manageLink, $tftBack, currentTID = 0, parentTID = 0, tft = {}, rootFolderName;

;(function($, jQuery) {
/**
 * Init the Taxonomy File Tree module
 */
Drupal.behaviors.initTFT = {

  attach: function(context) {
    /**
     * Store some global variables
     */
    if (!$folderName) {
      $folderName = $('#folder-name', context);
    }
    
    if (!$folderMenuContainer) {
      $folderMenuContainer = $('#folder-menu-container', context);
    }
    
    if (!$folderContainer) {
      $folderContainer = $('#folder-content-container', context);
    }
    
    if (!$folderMenu) {
      $folderMenu = $('#tabs', context);
    }
    
    if (!rootFolderName) {
      rootFolderName = $('#folder-name', context).html();
    }
    
    // Activate the "go to parent" link
    tft.activateParentLink();

    // Hash the manage links
    tft.hashManageLinks();
    
    // Hash the TAC lite link
    tft.hashTacLink();
    
    /**
     * Add event listeners for each folder link.
     * Will call tft.loadFolder to load the folder content via AJAX.
     */
    $('a.folder-link', context).each(function() {
      (function($this) {
        $this.click(function(e) {
          var tid = $this.parent('span').parent('li').attr('id').replace('tid-', '');
          
          if (tid) {          
            tft.loadFolder(tid);
          }
          
          //return false;
        });
      })($(this));
    });
    
    /**
     * Add event listeners for openening / closing each folder.
     * Will change the CSS classes of itself and the parent <li>
     */
    $('li.parent-folder span.closed-icon', context).each(function() {
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

    // Make tree collapsible
    $('#tft-outline tr.draggable:not(tr.tabledrag-leaf)', context).each(function() {
      var $icon = $(this).find('a.tabledrag-handle').after('<span class="icon opened-icon"></span>').next('span.icon');

      // Make sure we're not binding the click event twice
      $icon.unbind('click');

      $icon.click(function(e) {
        e.stopPropagation();

        var id = $icon.parents('tr').find('input.taxonomy_term_hierarchy-tid').val();

        if ($icon.hasClass('closed-icon')) {
          $icon.removeClass('closed-icon');
          $icon.addClass('opened-icon');

          tft.toggleChildrenDisplay(true, id)
        }
        else {
          $icon.removeClass('opened-icon');
          $icon.addClass('closed-icon');

          tft.toggleChildrenDisplay(false, id)
        }

        return false;
      }).click();
    });
    
    // Prepare the new folder links
    tft.prepareFolderLinks();
    
    // Hash the file 'edit' links
    tft.hashFileLinks();
    
    // Make the table sortable
    tft.makeTableSortable();
    
    /**
     * Setup the AJAX object with some default options
     */
    $.ajaxSetup({
      url: Drupal.settings.basePath + '?q=tft/ajax/get-folder',
      success: tft.requestCompleted,
      error: tft.requestFailed,
      type: 'get',
      dataType: 'json'
    });
    
    // If a url hash is present, load the selected folder
    if (String(window.location.hash).length > 1) {
      currentTID = String(window.location.hash).replace('#term/', '');
      
      tft.loadFolder(currentTID);
      
      tft.openFolder(currentTID);
    }
  }
};

/**
 * Change the folder menu.
 *
 * @param String name
 *        The new folder name
 * @param Number tid
 *        The new taxonomy term tid
 */
tft.changeFolderMenu = function(name, tid) {
  $folderName.html(name);
}

/**
 * Load the selected folder content via AJAX.
 *
 * @returns false
 */
tft.loadFolder = function(tid) {
  var name, parentName;
  
  currentTID = tid;
  
  $.ajax({
    data: 'tid='+tid
  });
  
  // Change folder name
  parentName  = $('#tid-' + tid + ' > span > a').html();
  
  if (parentName) {
    name = parentName;
  }
  else {
    name = rootFolderName;
  }
  
  tft.changeFolderMenu(name, tid);
  
  // Highlight active folder
  tft.setActiveFolder(tid);
  
  // Set the loader animation  
  $folderContainer.css('background-image', 'url(' + Drupal.settings.basePath + Drupal.settings.tftDirectory + '/img/ajax-loader.gif)');
  
  return false;
}

/**
  * Add event listeners for each folder link.
  * Will call tft.loadFolder to load the folder content via AJAX.
  *
  * @returns false
  */
tft.prepareFolderLinks = function() {
  $('a.folder-folder-link').each(function() {
    (function($this) {
      $this.click(function(e) {
        var tid = $this.attr('id').replace('tid-', '');
        
        if (tid) {          
          tft.loadFolder(tid);
          
          tft.openFolder(tid);
        }
        
        //return false;
      });
    })($(this));
  });
}


tft.toggleChildrenDisplay = function(display, paramID) {
  $('input.taxonomy_term_hierarchy-parent[value="' + paramID + '"]').each(function() {
    var $this = $(this);
    var $row = $this.parents('tr');

    if (display) {
      $row.show();
    }
    else {
      $row.hide().find('span.icon').removeClass('opened-icon').addClass('closed-icon');
      var id = $row.find('input.taxonomy_term_hierarchy-tid').val();
      tft.toggleChildrenDisplay(display, id);
    }
  });
};

/**
 * Highlight the selected folder by adding a CSS class
 */
tft.setActiveFolder = function(tid) {
  // Add CSS 'active' class to selected folder
  $('li.folder.active').each(function() {
    $(this).removeClass('active');
  });
  
  $('#tid-' + tid).addClass('active');
}

/**
 * Recursively open the parent folders in the folder tree.
 * Call loadFolder to load the folder content.
 *
 * @returns false
 */
tft.openFolder = function(tid) {
  // Open the parent folders in the tree
  $('#tid-' + tid).parents('ul').each(function() {
    (function($this) {
      $this.css('display', 'block');
      $this.siblings('span').each(function() {
        $(this).removeClass('closed-icon').addClass('opened-icon');
      });
    })($(this));
  });
  
  // Highlight active folder
  tft.setActiveFolder(tid);
  
  // Load the folder content
  return tft.loadFolder(tid);
}

/**
 * Insert the HTML inside #folder-content-container
 */
tft.requestCompleted = function(json, status, xhr) {
  if (json.error) {
    alert(json.data);
    return;
  }
  
  // Insert the HTML
  $folderContainer.html(json.data);
  
  // Replace the folder menu links
  $folderMenu.html(json.ops_links);
  
  // Activate the "go to parent" link
  tft.activateParentLink();
  
  // Hash the manage links
  tft.hashManageLinks();
  
  // Hash the file 'edit' links
  tft.hashFileLinks();
  
  // Hash the TAC lite link
  tft.hashTacLink();
  
  if (json.parent > -1) {
    parentTID = json.parent;
  }
  else {
    parentTID = null;
  }
  
  // Remove the loader animation
  $folderContainer.css('background-image', '');
  
  // Prepare the new folder links
  tft.prepareFolderLinks();
  
  // Make the table sortable
  tft.makeTableSortable();
  
  // Improve the "add" links with a hash of the current term tid
  var $addFile = $('#add-child-file');
  var $addFolder = $('#add-child-folder');
  
  var href = $addFile.attr('href');
  $addFile.attr('href', href + '%23term/' + currentTID);
  
  href = $addFolder.attr('href');
  $addFolder.attr('href', href + '%23term/' + currentTID);
}

/**
 * Request failed
 */
tft.requestFailed = function(xhr, status, e) {
  // Alert error
  alert("Request failed. Status: " + status + "\n" + e);
  
  // Remove the loader animation
  $folderContainer.css('background-image', '');
}

/**
 * Make the table sortable
 */
tft.makeTableSortable = function() {
  if ($.fn.tablesorter !== undefined) {
    $("#folder-content-container > table").tablesorter({ headers: { 4: { sorter: false } } } );
  }
}

/**
 * Activate the "go to parent" link
 */
tft.activateParentLink = function() {
  // We must always get the link again, as the html is replaced with AJAX calls
  $tftBack = $('#tft-back-link');
  
  /**
   * Add an event listener for the "go to parent" link.
   * Will call tft.loadFolder to load the folder content via AJAX.
   *
   * @returns false
   */
  $tftBack.click(function() {
    if (parentTID > -1 && !$tftBack.hasClass('disabled')) {
      tft.loadFolder(parentTID);
    }
    
    //return false;
  });
}

/**
 * Hash the edit TAC lite link.
 */
tft.hashTacLink = function() {
  if (currentTID) {
    // We must always get the link again, as the html is replaced with AJAX calls
    $tacLink = $('#tac-edit > a');
    
    if ($tacLink) {
      var href = $tacLink.attr('href');
      $tacLink.attr('href', href + '%23term/' + currentTID);
    }
  }
}

/**
 * Hash the manage sub-folders link.
 */
tft.hashManageLinks = function() {
  if (currentTID) {
    // We must always get the link again, as the html is replaced with AJAX calls
    var $links = $('#manage-folders > a, #reorder-folders > a');

    if ($links.length) {
      $links.each(function() {
        var href = this.href;

        this.href = href + '%23term/' + currentTID;
      });
    }
  }
}

/**
 * Hash the file 'edit' links.
 */
tft.hashFileLinks = function() {
  if (currentTID) {
    // We must always get the links again, as the html is replaced with AJAX calls
    $('a.node-edit-link, a.term-edit-link').each(function() {
      $this = $(this);
      var href = $this.attr('href');
      $this.attr('href', href + '%23term/' + currentTID);
    });
  }
}

/**
 * Format a link tag, similar to the Drupal l() function.
 * @see http://api.drupal.org/api/drupal/includes--common.inc/function/l/6
 *
 * @param String text
 *        The anchor text
 * @param String
 *        The path. Should be a Drupal internal path
 * @param Object options
 *        A keyed object with optional 'query', 'class', 'id' or 'style' keys.
 *
 * @returns String
 *        The formatted link
 */
tft.l = function (text, path, options) {
  var cssClass = '', cssID = '', style = '', query = '';
  
  if (options) {
    if (options.query) {
      query = '&';
      
      var item;
      for (item in options.query) {
        query += item + '=' + options.query[item] + '&';
      }
      
      query = String(query).substring(0, String(query).length - 1);
    }
    
    if (options.cssClass) {
      cssClass = ' class="' + options.cssClass + '"';
    }
    
    if (options.id) {
      cssID = ' class="' + options.id + '"';
    }
    
    if (options.style) {
      styles = ' style="' + options.style + '"';
    }
  }
  
  if (!Drupal.settings.cleanUrl) {
    path = '?q=' + path;
  }
  
  return '<a href="' + Drupal.settings.basePath + path + query + '"' + cssClass + cssID + style + '>' + text + '</a>';
}
})(jQuery, Drupal);
