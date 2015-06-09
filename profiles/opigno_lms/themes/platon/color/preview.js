/**
 * @file
 * Color preview logic.
 */


;(function ($, Drupal, undefined) {

  Drupal.color = {

    imgChanged: false,

    initialized: false,

    callback: function(context, settings, form, farb, height, width) {
      // Change the logo to be the real one.
      if (!this.imgChanged) {
        if (Drupal.settings.color.logo == null) {
          $('#preview-user-account-information-picture img').attr('src', Drupal.settings.basePath + Drupal.settings.color.themePath + '/logo.png');
        }
        else {
          $('#preview-logo img').attr('src', Drupal.settings.color.logo);
        }
        $('#preview-user-account-information-picture img').attr('src', Drupal.settings.basePath + Drupal.settings.color.themePath + '/img/anonymous-account.png');
        this.imgChanged = true;
      }

      // This should be handled by Color, but seems to break with Platon (??)
      // Implement the scheme select change ourselves.
      // @todo Figure out why Color is not updating the form and correct it.
      if (!this.initialized) {
        $('select[name="scheme"]').change(function() {
          var value = $(this).val();
          if (value != '') {
            for (var color in Drupal.settings.color.schemes[value]) {
              $('#palette input[name="palette[' + color + ']"]', form).val(Drupal.settings.color.schemes[value][color]).css({
                backgroundColor: Drupal.settings.color.schemes[value][color],
                'color': farb.RGBToHSL(farb.unpack(Drupal.settings.color.schemes[value][color]))[2] > 0.5 ? '#000' : '#fff'
              });
            }

            // Trigger change event.
            Drupal.color.callback(context, settings, form, farb, height, width);
          }
          else {
            // Remove the background image.
            $('#preview-header').css('background-image', 'none');
          }
        });
        this.initialized = true;
      }

      var elements = {
        white: {
          color: [],
          background: []
        },
        very_light_gray: {
          color: [],
          background: ['#preview-main']
        },
        light_gray: {
          color: [],
          background: ['#preview-content']
        },
        medium_gray: {
          color: [],
          background: ['#preview-sidebar']
        },
        dark_gray: {
          color: [],
          background: []
        },
        light_blue: {
          color: [],
          background: ['.tabs a.inactive']
        },
        dark_blue: {
          color: ['a.preview-link'],
          background: ['.tabs a.active']
        },
        deep_blue: {
          color: [],
          background: ['#preview-header', '#preview-footer']
        },
        leaf_green: {
          color: [],
          background: ['a.action-element']
        },
        blood_red: {
          color: [],
          background: ['a.danger-element']
        }
      };

      for (var color in elements) {
        var colorHex = $('#palette input[name="palette[' + color + ']"]', form).val();
        for (var i = 0, len = elements[color].color.length; i < len; i++) {
          $(elements[color].color[i], form).css('color', colorHex);
        }
        for (var i = 0, len = elements[color].background.length; i < len; i++) {
          $(elements[color].background[i], form).css('background-color', colorHex);
        }
      }
    }
  };

})(jQuery, Drupal);
