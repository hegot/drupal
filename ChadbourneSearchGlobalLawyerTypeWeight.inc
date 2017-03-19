<?php

/**
 * Class ChadbourneSearchGlobalLawyerTypeWeight
 */
class ChadbourneSearchGlobalLawyerTypeWeight extends SearchApiAbstractAlterCallback {

  public function alterItems(array &$items) {
    foreach ($items as $id => &$item) {
      if ($item->nid == '199') {
        $item->search_api_global_lawyer_type_weight = 4;
      }
      elseif (!isset($item->field_title) || $this->getContentTypeWeight($item->field_title) === FALSE) {
        $item->search_api_global_lawyer_type_weight = NULL;
      }
      else {
        $item->search_api_global_lawyer_type_weight = $this->getContentTypeWeight($item->field_title);
      }
    }
  }

  /**
   * @param $content_type
   * @return int
   */
  protected function getContentTypeWeight($content_type) {
    if (isset($content_type['und']['0']['tid'])) {
      $parents = taxonomy_get_parents($content_type['und']['0']['tid']);
    }
    $parent_tid = '';

    if (!empty($parents)) {
      foreach ($parents as $key => $value) {
        $parent_tid = $value->tid;
      }
    }

    $weights = [
      '1150' => 1,
      '1152' => 2,
      '1151' => 3,
    ];
    if (isset($weights[$parent_tid])) {
      return $weights[$parent_tid];
    }

    return FALSE;
  }

  public function propertyInfo() {
    return array(
      'search_api_global_lawyer_type_weight' => array(
        'label' => t('Lawyer type weight'),
        'description' => t('Lawyer type weight that is used as primary sorting criteria on Global Search'),
        'type' => 'integer',
      ),
    );
  }

}
