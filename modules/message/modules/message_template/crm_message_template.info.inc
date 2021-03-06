<?php

/**
 * @file
 */

/**
 * Implements hook_entity_property_info().
 */
function crm_message_template_entity_property_info() {
  $info = array();
  $properties = &$info['crm_message_template']['properties'];

  $default_properties = array(
    'setter callback' => 'entity_property_verbatim_set',
    'getter callback' => 'entity_property_verbatim_get',
  );

  $properties['is_new'] = array(
      'label' => t('Is new'),
      'type' => 'boolean',
      'description' => t('Whether the entity is new and not saved to the database yet.'),
    ) + $default_properties;
  $properties['template_id'] = array(
    'label' => t('Message_template ID'),
    'type' => 'integer',
    'schema field' => 'template_id',
    'getter callback' => 'entity_property_verbatim_get',
  );
  $properties['revision_id'] = array(
    'label' => t("Revision ID"),
    'type' => 'integer',
    'description' => t("The unique ID of the node's revision."),
    'schema field' => 'revision_id',
  );
  $properties['name'] = array(
      'label' => t('Name'),
      'description' => t('One time token'),
      'type' => 'text',
      'schema field' => 'name',
    ) + $default_properties;
  $properties['type'] = array(
      'label' => t('Type'),
      'description' => t('Entity bundle'),
      'type' => 'text',
      'options list' => 'crm_message_template_types',
      'required' => TRUE,
      'schema field' => 'type',
    ) + $default_properties;
  $properties['created'] = array(
      'label' => t('Date created'),
      'type' => 'date',
      'description' => t('The date when channel was posted.'),
      'schema field' => 'created',
    ) + $default_properties;
  $properties['changed'] = array(
      'label' => t('Date changed'),
      'type' => 'date',
      'schema field' => 'changed',
      'description' => t('The date when channel was most recently updated.'),
    ) + $default_properties;
  $properties['language'] = array(
      'label' => t("Language"),
      'type' => 'token',
      'description' => t("The language the node is written in."),
      'options list' => 'entity_metadata_language_list',
      'schema field' => 'language',
    ) + $default_properties;
  $properties['locked'] = array(
    'label' => t("Locked"),
    'type' => 'boolean',
    'description' => t("Whether removing this entity is allowed."),
    'schema field' => 'locked',
  ) + $default_properties;

  $properties['log'] = array(
    'label' => t("Revision log message"),
    'type' => 'text',
    'description' => t("In case a new revision is to be saved, the log entry explaining the changes for this version."),
    'setter callback' => 'entity_property_verbatim_set',
  );
  $properties['revision'] = array(
    'label' => t("Creates revision"),
    'type' => 'boolean',
    'description' => t("Whether saving this entity creates a new revision."),
    'setter callback' => 'entity_property_verbatim_set',
  );

  return $info;
}
