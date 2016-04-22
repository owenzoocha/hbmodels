<?php

/**
 * @file models_imgs.uploader.inc.
 */

/**
 * Provides functionality to handle dropzone js uploads.
 */
function models_imgs_upload_page() {
  global $user;
  if (!empty($_GET['nid'])) {
    if (!empty($_FILES)) {

      $nw = entity_metadata_wrapper('node', $_GET['nid']);

      $i = 0;
      foreach ($_FILES['files']['name'] as $key => $file) {

        $uri = 'public://job_imgs/' . $nw->getIdentifier();
        file_prepare_directory($uri, FILE_CREATE_DIRECTORY);
        $path = drupal_realpath($uri);

        $src = $_FILES['files']['tmp_name'][$key];
        $file_name = $nw->getIdentifier()  . '_' . strtotime('now') . '_' . transliteration_clean_filename($file);
        $destination = $path . '/' . $file_name;

        $ew = entity_create('pics', array('type' => 'pics'));
        $title = 'pics_' . $i . '_' . $nw->getIdentifier() . '_' . $nw->label();
        $ew->title = $title;
        $ew->created = strtotime('now');
        $ew->changed = strtotime('now');

        move_uploaded_file($src, $destination);

        // if ($nw->field_hb_imgs->value()) {
        //   // do something..
        // }
        // else {
          $fs = filesize($destination);
          $file = array(
            'uid' => $user->uid,
            'uri' => $uri . '/' . $file_name,
            'filemime' => file_get_mimetype($destination),
            'status' => 1,
            'filesize' => $fs,
            'filename' => $file_name,
            'display' => 1,
          );
        // }
        // dpm($file, 'fileez');

        $file = file_save((object) $file);
        $ew->field_pics_img[LANGUAGE_NONE][0] = (array) $file;
        $ew->save();
        $i++;

        // dpm($ew, 'eid');

        $nw->field_hb_pics[] = $ew->id;
      }

      // dpm($nw->value());
      $nw->save();
    }
  }
}
