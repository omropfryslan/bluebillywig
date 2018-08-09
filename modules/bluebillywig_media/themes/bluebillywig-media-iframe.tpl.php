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

// If set add microdata, so search engines and web-crawlers are provided with extra information about the media.
echo $microdata;
?>
<div class="<?php print $classes; ?> bluebillywig-media-<?php print $id; ?>">
<iframe onload="this.src += '#!referrer='+encodeURIComponent(location.href)" src="<?php print $iframeUrl . (!empty($qs) ? '?' . http_build_query($qs) : ''); ?>" width="<?php print $width; ?>" height="<?php print $height; ?>"  frameborder="0" webkitallowfullscreen mozallowFullscreen oallowFullscreen msallowFullscreen allowfullscreen ></iframe>
</div>
