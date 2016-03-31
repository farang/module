<?php

/**
 * Definition of the 'Show in border.' panel style.
 */
$plugin = array(
  'title'              => t('Show in border.'),
  'description'        => t('Show content in border.'),
  'render pane'        => 'panels_show_in_border_style_render_pane',
  'pane settings form' => 'panels_show_in_border_style_settings_form',
  'render region'      => 'panels_show_in_border_style_render_region',
  'hook theme'         => array(
    'show_in_border'   => array(
      'variables'        => array('content' => NULL),
      'path'             => drupal_get_path('module', 'adyax_test') . '/plugins/styles/show_in_border',
      'template'         => 'show_in_border',
    ),
  ),
  'settings form'      => 'panels_show_in_border_style_settings_form',
);

/**
 *Definition of the panels pane style.
 */
function theme_panels_show_in_border_style_render_pane($vars) {

  $content  = $vars['content'];
  $settings = $vars['settings'];
  $pane     = $vars['pane'];
  $display  = $vars['display'];
  $border   = $settings['border'];
  $output   = theme('panels_pane', array('content' => $content, 'pane' => $pane, 'display' => $display));
  $output   = theme('show_in_border', array('content' => $output, 'border_width' => $border));

  return $output;
}

/**
 * Definition of the panels region style.
 */
function theme_panels_show_in_border_style_render_region($vars){

  $panes    = $vars['panes'];
  $settings = $vars['settings'];
  $output   = '';
  $border   = $settings['border'];

  foreach ($panes as $pane) {
    $output .= theme('show_in_border', array('content' => $pane, 'border_width' => $border));
  }

  return $output;
}

/**
 * Form to edit border style settings.
 */
function panels_show_in_border_style_settings_form($style){

  $form['border'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Border width'),
    '#default_value' => (isset($style['border'])) ? $style['border'] : '1',
    '#description'   => t('Specify boder width.'),
  );

  return $form;
}