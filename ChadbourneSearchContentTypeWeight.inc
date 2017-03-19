<?php


/**
 * Class ChadbourneSearchContentTypeWeight
 */
class ChadbourneSearchContentTypeWeight extends SearchApiAbstractAlterCallback {

  public function alterItems(array &$items) {
    foreach ($items as $id => &$item) {
      if (!isset($item->type) || $this->getContentTypeWeight($item->type) === FALSE) {
        $item->search_api_content_type_weight = NULL;
      }

      $item->search_api_content_type_weight = $this
        ->getContentTypeWeight($item->type);
    }
  }

  /**
   * @param $content_type
   * @return int
   */
  protected function getContentTypeWeight($content_type) {
    $weights = [
      'lawyers' => 1,
      'services' => 2,
      'publications' => 3,
      'events' => 3,
      'blog_post' => 3,
      'news' => 3,
      'offices' => 3,
    ];

    if (isset($weights[$content_type])) {
      return $weights[$content_type];
    }

    return FALSE;
  }

  public function propertyInfo() {
    return array(
      'search_api_content_type_weight' => array(
        'label' => t('Content type weight'),
        'description' => t('Content type weight that is used as primary sorting criteria on Global Search'),
        'type' => 'integer',
      ),
    );
  }

}
