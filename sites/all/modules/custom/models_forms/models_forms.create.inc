<?php

/**
 * @file
 * Provides form functionality to create events.
 */

/**
 * Implements hook_form().
 * Provides functionality to create an event.
 */
function models_forms_create_form($form, &$form_state) {
  global $user;

  if (arg(2) == 'edit') {
    if (is_numeric(arg(1))) {
      $nw = entity_metadata_wrapper('node', arg(1));
      if ($nw->value()) {
        drupal_set_title('Edit' . ' ' . $nw->label());
        drupal_set_title($nw->label() . ' - Update');

        $title = $nw->label();
        $notes = $nw->body->value() ? $nw->body->value()['value'] : FALSE;
        $hb_type = $nw->field_hb_type->value() ? $nw->field_hb_type->value() : FALSE;

        $form_state['job_update'] = $nw->getIdentifier();
        drupal_add_js(array('form_type' => $hb_type), 'setting');

        if ($nw->field_hb_gender->value()) {
          $field_hb_gender = array();
          foreach ($nw->field_hb_gender->getIterator() as $k => $v) {
            $field_hb_gender[] = $v->value();
          }
        }
        if ($nw->field_hb_ht->value()) {
          $field_hb_ht = array();
          foreach ($nw->field_hb_ht->getIterator() as $k => $v) {
            $field_hb_ht[] = $v->value();
          }
        }
        if ($nw->field_hb_ht_colour->value()) {
          $field_hb_ht_colour = array();
          foreach ($nw->field_hb_ht_colour->getIterator() as $k => $v) {
            $field_hb_ht_colour[] = $v->value();
          }
        }
        if ($nw->field_hb_ht_cut->value()) {
          $field_hb_ht_cut = array();
          foreach ($nw->field_hb_ht_cut->getIterator() as $k => $v) {
            $field_hb_ht_cut[] = $v->value();
          }
        }
        if ($nw->field_hb_bt->value()) {
          $field_hb_bt = array();
          foreach ($nw->field_hb_bt->getIterator() as $k => $v) {
            $field_hb_bt[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_makeup->value()) {
          $field_hb_bt_makeup = array();
          foreach ($nw->field_hb_bt_makeup->getIterator() as $k => $v) {
            $field_hb_bt_makeup[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_eyelashes->value()) {
          $field_hb_bt = array();
          foreach ($nw->field_hb_bt->getIterator() as $k => $v) {
            $field_hb_bt_eyelashes[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_eyebrows->value()) {
          $field_hb_bt_eyebrows = array();
          foreach ($nw->field_hb_bt_eyebrows->getIterator() as $k => $v) {
            $field_hb_bt_eyebrows[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_nails->value()) {
          $field_hb_bt_nails = array();
          foreach ($nw->field_hb_bt_nails->getIterator() as $k => $v) {
            $field_hb_bt_nails[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_waxing->value()) {
          $field_hb_bt_waxing = array();
          foreach ($nw->field_hb_bt_waxing->getIterator() as $k => $v) {
            $field_hb_bt_waxing[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_makeup->value()) {
          $field_hb_bt_makeup = array();
          foreach ($nw->field_hb_bt_makeup->getIterator() as $k => $v) {
            $field_hb_bt_makeup[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_facials->value()) {
          $field_hb_bt_facials = array();
          foreach ($nw->field_hb_bt_facials->getIterator() as $k => $v) {
            $field_hb_bt_facials[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_massage->value()) {
          $field_hb_bt_massage = array();
          foreach ($nw->field_hb_bt_massage->getIterator() as $k => $v) {
            $field_hb_bt_massage[] = $v->value();
          }
        }
        if ($nw->field_hb_bt_tanning->value()) {
          $field_hb_bt_tanning = array();
          foreach ($nw->field_hb_bt_tanning->getIterator() as $k => $v) {
            $field_hb_bt_tanning[] = $v->value();
          }
        }

        $date = $nw->field_hb_time->value() ? format_date($nw->field_hb_time->value(), 'custom', 'Y-m-d H:i:s') : FALSE;
        // $file = $nw->field_e_image->value() ? $nw->field_e_image->value()['fid'] : FALSE;
        $dependent_locality = $nw->field_hb_location->value()['dependent_locality'] ? $nw->field_hb_location->value()['dependent_locality'] : FALSE;
        $thoroughfare = $nw->field_hb_location->value()['thoroughfare'] ? $nw->field_hb_location->value()['thoroughfare'] : FALSE;
        $premise = $nw->field_hb_location->value()['premise'] ? $nw->field_hb_location->value()['premise'] : FALSE;
        $locality = $nw->field_hb_location->value()['locality'] ? $nw->field_hb_location->value()['locality'] : FALSE;
        $administrative_area = $nw->field_hb_location->value()['administrative_area'] ? $nw->field_hb_location->value()['administrative_area'] : FALSE;
        $postal_code = $nw->field_hb_location->value()['postal_code'] ? $nw->field_hb_location->value()['postal_code'] : FALSE;
        $country = $nw->field_hb_location->value()['country'] ? $nw->field_hb_location->value()['country'] : 'AU';
      }
    }
  }

  // $form['#attached']['js'] = 'https://cdnjs.cloudflare.com/ajax/libs/nanobar/0.2.1/nanobar.min.js, 'external');array(
  //   drupal_get_path('module', 'km_forms') . '/js/km_forms.js',
  // );
  // $repos = field_info_field('field_doc_repo_type');
  // $allowed_values = list_allowed_values($repos);
  // $form['repo'] = array(
  //   '#type' => 'select',
  //   '#options' => $allowed_values,
  //   '#chosen' => TRUE,
  //   '#multiple' => TRUE,
  //   '#title' => 'Select repo(s)',
  //   '#description' => 'Select the repo(s) you wish your tag(s) to be added.',
  // );
  // Grab a list of clients created by global user - or 'admin user' of group.
  // $query = new EntityFieldQuery();
  // $query->entityCondition('entity_type', 'client')
  //   ->entityCondition('bundle', 'client')
  //   ->propertyCondition('uid', $user->uid)
  //   ->propertyOrderBy('title', 'ASC');
  // $results = $query->execute();

  // if (count($results['client'])) {
  //   $clients = array();
  //   foreach ($results['client'] as $key => $tid) {
  //     $ew = entity_metadata_wrapper('client', $key);
  //     $clients[$ew->getIdentifier()] = $ew->label();
  //   }
  // }

  $form['#attached']['js'] = array(
    'https://cdnjs.cloudflare.com/ajax/libs/nanobar/0.2.1/nanobar.min.js' => array(
      'type' => 'external',
    ),
    'https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/js/bootstrap-datetimepicker.min.js' => array(
      'type' => 'external',
    ),
    drupal_get_path('module', 'models_forms') . '/js/models_forms.js',
  );

  $form['#attached']['css'] = array(
    'https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datetimepicker/4.17.37/css/bootstrap-datetimepicker.min.css' => array(
      'type' => 'external',
    ),
  );

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => isset($title) ? t('Edit Job') : t('Post a Job'),
  );

  $form['wrapper']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Job title'),
    '#default_value' => isset($title) ? $title : FALSE,
    '#required' => TRUE,
  );

  $type = field_info_field('field_hb_gender');
  $options = list_allowed_values($type);
  $form['wrapper']['field_hb_gender'] = array(
    '#type' => 'select',
    '#title' => t('Who\'s it for?'),
    '#description' => t('You can select multiple.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_gender) ? $field_hb_gender : FALSE,
    // '#disabled' => isset($hb_type) ? TRUE : FALSE,
    // '#required' => TRUE,
  );

  $type = field_info_field('field_hb_type');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_type'] = array(
    '#type' => 'select',
    '#title' => t('What kind of Job is it?'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#default_value' => isset($hb_type) ? $hb_type : FALSE,
    '#disabled' => isset($hb_type) ? TRUE : FALSE,
    '#required' => TRUE,
  );

  // HAIR --------------------------------------------------
  // If HAIR was selected - commence the following:
  $type = field_info_field('field_hb_ht');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht'] = array(
    '#type' => 'select',
    '#title' => t('Select hair treatment type'),
    '#description' => t('You can select multiple hair treatment types.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_ht) ? $field_hb_ht : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht" class=" hide-hair">',
    '#suffix' => '</div>',
  );

  // If HAIR - COLOUR was selected - commence the following:
  $type = field_info_field('field_hb_ht_colour');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht_colour'] = array(
    '#type' => 'select',
    '#title' => t('Hair colour type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_ht_colour) ? $field_hb_ht_colour : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht_colour" class="hide-me hide-hair">',
    '#suffix' => '</div>',
  );

  // If HAIR - CUT was selected - commence the following:
  $type = field_info_field('field_hb_ht_cut');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_ht_cut'] = array(
    '#type' => 'select',
    '#title' => t('Hair cut type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_ht_cut) ? $field_hb_ht_cut : FALSE,
    '#prefix' => '<div id="hbf-field_hb_ht_cut" class="hide-me hide-hair">',
    '#suffix' => '</div>',
  );

  // BEAUTY --------------------------------------------------
  // If BEAUTY was selected - commence the following:
  $type = field_info_field('field_hb_bt');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt'] = array(
    '#type' => 'select',
    '#title' => t('Select beauty treatment type'),
    '#description' => t('You can select multiple beauty treatment types.'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_bt) ? $field_hb_bt : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt" class="hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - MAKEUP was selected - commence the following:
  $type = field_info_field('field_hb_bt_makeup');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_makeup'] = array(
    '#type' => 'select',
    '#title' => t('Makeup type'),
    '#options' => $options,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#default_value' => isset($field_hb_bt_makeup) ? $field_hb_bt_makeup : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_makeup" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - EYELASHES was selected - commence the following:
  $type = field_info_field('field_hb_bt_eyelashes');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_eyelashes'] = array(
    '#type' => 'select',
    '#title' => t('Eyelashes type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_eyelashes) ? $field_hb_bt_eyelashes : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_eyelashes" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - EYEBROWS was selected - commence the following:
  $type = field_info_field('field_hb_bt_eyebrows');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_eyebrows'] = array(
    '#type' => 'select',
    '#title' => t('Eyebrows type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_eyebrows) ? $field_hb_bt_eyebrows : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_eyebrows" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - NAILS was selected - commence the following:
  $type = field_info_field('field_hb_bt_nails');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_nails'] = array(
    '#type' => 'select',
    '#title' => t('Nails type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_nails) ? $field_hb_bt_nails : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_nails" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - WAXING was selected - commence the following:
  $type = field_info_field('field_hb_bt_waxing');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_waxing'] = array(
    '#type' => 'select',
    '#title' => t('Hair Removal type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_waxing) ? $field_hb_bt_waxing : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_waxing" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - FACIALS was selected - commence the following:
  $type = field_info_field('field_hb_bt_facials');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_facials'] = array(
    '#type' => 'select',
    '#title' => t('Facials type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_facials) ? $field_hb_bt_facials : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_facials" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // If BEAUTY - MASSAGE was selected - commence the following:
  $type = field_info_field('field_hb_bt_massage');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_massage'] = array(
    '#type' => 'select',
    '#title' => t('Massage type'),
    '#options' => $options,
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_massage) ? $field_hb_bt_massage : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_massage" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );
  // If BEAUTY - TANNING was selected - commence the following:
  $type = field_info_field('field_hb_bt_tanning');
  $options = list_allowed_values($type);
  $form['wrapper']['hbf_field_hb_bt_tanning'] = array(
    '#type' => 'select',
    '#title' => t('Tanning type'),
    '#multiple' => TRUE,
    '#options' => $options,
    '#chosen' => TRUE,
    '#default_value' => isset($field_hb_bt_tanning) ? $field_hb_bt_tanning : FALSE,
    '#prefix' => '<div id="hbf-field_hb_bt_tanning" class="hide-me hide-beauty">',
    '#suffix' => '</div>',
  );

  // STEP 2 ---------------
  $form['wrapper']['extra_info_btn'] = array(
    '#markup' => '<div id="step-extra-btn" class="text-center"><btn class="btn btn-sm btn-success"><i class="fa fa-angle-down"></i> Continue</button></div>',
  );

  $form['wrapper']['step2_start'] = array(
    '#markup' => '<div id="step-extra">',
  );

  $form['wrapper']['notes'] = array(
    '#type' => 'textarea',
    '#title' => t('Notes'),
    '#maxlength' => 350,
    '#maxlength_js' => TRUE,
    '#default_value' => isset($notes) ? $notes : FALSE,
    '#description' => t('Tell us about your job.'),
  );

  $form['wrapper']['date'] = array(
    '#type' => 'textfield',
    '#title' => 'Date/Time',
    '#description' => t('Tell us the date and time for the job.'),
    '#value' => isset($date) ? $date : FALSE,
  );

  // https://www.drupal.org/node/970048
  $form['wrapper']['location'] = array (
    '#type' => 'addressfield',
    '#title' => t('Location'),
    // '#description' => t('Location of the job.'),
    '#required' => FALSE,
    '#chosen' => TRUE,
    '#default_widget' => 'addressfield_standard',
    '#default_formatter' => 'addressfield_default',
    '#default_value' => array (
      'dependent_locality ' => isset($dependent_locality) ? $dependent_locality : FALSE,
      'thoroughfare' =>  isset($thoroughfare) ? $thoroughfare : FALSE,
      'premise' => isset($premise) ? $premise : FALSE,
      'locality' => isset($locality) ? $locality : FALSE,
      'administrative_area' => isset($administrative_area) ? $administrative_area : FALSE,
      'postal_code' => isset($postal_code) ? $postal_code : FALSE,
      'country' => 'AU',
    ),
    '#available_countries' => array('AU'),
  );

  // $form['wrapper']['img'] = array(
  //   '#type' => 'managed_file',
  //   '#default_value' => isset($file) ? $file : FALSE,
  //   '#title' => t('Attachments'),
  //   '#description' => t('Upload an event image'),
  //   '#upload_validators' => array(
  //     'file_validate_extensions' => array('jpg jpeg png'),
  //     'file_validate_size' => array(5000000),
  //   ),
  //   '#upload_location' => 'public://',
  // );

  $form['wrapper']['submit'] = array(
    '#type' => 'submit',
    '#value' => isset($hb_type) ? t('Update Job') : t('Post Job'),
    // '#disabled' => sizeof($nw->field_t_users->value()) <= $fbk_size ? TRUE : FALSE,
    '#attributes' => array(
      // 'class' => !isset($requested) ? array('btn-success') : array('btn-danger'),
      'class' => array('btn-success'),
      'data-loading-text' => isset($hb_type) ? array("Updating..") : array("Posting.."),
      'data-complete-text' => array('Saved!'),
    ),
    '#prefix' => '<div id="step-submit">',
    '#suffix' => '</div>',
  );

  $form['wrapper']['step2_end'] = array('#markup' => '</div>');

  return $form;
}

/**
 * Custom submit function for models_forms_create_form_submit.
 */
function models_forms_create_form_submit(&$form, &$form_state){
  global $user;

  $fs = $form_state['values'];

  if (!isset($form_state['job_update'])) {
    $node = new stdClass();
    $node->type = "job";
    $node->create = strtotime('now');
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->status = 0;
  } else {
    $node = node_load($form_state['job_update']);
    $node->updated = strtotime('now');
    unset($node->field_hb_gender[LANGUAGE_NONE]);
    unset($node->field_hb_ht[LANGUAGE_NONE]);
    unset($node->field_hb_ht_colour[LANGUAGE_NONE]);
    unset($node->field_hb_ht_cut[LANGUAGE_NONE]);
    unset($node->field_hb_bt[LANGUAGE_NONE]);
    unset($node->field_hb_bt_makeup[LANGUAGE_NONE]);
    unset($node->field_hb_bt_eyelashes[LANGUAGE_NONE]);
    unset($node->field_hb_bt_eyebrows[LANGUAGE_NONE]);
    unset($node->field_hb_bt_nails[LANGUAGE_NONE]);
    unset($node->field_hb_bt_waxing[LANGUAGE_NONE]);
    unset($node->field_hb_bt_facials[LANGUAGE_NONE]);
    unset($node->field_hb_bt_massage[LANGUAGE_NONE]);
    unset($node->field_hb_bt_tanning[LANGUAGE_NONE]);
  }

  $node->title = $fs['title'];

  $type = $fs['hbf_field_hb_type'];
  if (!empty($type)) {
    $node->field_hb_type[LANGUAGE_NONE][0]['value'] = $type;

    if(!empty($fs['field_hb_gender'])){
      foreach ($fs['field_hb_gender'] as $k => $v) {
        $node->field_hb_gender[LANGUAGE_NONE][]['value'] = $v;
      }
    }

    if ($type == 'hair') {
      if(!empty($fs['hbf_field_hb_ht'])){
        foreach ($fs['hbf_field_hb_ht'] as $k => $v) {
          $node->field_hb_ht[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_ht_colour'])){
        foreach ($fs['hbf_field_hb_ht_colour'] as $k => $v) {
          $node->field_hb_ht_colour[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_ht_cut'])){
        foreach ($fs['hbf_field_hb_ht_cut'] as $k => $v) {
          $node->field_hb_ht_cut[LANGUAGE_NONE][]['value'] = $v;
        }
      }
    }

    if ($type == 'beauty') {
      if(!empty($fs['hbf_field_hb_bt'])){
        foreach ($fs['hbf_field_hb_bt'] as $k => $v) {
          $node->field_hb_bt[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_makeup'])){
        foreach ($fs['hbf_field_hb_bt_makeup'] as $k => $v) {
          $node->field_hb_bt_makeup[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_eyelashes'])){
        foreach ($fs['hbf_field_hb_bt_eyelashes'] as $k => $v) {
          $node->field_hb_bt_eyelashes[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_eyebrows'])){
        foreach ($fs['hbf_field_hb_bt_eyebrows'] as $k => $v) {
          $node->field_hb_bt_eyebrows[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_nails'])){
        foreach ($fs['hbf_field_hb_bt_nails'] as $k => $v) {
          $node->field_hb_bt_nails[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_waxing'])){
        foreach ($fs['hbf_field_hb_bt_waxing'] as $k => $v) {
          $node->field_hb_bt_waxing[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_facials'])){
        foreach ($fs['hbf_field_hb_bt_facials'] as $k => $v) {
          $node->field_hb_bt_facials[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_massage'])){
        foreach ($fs['hbf_field_hb_bt_massage'] as $k => $v) {
          $node->field_hb_bt_massage[LANGUAGE_NONE][]['value'] = $v;
        }
      }
      if(!empty($fs['hbf_field_hb_bt_tanning'])){
        foreach ($fs['hbf_field_hb_bt_tanning'] as $k => $v) {
          $node->field_hb_bt_tanning[LANGUAGE_NONE][]['value'] = $v;
        }
      }
    }
  }

  // Body.
  if(!empty($fs['notes'])){
    $node->body[LANGUAGE_NONE][0]['value'] = $fs['notes'];
  }

  // Date.
  if(!empty($fs['date'])){
    $date = format_date(strtotime( str_replace('/', '-', $fs['date'])), 'custom', 'Y-m-d H:i:s', 'UTC');
    $node->field_hb_time[LANGUAGE_NONE][0]['value'] = $date;
  }

  // Location.
  if(!empty($fs['location'])){
    $node->field_hb_location[LANGUAGE_NONE][0]['thoroughfare'] = $fs['location']['thoroughfare'] ? $fs['location']['thoroughfare'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['premise'] = $fs['location']['premise'] ? $fs['location']['premise'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['dependent_locality'] = $fs['location']['dependent_locality'] ? $fs['location']['dependent_locality'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['locality'] = $fs['location']['locality'] ? $fs['location']['locality'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['administrative_area'] = $fs['location']['administrative_area'] ? $fs['location']['administrative_area'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['postal_code'] = $fs['location']['postal_code'] ? $fs['location']['postal_code'] : FALSE;
    $node->field_hb_location[LANGUAGE_NONE][0]['country'] = $fs['location']['country'] ? $fs['location']['country'] : FALSE;
  }

  node_save($node);
  if (!isset($form_state['job_update'])) {
    drupal_set_message(t('Your Job: ' . $fs['title'] . ' has been posted '), 'info', FALSE);
  }
  else {
    drupal_set_message(t('Your Job: ' . $fs['title'] . ' has been updated '), 'success', FALSE);
  }
  drupal_goto('node/' .$node->nid);
}

  // // Client.
  // if(!empty($fs['client'])){
  //   // Make new client entity.
  //   $ew = entity_create('client', array('type' => 'client'));
  //   $ew->title = strtolower($fs['client']);
  //   $ew->created = strtotime('now');
  //   $ew->changed = strtotime('now');
  //   $ew->uid = $user->uid;
  //   $ew->save();
  //   $node->field_e_client[LANGUAGE_NONE][0]['target_id'] = $ew->id;
  // }
  // File.
  // if(!empty($fs['img'])){
  //   $file = file_load($fs['img']);
  //   $node->field_e_image = array (
  //     LANGUAGE_NONE => array (
  //       0 => array (
  //         'fid' => $file->fid,
  //         'filename' => $file->filename,
  //         'filemime' => $file->filemime,
  //         'uid' => 1,
  //         'uri' => $file->uri,
  //         'status' => 1,
  //         'display' => 1
  //       )
  //     )
  //   );
  // }
