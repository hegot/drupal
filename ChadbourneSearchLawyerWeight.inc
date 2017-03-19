<?php


/**
 * Class ChadbourneSearchLawyerWeight
 *
 * Calculates weight of lawyer depending on its title - partner, counsel,
 * of counsel, associate.
 */
class ChadbourneSearchLawyerWeight extends SearchApiAbstractAlterCallback {

  public function alterItems(array &$items) {
    $weight =& drupal_static(__FUNCTION__, []);

    // Fetch an cache weights.
    if (!$weight) {
      $voc = taxonomy_vocabulary_machine_name_load('lawyer_title');
      $q = db_select('taxonomy_term_lineage', 'ttl')
        ->fields('ttl');
      $q->innerJoin(
        'taxonomy_term_data',
        'tt',
        'ttl.tid=tt.tid AND tt.vid=:vid',
        ['vid' => $voc->vid]
      );
      $result = $q->execute()->fetchAllAssoc('tid');

      if (!empty($result)) {
        foreach ($result as $tid => $lineage) {
          $exploded_lineage_terms = explode(PHP_EOL, $lineage->lineage);
          $item_weight = '';
          foreach ($exploded_lineage_terms as $lineage_exploaded_term) {
            $components = explode('-', $lineage_exploaded_term);
            $item_weight .= reset($components);
          }
          $weight[$tid] = $item_weight;
        }
      }
    }

    // Set weight for each node
    foreach ($items as $id => &$item) {
      $item->search_api_lawyer_weight = NULL;
      if (!empty($item->field_title)) {
        if ($item->field_title) {
          foreach ($item->field_title as $tid) {
            if (isset($weight[$tid]) && strlen($weight[$tid]) < 5) {
              $item->search_api_lawyer_weight = $weight[$tid];
              break;
            }
          }
        }
      }
    }
  }

  public function propertyInfo() {
    return array(
      'search_api_lawyer_weight' => array(
        'label' => t('Lawyer weight according to its title'),
        'description' => t(
          'Calculated weight of lawyer depending on its title - partner, counsel, of counsel, associate'
        ),
        'type' => 'text',
      ),
    );
  }

}
