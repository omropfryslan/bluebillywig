/**
 * Blue billywig video callback.
 */
function bbw_thumbnailer_init(player) {
  var content = player.getContentLayer();
  var video = content.querySelector('video');

  // Make video element CORS-proof.
  video.setAttribute('crossOrigin', 'Anonymous');

  var thumbnail = document.querySelector('.bluebillywig-media-thumbnail-image');
  player.on('playing', function() {
    thumbnail.classList.add('playing');
  });

  player.on('ended', function() {
    thumbnail.classList.remove('playing');
  });
}

(function ($) {
  /**
   * Initiate bluebillywig thumbnailer.
   */
  Drupal.behaviors.bluebillywig_thumbnailer = {
    attach: function (context) {
      var lastFile = false;

      $('.bluebillywig-media-thumbnail-image', context).on('click', function() {
        var $this = $(this);
        var player_wrapper = $('.bb_wrapper', $this.parent());

        var $video = player_wrapper.find('video');
        var video = $video[0];

        var up = $('.plupload-element').pluploadQueue();
        var files = [];

        video.pause();

        var blob = getThumbAsBlob(video, 'image/jpeg');
        blob.name = 'Thumbnail-' + Date.now() + '.jpg';
        blob.type = 'image/jpeg';

        // https://stackoverflow.com/a/11750546
        up.addFiles([blob]);

        if (up.files.length > 1) {
          up.removeFile(up.files[0]);
        }

        lastFile = files[0];

        $('.bluebillywig-media-thumbnail-flash')
         .show()
         .animate({opacity: 0.5}, 300)
         .fadeOut(300)
         .css({'opacity': 1});
      });

      /**
       * Create blob from video element.
       */
      function getThumbAsBlob(video, type) {
        // Create canvas from video element.
        var w = video.videoWidth;
        var h = video.videoHeight;

        var canvas = document.createElement('canvas');
        canvas.width = w;
        canvas.height = h;

        var ctx = canvas.getContext('2d');
        ctx.drawImage(video, 0, 0, w, h);

        // Save canvas as DataURI.
        var dataURI = canvas.toDataURL(type);

        // Reference: https://stackoverflow.com/q/4998908.

        // Get bytestring.
        var byteString;
        if (dataURI.split(',')[0].indexOf('base64') >= 0) {
          byteString = atob(dataURI.split(',')[1]);
        } else {
          byteString = encodeURI(dataURI.split(',')[1]);
        }

        // Separate out the mime component.
        var mimeString = dataURI.split(',')[0].split(':')[1].split(';')[0];

        // Write the bytes of the string to a typed array.
        var intArray = new Uint8Array(byteString.length);
        for (var i = 0; i < byteString.length; i++) {
          intArray[i] = byteString.charCodeAt(i);
        }

        return new Blob([intArray], {type:mimeString});
      }
    }
  };
})(jQuery);
