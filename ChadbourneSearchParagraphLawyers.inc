<?php

/**
 * Class ChadbourneSearchParagraphLawyers
 */
class ChadbourneSearchParagraphLawyers extends SearchApiAbstractAlterCallback {

  public function alterItems(array &$items) {
    foreach ($items as $id => &$item) {
      if ($item->type == 'publications' || $item->type == 'events' || $item->type == 'blog_post' || $item->type == 'news') {
        if (!empty($item->field_related_people)) {
          $pagraphs_item_ids = array();
          foreach ($item->field_related_people['und'] as $paragraph) {
            $pagraphs_item_ids[] = $paragraph['value'];
          }
          $paragraphs = entity_load('paragraphs_item', $pagraphs_item_ids);
          $item->field_related_people['und'] = array();
          foreach ($paragraphs as $single_paragraph) {
            $item->field_related_people['und'][] = array('value' => $single_paragraph->field_related_lawyer['und'][0]['target_id']);
          }
        }
      }
    }
  }
}
