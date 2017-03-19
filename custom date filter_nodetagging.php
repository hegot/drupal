<?php
/**
 * Implements hook_entity_property_info_alter().
 */
function chadbourne_insight_entity_property_info_alter(&$info) {
  $info['node']['properties']['insight_type'] = [
    'label' => t('Insight type'),
    'description' => t('Insight type for the filter'),
    'type' => 'text',
    'options list' => 'chadbourne_insight_type_options',
    'computed' => TRUE,
    'getter callback' => '_chadbourne_insight_get_type',
    'entity views field' => TRUE,
  ];
  $info['node']['properties']['agregated_date'] = [
    'label' => t('Agregated date'),
    'description' => t('Agregated date for the filter - datecreated and start date for events'),
    'type' => 'text',
    'computed' => TRUE,
    'getter callback' => '_chadbourne_insight_get_agregated_date',
    'entity views field' => TRUE,
  ];
}

/**
 * Getter for insight agregated_date property for nodes.
 */
function _chadbourne_insight_get_agregated_date($item) {
  if ($item->type == 'event') {
    if (!empty($item->field_event_date['und'][0]['value'])) {
      $result = strtotime($item->field_event_date['und'][0]['value']);
    }
    else {
      $result = $item->created;
    }
  }
  else {
    $result = $item->created;
  }
  return $result;
}

/**
 * Getter for insight type property for nodes.
 */
function _chadbourne_insight_get_type($item) {
  $type = $item->type;
  switch ($type) {
    case 'blog_post':
      $result = 'blog';
      break;
    case 'events':
      foreach ($item->field_event_type['und'] as $type) {
        if ($type['tid'] == 1285) {
          $result = 'webinar';
        }
      }
      if (empty($result)) {
        $result = 'event';
      }
      break;
    case 'news':
      foreach ($item->field_news_types['und'] as $type) {
        if ($type['tid'] == 1139) {
          $result = 'pressrelease';
        }
        else {
          $result = 'news';
        }
      }
      break;
    case 'publications':
      if ($item->field_publication_type['und'][0]['tid'] == 1146) {
        $result = 'article';
      }
      if ($item->field_publication_type['und'][0]['tid'] == 1147) {
        $result = 'client_alert';
      }
      if ($item->field_publication_type['und'][0]['tid'] == 1148) {
        $result = 'newswire';
      }

      break;
  }
  return $result;
}