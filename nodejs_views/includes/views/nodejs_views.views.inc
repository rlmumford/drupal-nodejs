<?php
function nodejs_views_views_plugins() {

return array(
  'display' => array(
    'nodejs_page' => array(
      'title' => t('Nodejs Page'),
      'help' => t('Display the view as a page, using nodejs, with a URL and menu links.'),
      'handler' => 'views_plugin_display_page',
      'theme' => 'views_view',
      'uses hook menu' => TRUE,
      'contextual links locations' => array('page'),
      'use ajax' => TRUE,
      'use pager' => TRUE,
      'use more' => TRUE,
      'accept attachments' => TRUE,
      'admin' => t('Nodejs Page'),
      'help topic' => 'display-page',
      ),
    'nodejs_block' => array(
      'title' => t('Nodejs Block'),
      'help' => t('Display the view as a block, using nodejs.'),
      'handler' => 'views_plugin_display_block',
      'theme' => 'views_view',
      'uses hook block' => TRUE,
      'contextual links locations' => array('block'),
      'use ajax' => TRUE,
      'use pager' => TRUE,
      'use more' => TRUE,
      'accept attachments' => TRUE,
      'admin' => t('Nodejs Block'),
      'help topic' => 'display-block',
                     ),
                     ),
             );
}

function nodejs_views_views_data() {
  // The 'group' index will be used as a prefix in the UI for any of this                
  // table's fields, sort criteria, etc. so it's easy to tell where they came            
  // from.                                                                               
  $data['nodejs_views']['table']['group'] = t('Nodejs Views');

  // Define this as a base table. In reality this is not very useful for                 
  // this table, as it isn't really a distinct object of its own, but                    
  // it makes a good example.                                                            
  $data['nodejs_views']['table']['base'] = array(
    'field' => 'vid',
    'title' => t('Nodejs Views table'),
    'help' => t("Nodejs views table contains if the current view should be autorefresh by nodejs and can be related to views."),
    'weight' => -10,
                                                  );

  // This table references the {node} table.                                             
  // This creates an 'implicit' relationship to the node table, so that when 'Node'      
  // is the base table, the fields are automatically available.                          
  $data['nodejs_views']['table']['join'] = array(
    // Index this array by the table name to which this table refers.                    
    // 'left_field' is the primary key in the referenced table.                          
    // 'field' is the foreign key in this table.                                         
    'views_view' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  // Nodejs enabled field.                                                              
  $data['nodejs_views']['boolean_field'] = array(
    'title' => t('Nodejs enabled'),
    'help' => t('Autorefresh the view with nodejs.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
                     ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Published'),
      'type' => 'yes-no',
      // use boolean_field = 1 instead of boolean_field <> 0 in WHERE statment           
      'use equal' => TRUE,
                      ),
    'sort' => array(
      'handler' => 'views_handler_sort',
                    ),
    );
}