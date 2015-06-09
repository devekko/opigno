/**
 * @file
 * Define theme JS logic.
 */

;(function($, Drupal, window, undefined) {

  Drupal.settings.platon = Drupal.settings.platon || {};

  Drupal.behaviors.platon = {

    attach: function(context) {

      // Remove no-js class from html.
      $('html').removeClass('no-js');

      if($('#opigno-group-progress').length)         // use this if you are using id to check
      {
          $("#second-sidebar #content").addClass("has-group-progress");
          $("#second-sidebar #tabs").addClass("has-group-progress");
          $("#second-sidebar .action-links").addClass("has-group-progress");
          $("#first-sidebar").addClass("collapsed");
      }

      // Make search form appear on hover.
      var $headerSearch = $('#header-search', context);
      if ($headerSearch.length && !$headerSearch.hasClass('js-processed')) {
        // On mouseenter, show the form (if not already visible). Else, hide it - unless one of the child inputs has focus.
        $headerSearch.hover(
          function() {
            if (!(Modernizr && Modernizr.mq && Modernizr.mq('(min-width: 800px)'))) {
              return;
            }

            // Clear any past timeouts.
            if (this._timeOut) {
              clearTimeout(this._timeOut);
            }

            if (!$headerSearch.hasClass('opened')) {
              $headerSearch.addClass('opened').animate({ width: '180px' });
            }
          },
          function() {
            if (!(Modernizr && Modernizr.mq && Modernizr.mq('(min-width: 800px)'))) {
              return;
            }

            // Clear any past timeouts.
            if (this._timeOut) {
              clearTimeout(this._timeOut);
            }

            // Wait for half a second before closing.
            this._timeOut = setTimeout(function() {
              // Only close if no child input has any focus.
              if (!$headerSearch.find('input:focus').length) {
                $headerSearch.animate({ width: '40px' }, { complete: function() { $headerSearch.removeClass('opened'); } });
              }
            }, 500);
          }
        );

        // If a child input is blurred, trigger the "mouseleave" event to see if we can close it.
        $headerSearch.find('input[type="text"], input[type="submit"]').blur(function() {
          $headerSearch.mouseleave();
        });

        // Add a placeholder text to the search input.
        $headerSearch.find('input[type="text"]').attr('placeholder', Drupal.t("Search") + '...');

        // Don't process it again.
        $headerSearch.addClass('js-processed');
      }

      // Make messages dismissable.
      $('div.messages', context).each(function() {
        var $message = $(this),
            $dismiss = $('span.messages-dismiss', this);
        if ($dismiss.length && !$dismiss.hasClass('js-processed')) {
          $dismiss.click(function() {
            $message.hide('fast', function() { $message.remove(); });
          }).addClass('js-processed');
        }
      });

      // Make entire section in admin/opigno clickable and hoverable.
      var $adminSections = $('div.admin-panel dt', context);
      if ($adminSections.length) {
        $adminSections.each(function() {
          var $this = $(this);

          // Only process it once.
          if (!$this.hasClass('js-processed')) {
            $this._dd = $this.next('dd');

            // On hover, make entire section light up.
            $this.hover(
              function() {
                $this.addClass('hover');
                $this._dd.addClass('hover');
              },
              function() {
                $this.removeClass('hover');
                $this._dd.removeClass('hover');
              }
            );
            $this._dd.hover(
              function() {
                $this.mouseenter();
              },
              function() {
                $this.mouseleave();
              }
            );

            // On click, trigger the dt > a click.
            $this.click(function() {
              window.location.href = $this.find('a')[0].href;
            });
            $this._dd.click(function() {
              $this.click();
            });

            // Flag them as being processed.
            $this.addClass('js-processed');
            $this._dd.addClass('js-processed');
          }
        });
      }

      // Show the number of unread messages.
      if (typeof Drupal.settings.platon.unreadMessages !== 'undefined' && Drupal.settings.platon.unreadMessages) {
        var $messageLink = $('#main-navigation-item-messages', context);
        if ($messageLink.length && !$messageLink.hasClass('js-processed')) {
          $messageLink.find('a').prepend('<span id="messages-num-unread">' + Drupal.settings.platon.unreadMessages + '</span>');
          $messageLink.addClass('js-processed');
        }
      }

      // Make the entire tool "block" clickable for a better UX.
      $('.opigno-tool-block', context).each(function() {
        var $this = $(this);
        if (!$this.hasClass('js-processed')) {
          $this.click(function() {
            window.location = $this.find('a.opigno-tool-link').attr('href');
          }).addClass('js-processed');
        }
      });

      // Make the left menu collapsible.
      var $left = $('#first-sidebar', context);
      if ($left.length) {
        if (!$left.hasClass('js-processed')) {
          $left.append('<span id="first-sidebar-toggle"></span>');

          $('#first-sidebar-toggle').click(function() {
            $left.toggleClass('collapsed');
            if (!$left.hasClass('collapsed'))
            {
                if($('#opigno-group-progress').length)         // use this if you are using id to check
                {
                $("#second-sidebar #content").removeClass("has-group-progress");
                $("#second-sidebar #tabs").removeClass("has-group-progress");
                $("#second-sidebar .action-links").removeClass("has-group-progress");
                $("#opigno-group-progress").hide();
                }
            }
            else
            {
                if($('#opigno-group-progress').length)         // use this if you are using id to check
                {
                $("#second-sidebar #content").addClass("has-group-progress");
                $("#second-sidebar #tabs").addClass("has-group-progress");
                $("#second-sidebar .action-links").addClass("has-group-progress");
                $("#opigno-group-progress").show();
                }
            }
            setTimeout(function() {
              $.cookie('left_collapsed', $left.hasClass('collapsed') ? 1 : 0);   
            }, 10);
          });

          $left.addClass('js-processed');
        }

        if ($.cookie('left_collapsed') === '1') {
          $left.addClass('collapsed');
        }
      }

      // Make menu "toggleable" on mobile.
      var $menuToggle = $('#menu-toggle-link', context);
      if (!$menuToggle.hasClass('js-processed')) {
        $menuToggle.click(function() {
          $('#main-navigation-wrapper').toggleClass('open');
        }).addClass('js-processed');
      }
    }

  };

})(jQuery, Drupal, window);
