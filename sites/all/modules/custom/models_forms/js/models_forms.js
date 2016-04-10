(function ($) {

  var hbmf = {
    nanobar : false,

    init: function(context) {
      var options = {
        bg: 'yellow',
        id: 'mynano'
      };
      hbmf.nanobar = new Nanobar( options );
      hbmf.formSubmit();

      var dateInput = $("#edit-date");
      dateInput.parent().css("position", "relative");

      var dd = moment("31/05/2016 09:00", "DD/MM/YYYY HH:mm");
      var dd2 = "31/05/2016 09:00";
      dateInput.datetimepicker({
        format: 'DD/MM/YYYY HH:mm',
        defaultDate: dd,
        minDate: moment(),
        maxDate: moment().add(1, 'year'),
      });
      // dateInput.data("DateTimePicker").defaultDate("31/05/2016 09:00")

console.log(Drupal.settings.form_type);
      if (!Drupal.settings.form_type) {
        hbmf.formSelectType();
        hbmf.formSelectHairType();
        hbmf.formSelectBeautyType();
        hbmf.formExtraInfo();
        $('#edit-location-country').attr('disabled', 'disabled');
        $("#edit-location-administrative-area, #edit-location-country").chosen();

        if (!$('.has-error').length) {
          $('#hbf-field_hb_ht, #hbf-field_hb_bt, .hide-hair, .hide-beauty, #step-extra, #step-extra-btn').hide();
        } else {
          $('.hide-hair, .hide-beauty').hide();
          var jobType = $('#edit-hbf-field-hb-type option:selected').val();
          if (jobType == 'hair') {
            $('.hide-hair').show();
          }
          if (jobType == 'beauty') {
            $('.hide-beauty').show();
          }
        }
      } else {
        if (Drupal.settings.form_type == 'hair') {
          $('.hide-beauty, #step-extra-btn').hide();
        } else {
          $('.hide-hair, #step-extra-btn').hide();
        }
      }

      $('.btn').on('click', function () {
        var $btn = $(this).button('loading');
        setTimeout(function(){
          $btn.button('reset');
        }, 500);
      })

    },

    formSelectType : function() {
      $('#edit-hbf-field-hb-type').change(function() {
        $('.hide-beauty, .hide-hair').hide();
        hbmf.nanobar.go(100);

        if ( $(this).find('option:selected').val() == 'hair' ) {
          setTimeout(function(){
            $('#hbf-field_hb_ht').fadeIn();
          }, 500);
        }
        if ( $(this).find('option:selected').val() == 'beauty' ) {
          setTimeout(function(){
            $('#hbf-field_hb_bt').fadeIn();
          }, 500);
        }
        if ( !$(this).find('option:selected').val() ) {
          $('#hbf-field_hb_ht, #hbf-field_hb_bt').hide();
        }
      });

    },

    formSelectHairType : function() {
      $('#edit-hbf-field-hb-ht').change(function() {
        hbmf.nanobar.go(100);

        setTimeout(function(){
          $('#step-extra-btn').fadeIn();
        }, 1000);

        $.each($(this).find('option:selected'), function(i, v){
          if ($(this).val() == 'Colour') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_ht_colour').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Cut') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_ht_cut').fadeIn();
            }, 500);
          }
        });
      });
    },

    formSelectBeautyType : function() {
      $('#edit-hbf-field-hb-bt').change(function() {
        hbmf.nanobar.go(100);

        setTimeout(function(){
          $('#step-extra-btn').fadeIn();
        }, 500);

        $.each($(this).find('option:selected'), function(i, v){
          if ($(this).val() == 'Make Up') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_makeup').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Eyelashes') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_eyelashes').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Eyebrows') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_eyebrows').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Nails') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_nails').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Hair Removal') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_waxing').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Facial') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_facials').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Massage') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_massage').fadeIn();
            }, 500);
          }
          if ($(this).val() == 'Tanning') {
            $('.hide-me').hide();
            setTimeout(function(){
              $('#hbf-field_hb_bt_tanning').fadeIn();
            }, 500);
          }
        });
      });
    },

    formExtraInfo : function(){
      $('#step-extra-btn').on('click', function(){
        hbmf.nanobar.go(100);
        setTimeout(function(){
          $('#step-extra').slideDown();
        }, 500);
      });
    },

    formSubmit : function(){
      $('#models-forms-create-form').submit(function(){
        console.log('here!');
        hbmf.nanobar.go(30);
        setTimeout(function(){
          hbmf.nanobar.go(100);
          // setTimeout(function(){
          //   hbmf.nanobar.go(100);
          // }, 200);
        }, 1000);
      });
    }
  }

  Drupal.behaviors.hbmf = {
    attach: function(context) {
      $('body', context).once(function () {
        hbmf.init();
      });
    }
  };

})(jQuery);
