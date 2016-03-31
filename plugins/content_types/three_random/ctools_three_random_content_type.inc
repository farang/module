<?php

/**
 * Definition of the 'Three random node teasers.' panel style.
 */
$plugin = array(
  'title'           => t('Three random node teasers.'),
  'description'     => t('Show us three random teasers of nodes.'),
  'content_types'   => array('no_context_content_type'),
  'render callback' => 'ctools_three_random_static_block_render',
  'defaults'        => array(),
  'edit form'       => 'ctools_three_random_block_edit_form',
  'icon'            => 'favicon.ico',
  'category'        => array(t('Nodes'), -9),
);

/** 
 *Default edit form Content type
 */
function ctools_three_random_block_edit_form($form, &$form_state) {

  return $form;
}

/**
 *Render Block View
*/
function ctools_three_random_static_block_render($subtype, $conf, $args, $context) {

  $block  = new stdClass();

  $result = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.status', NODE_PUBLISHED)
    ->execute()
    ->fetchAll();

  $result_amount = count($result);
  $amount = $result_amount == 0 ? 3 : 1;
  $rendered_teaser = '';

  switch ($result_amount) {
    case '0':
        $random_nid = false;
      break;

    case '1':
        $random_nid = array($result[0]->nid => 0);
      break;
    
    default:
        $random_nid = $result_amount < 3 ? array_rand($result, $result_amount) : array_rand($result, 3); 
      break;
  }

  if ($result_amount > 0){
    foreach ($random_nid as $key => $value) {
      $nid             = $result[$value];
      $view_type       = 'teaser';
      $node            = node_load($nid->nid);
      $view            = node_view($node, $view_type);
      $teaser          = render($view);
      $rendered_teaser .= $teaser;
    }
  }
  else {
      $rendered_teaser = 'No content has been created yet.';
  }

  $block->content = $rendered_teaser;

  return $block;
}