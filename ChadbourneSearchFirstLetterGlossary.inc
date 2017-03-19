<?php


/**
 * Class ChadbourneSearchFirstLetterGlossary
 */
class ChadbourneSearchFirstLetterGlossary extends SearchApiAbstractAlterCallback {

  public function alterItems(array &$items) {
    foreach ($items as $id => &$item) {
      $wrapped_item = entity_metadata_wrapper('node', $item);
      if (!$wrapped_item || !isset($wrapped_item->field_last_name)) {
        $item->search_api_title_first_letter = NULL;
        continue;
      }
      if(drupal_strtolower(substr($wrapped_item->field_last_name->value(), 0, 1))=='x'||drupal_strtolower(substr($wrapped_item->field_last_name->value(), 0, 1))=='y'){
        $item->search_api_title_first_letter = 'xy';
      }
      else{
        $item->search_api_title_first_letter = drupal_strtolower(substr($wrapped_item->field_last_name->value(), 0, 1));
      }
      
    }
  }

  public function propertyInfo() {
    return array(
      'search_api_title_first_letter' => array(
        'label' => t('First Letter of title'),
        'description' => t('Provides first letter of title for fitlers'),
        'type' => 'text',
      ),
    );
  }

}
