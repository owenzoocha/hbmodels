(function ($) {

  var models_nav = {
    init: function(context) {
      $('#block-views-user-profile-jobs-block .view-content, #block-views-user-profile-jobs-block-1 .view-content').slick({
        dots: true,
        infinite: true,
        speed: 500,
        slidesToShow: 4,
        slidesToScroll: 4,
      });
    }
  }

  Drupal.behaviors.models_nav = {
    attach: function(context) {
      $('body', context).once(function () {
        models_nav.init();
      });
    }
  };

})(jQuery);
