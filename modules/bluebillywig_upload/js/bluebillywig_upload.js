/**
 * @file
 * Handle BeforeUpload: ingest original filename into the multipart form.
 */

jQuery(document).ready(function () {
var myUploader = jQuery('.plupload-element').pluploadQueue();

// Bind on queue changed event to disable more than 1 upload.
 myUploader.bind('QueueChanged', function () {
    var add_button = jQuery('.plupload_button.plupload_add');
        var local_uploader_element = this;
        // Remove files exceeding the cardinality setting.
        if (local_uploader_element.files.length >= 1) {
          var i = 0;
          for (i = 0; i < local_uploader_element.files.length; i++) {
            if (i >= 1) {
              myUploader.removeFile(myUploader.files[i]);
            }
          }
      add_button.hide();
        }
    else {
      add_button.show();
    }
  });

 myUploader.bind('BeforeUpload', function (up, file) {
    up.settings.multipart_params = {"originalfilename": file.name };
    jQuery('#edit-bb-mc-originalfilename').val(file.name);
   });
 myUploader.bind('FileUploaded', function (up, file, response) {
        var vmsResponse;
        try {
           vmsResponse = eval(response.response);
        }
catch (err) {
           vmsResponse = eval('(' + response.response + ')');
        }
        if (vmsResponse != undefined) {
          jQuery('#edit-bb-mc-id').val(vmsResponse.id);
          // Enable save button now.
                  jQuery('#edit-bb-mc-save').removeAttr('disabled');
                  jQuery('#edit-bb-mc-save').attr('class','form-submit');
          // If autosave is checked, we call bluebillywig_upload_metadata.
          if (jQuery('#edit-bb-mc-save-on-uploaded').attr('checked')) {
             bluebillywig_upload_metadata();
          }
          // As we have a successful upload, we don't need the autosave option anymore. disable it.
          jQuery('#edit-bb-mc-save-on-uploaded').attr('disabled','disabled');
        }
        });
});


function bluebillywig_upload_metadata() {
   var vmsClip;
   var myUploader = jQuery('.plupload-element').pluploadQueue();
   if (myUploader != undefined) {
      var vmsUploadUrl = myUploader.settings.url;
      // Gather metadata fields and POST them to the VMS
      // if we have an ID that is...
      var numericReg = /^\d*[0-9](|.\d*[0-9]|,\d*[0-9])?$/;
      if (numericReg.test(jQuery('#edit-bb-mc-id').val())) {
    var objClip = new Object();
    objClip.id = jQuery('#edit-bb-mc-id').val();
    if (jQuery('#edit-bb-mc-title').val()) {
       objClip.title = jQuery('#edit-bb-mc-title').val();
        }
    objClip.status = jQuery('input[name=bb_mc_status]:checked').val();
    objClip.description = jQuery('#edit-bb-mc-description').val();
    objClip.cat = jQuery('#edit-bb-mc-tags').val().split(/\n|\r/);
    var strClip = JSON.stringify(objClip);
    jQuery.ajax({
            url: vmsUploadUrl,
            type: "POST",
            data: {"clipData": strClip},
            async: false,
        success: function (data) {
            // Display the message from successful response.
            jQuery("#edit-bb-mc-save").after('<div id="bb-mc-statusmsg" class="messages status">Clip metadata saved</div>');
        // Select the newly uploaded clip in the media-browser.
        var uri = jQuery('input[name=bb_uri_prefix]').val() + objClip.id + '.js';
        jQuery("input[name='submitted-video']").val(uri);
        jQuery("#edit-submit").click();
            },
        error: function (request, status, error) {
            alert(request.responseText);
            },
         });
       }
      else {
      }
    }
   return false;
}
