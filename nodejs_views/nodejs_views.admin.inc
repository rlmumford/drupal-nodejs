<?php
/**
 * @file
 * Admin page callbacks for the Node.js Views module.
 */

/**
 * Form builder function.
 */
function nodejs_views_settings() {
	
  $form['views'] = array(
    '#type' => 'fieldset',
    '#title' => t('Views list in block display mode'),
  );
  //get all the views in mode block
  $queryblock = db_select('views_view', 'vv');
  $queryblock->join('views_display', 'vd', 'vv.vid = vd.vid');
  $viewsblocks = $queryblock->fields('vv',array('vid', 'name'))
            ->condition('vd.display_plugin', 'nodejs_block')
            ->execute()
            ->fetchAll();

  //get all the views in mode page
  $querypage = db_select('views_view', 'vv');
  $querypage->join('views_display', 'vd', 'vv.vid = vd.vid');
  $viewspages = $querypage->fields('vv',array('vid', 'name'))
            ->condition('vd.display_plugin', 'nodejs_page')
            ->execute()
            ->fetchAll();
            
  foreach ($viewsblocks as $block) {
	  $options_block[$block->vid] = $block->name;
  }

  foreach ($viewspages as $page) {
	  $options_page[$page->vid] = $page->name;
  }
  
  if (isset($options_block)) {
	  $form['views']['nodejs_views_block_list'] = array(
	   '#type' => 'checkboxes',
	   '#options' => $options_block,
	   '#title' => t('Which of the following views in block display should we use?'),
	  );  
  }

  if (isset($options_page)) {
	  $form['views']['nodejs_views_page_list'] = array(
	   '#type' => 'checkboxes',
	   '#options' => $options_page,
	   '#title' => t('Which of the following views in page display should we use?'),
	  );
  }

  return system_settings_form($form);
}

/**
 * Form builder function.
 */
function nodejs_views_wrapper_settings() {
  $query = db_select('views_display', 'vd');
  $blocks = $query->fields('vd',array('vid'))
    ->condition('vd.display_plugin', 'nodejs_block')
    ->execute()
    ->fetchAll();

  $form['blockwrappers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit custom block wrappers'),
    '#description' => t('If you have custom blocks template or are not using the standard views block id, please change it here.'),
  );
         
  if ($blocks) {
	  foreach ($blocks as $block) {
		if ($block) {
		   $query = db_select('views_view', 'vv');
		   $viewname = $query->fields('vv',array('name'))
					->condition('vv.vid', $block->vid)
					->execute()
					->fetchCol();
				
		   $id = '#view-' . str_replace(' ', '-', strtolower($viewname[0]));
				
	       $form['blockwrappers']['nodejs_block_wrapper'.$block->vid] = array(
			  '#type' => 'textfield',
			  '#title' => t('Custom wrapper id for the view block ' . $viewname[0]),
			  '#default_value' => variable_get('nodejs_block_wrapper'.$block->vid, $id),
			  '#size' => 60,
			  '#maxlength' => 128,
			  '#required' => TRUE,
			);
	    }
	  }
  }
  

         
  $query = db_select('views_display', 'vd');
  $pages = $query->fields('vd',array('vid'))
    ->condition('vd.display_plugin', 'nodejs_page')
    ->execute()
    ->fetchAll();

  if ($pages) {
  $form['pagewrappers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Edit custom page wrappers'),
    '#description' => t('If you have custom templates for a view in page display or are not using the standard views block id, please change it here.'),
  );
	  foreach ($pages as $page) {
		if ($page) {
		   $query = db_select('views_view', 'vv');
		   $viewname = $query->fields('vv',array('name'))
					->condition('vv.vid', $page->vid)
					->execute()
					->fetchCol();
				
		   $id = '.view-' . str_replace(' ', '-', strtolower($viewname[0]));
				
       $form['pagewrappers']['nodejs_page_wrapper'.$page->vid] = array(
			  '#type' => 'textfield',
			  '#title' => t('Custom wrapper id for the view block ' . $viewname[0]),
			  '#default_value' => variable_get('nodejs_page_wrapper'.$page->vid, $id),
			  '#size' => 60,
			  '#maxlength' => 128,
			  '#required' => TRUE,
			);
	    }
	  }
  }
  return system_settings_form($form);
}
