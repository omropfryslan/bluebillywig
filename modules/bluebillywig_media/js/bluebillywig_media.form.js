/**
 * @file
 * Checks whether the thumbnail is loaded, otherwise hide the broken image.
 */

(function ($) {
  Drupal.behaviors.bluebillywig_media = {
    attach: function (context, settings) {
      $('img').each(function () {
        $(this).error(function () {
          $(this).hide();
        });
      });
    }
};
})(jQuery);
