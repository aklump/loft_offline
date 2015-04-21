<?php
/**
 * @file
 * Provides variable meta-data using variable module.
 *
 * @ingroup loft_offline
 */

/**
 * Define variables used by a module.
 *
 * Provides meta-information for each variable that includes at the very least some human readable title.
 * This information may be used by other modules to select variables from a list for translating, exporting, etc.
 *
 * Though not required we can also provide some more information to be able to handle the variable in an effective
 * way, like which type of data and form element it uses, default value, etc.. There are multiple predefined
 * variable types ('type' attribute) that will add a predefined set of properties. Some of them are:
 *
 * - "string": Simple plain string variable. The form element will be a text field and it will be localizable.
 * - "number": Simple numeric value. The form element will be a text field.
 * - "boolean": Simple TRUE/FALSE value. It will be a checkbox.
 * - "enable": Enabled / Disabled selector. It will display as two radio buttons.
 * - "select": Selectable list of options. Depending on the number of options, the element will be a list of
 *   radios or a drop down.
 * - "options": List of options with multiple choices. It will be a list of checkboxes.
 * ...
 *
 * More variable types can be defined by modules using hook_variable_type_info().
 *
 * For the case of variable names that depend on some other parameter (like variables per content-type),
 * there's some special type of variables: Multiple variables. These can be defined like this:
 *
 * @code
 *   $variables['node_options_[node_type]'] = array(
 *     'type' => 'multiple',
 *     'title' => t('Default options', array(), $options),
 *     'repeat' => array(
 *       'type' => 'options',
 *       'default' => array('status', 'promote'),
 *       'options callback' => 'node_variable_option_list',
 *     ),
 *   );
 * @endcode
 *
 * This multiple variable will spawn into one variable for each node type. Note the variable name that includes
 * the property [node_type]. Values for [node_type] will be defined on hook_variable_type_info().
 *
 * The 'repeat' property defines the properties of children variables. In this case the 'type' property is optional
 * and will default to 'multiple'.
 *
 * @param $options
 *   Array of options to build variable properties. Since variable properties are cached per language
 *   these options should be used at the very least for string translations, so titles and defaults are
 *   localized. Possible options:
 *   - "language" => Language object for which strings and defaults must be returned. This one will be always defined.
 *
 * @return
 *   An array of information defining the module's variables. The array
 *   contains a sub-array for each node variable, with the variable name
 *   as the key. Possible attributes:
 *   - "title": The human readable name of the variable, will be used in auto generated forms.
 *   - "type": Variable type, should be one of the defined on hook_variable_type_info().
 *   - "group": Group key, should be one of the defined on hook_variable_group_info().
 *   - "description": Variable description, will be used in auto generated forms.
 *   - "options": Array of selectable options, or option name as defined on hook_variable_option_info().
 *   - "options callback": Function to invoke to get the list of options.
 *   - "default": Default value.
 *   - "default callback": Function to invoke to get the default value.
 *   - "multiple": Array of multiple children variables to be created from this one.
 *   - "multiple callback": Function to invoke to get children variables.
 *   - "element": Form element properties to override the default ones for this variable type.
 *   - "element callback": Function to invoke to get a form element for this variable.
 *   - "module": Module to which this variable belongs. This property will be added automatically.
 *   - "repeat": Array of variable properties for children variables.
 *   - "localize": Boolean value, TRUE for variables that should be localized. This may be used by other modules.
 *   - "validate callback": Callback to validate the variable value, it will be added to form element #validate.
 *
 * @see hook_variable_info_alter()
 */
function loft_offline_variable_info($options) {
  $variables['loft_offline'] = array(
    'title' => t('Maintenance directive', array(), $options),
    'group' => 'loft_offline',
    'type' => 'number',
    'default' => 0,
    'description' => t('0 for normal mode, 1 for maintenance mode, or n seconds in the future for automatic, delayed maintenance mode.', array(), $options),
    'required' => TRUE,
  );

  $variables['loft_offline_meta'] = array(
    'title' => t('Tracking data', array(), $options),
    'group' => 'loft_offline',
    'type' => 'array',
    'default' => array(
      'previous' => NULL,
      'start' => NULL,
      'status' => MENU_SITE_ONLINE,
      'countdown' => NULL,
    ),
    'description' => t('Internal meta data for managing the offline state.', array(), $options),
    'required' => TRUE,
  );

  $variables['loft_offline_threshold'] = array(
    'title' => t('Message repeat threshold', array(), $options),
    'group' => 'loft_offline',
    'type' => 'number',
    'default' => 2,
    'description' => t('The min number of seconds before a message is repeated.', array(), $options),
    'required' => TRUE,
  );

  $variables['loft_offline_force_logout'] = array(
    'title' => t('Logout users', array(), $options),
    'group' => 'loft_offline',
    'type' => 'boolean',
    'default' => TRUE,
    'description' => t('Logout users during site maintenance.', array(), $options),
    'required' => FALSE,
  );

  $variables['loft_offline_message'] = array(
    'title' => t('Advance warning', array(), $options),
    'group' => 'loft_offline',
    'type' => 'text',
    'default' => "[site:name] will be going offline for maintenance at @time (@remaining from now).",
    'description' => t('The message to display to users before the site goes offline.  Dynamic values are: @remaining, @time. Tokens are supported.', array(), $options),
    'required' => TRUE,
  );

  $variables['loft_offline_whitelist_message'] = array(
    'title' => t('Notice to whitelist users', array(), $options),
    'group' => 'loft_offline',
    'type' => 'text',
    'default' => "[site:name] is currently in extreme maintenance mode for non-privilaged users.",
    'description' => t('The message to display to whitelist users during extreme maintenance mode.  Tokens are supported.', array(), $options),
    'required' => TRUE,
  );

  $variables['loft_offline_message_time_format'] = array(
    'title' => t('Time format', array(), $options),
    'group' => 'loft_offline',
    'type' => 'string',
    'default' => 'g:ia T',
    'description' => t('Time format for offline messages', array(), $options),
    'required' => TRUE,
  );
  $variables['loft_offline_uids'] = array(
    'title' => t('Allowed UIDs', array(), $options),
    'group' => 'loft_offline',
    'type' => 'string',
    'default' => array(),
    'description' => t('A space-separated list of UIDs that may still login during extreme maintenance.', array(), $options),
    'required' => FALSE,
  );
  
  return $variables;
}
