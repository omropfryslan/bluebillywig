<?php
/**
 * @file Media_vimeo/themes/bluebillywig-media-video.tpl.php.
 *
 * Template file for theme('media_billywig_video').
 *
 * Variables available:
 *  $uri - The media uri for the Blue Billywig video.
 *  $url - The full javascript embed url src for the Blue Billywig video.
 *  $clip_id - The unique identifier of the Blue Billywig video within the chosen bb publication.
 *  $contextIdentifier - c for clip, l for cliplist, q for query
 *  $id - The file entity ID (fid).
 *  $width - The width value set in Media: Blue Billywig file display options.
 *  $height - The height value set in Media: Blue Billywig file display options.
 *  $title - The Media: Blue Billywig clip title.
 */

// @TODO, add other properties to the qs, like autoplay.
$qs = array();

if($width > 0) {
  $qs['width'] = $width;
}
if($height > 0) {
  $qs['height'] = $height;
}
if($autoplay == 1) {
  $qs['autoPlay'] = 'true';
}

$qs['autoPlay'] = 'false';
$qs['callback'] = 'bbw_thumbnailer_init';
$qs['controlBar'] = 'Show';
$qs['noStats'] = 'true';
$qs['relatedItems'] = 'Hide';
$qs['autoMute'] = 'true';
$qs['fitmode'] = 'FIT_SMART';
$qs['title'] = 'hide';
?>

<div class="<?php print $classes; ?> bluebillywig-media-<?php print $id; ?>">
  <div class="bluebillywig-media-thumbnail-wrapper">
    <?php echo $microdata; ?>
    <script crossOrigin="Anonymous" src="<?php print $url . (!empty($qs) ? '?' . http_build_query($qs) : '') ?>" type="text/javascript" async></script>
  </div>
  <div class="bluebillywig-media-thumbnail-image">
    <div class="bluebillywig-media-thumbnail-image-camera">
      <span class="bluebillywig-thumbnailer-icon-camera-retro"></span>
    </div>
  </div>
  <div class="bluebillywig-media-thumbnail-flash"></div>
</div>
