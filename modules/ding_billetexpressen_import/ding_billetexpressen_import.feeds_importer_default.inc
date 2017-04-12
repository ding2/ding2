<?php
/**
 * @file
 * ding_billetexpressen_import.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function ding_billetexpressen_import_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'billetexpressen_events';
  $feeds_importer->config = array(
    'name' => 'Billetexpressen events',
    'description' => 'Import events from Billetexpressen',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => 1,
        'use_pubsubhubbub' => 0,
        'designated_hub' => '',
        'request_timeout' => '30',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsExXml',
      'config' => array(
        'context' => array(
          'value' => '/Events/Event',
        ),
        'sources' => array(
          'unique_id' => array(
            'name' => 'Unique Id',
            'value' => 'UniqueId',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '1',
          ),
          'title' => array(
            'name' => 'Title',
            'value' => 'EventTitle',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '2',
          ),
          'lead' => array(
            'name' => 'Lead',
            'value' => 'ShortDescription',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '3',
          ),
          'body' => array(
            'name' => 'Body',
            'value' => 'LongDescription',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '4',
          ),
          'category' => array(
            'name' => 'Category',
            'value' => 'Category',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '5',
          ),
          'date_start' => array(
            'name' => 'Date:start',
            'value' => 'EventStart',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '6',
          ),
          'date_end' => array(
            'name' => 'Date:end',
            'value' => 'EventStop',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '7',
          ),
          'library' => array(
            'name' => 'Library',
            'value' => 'VenueName',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '8',
          ),
          'location_city' => array(
            'name' => 'Location:City',
            'value' => 'VenueCity',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '9',
          ),
          'location_zip' => array(
            'name' => 'Location:Zip',
            'value' => 'VenueZip',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '10',
          ),
          'location_address_1' => array(
            'name' => 'Location:Address 1',
            'value' => 'VenueAddress_1',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '11',
          ),
          'location_address_2' => array(
            'name' => 'Location:Address 2',
            'value' => 'VenueAddress_2',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '12',
          ),
          'rooms' => array(
            'name' => 'Rooms',
            'value' => 'Auditorium',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '13',
          ),
          'image_url' => array(
            'name' => 'Image URL',
            'value' => 'PictureLinkOriginal',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '14',
          ),
          'image_title' => array(
            'name' => 'Image:Title',
            'value' => 'PictureTitle',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '15',
          ),
          'image_description' => array(
            'name' => 'Image:Description',
            'value' => 'PictureDescription',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '16',
          ),
          'subcategories' => array(
            'name' => 'SubCategories',
            'value' => 'SubCategories',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '17',
          ),
          'subcategory' => array(
            'name' => 'SubCategory',
            'value' => 'SubCategories/SubCategory',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '18',
          ),
          'eventwithticketsale' => array(
            'name' => 'Tickets:EventWithTicketSale',
            'value' => 'EventWithTicketSale',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '19',
          ),
          'ticketsalelink' => array(
            'name' => 'TicketSaleLink',
            'value' => 'TicketSaleLink',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '20',
          ),
          'tickets_soldout' => array(
            'name' => 'Tickets:SoldOut',
            'value' => 'SoldOut',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '21',
          ),
          'tickets' => array(
            'name' => 'Tickets',
            'value' => 'Tickets',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '22',
          ),
          'ticket' => array(
            'name' => 'Ticket',
            'value' => 'Tickets/Ticket',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '23',
          ),
          'ticket_name' => array(
            'name' => 'Ticket:Name',
            'value' => 'Tickets/Ticket/Name',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '24',
          ),
          'ticket_price' => array(
            'name' => 'Ticket:Price',
            'value' => 'Tickets/Ticket/Price',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '25',
          ),
          'tickets_availabletickets' => array(
            'name' => 'Ticket:AvailableTickets',
            'value' => 'Tickets/Ticket/AvailableTickets',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '26',
          ),
          'ticket_soldout' => array(
            'name' => 'Ticket:SoldOut',
            'value' => 'Tickets/Ticket/SoldOut',
            'raw' => 0,
            'inner' => 0,
            'debug' => 0,
            'weight' => '27',
          ),
        ),
        'display_errors' => 1,
        'debug_mode' => 1,
        'source_encoding' => array(
          0 => 'auto',
        ),
        'use_tidy' => 1,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'unique_id',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'lead',
            'target' => 'field_ding_event_lead',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'body',
            'target' => 'field_ding_event_body',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'subcategory',
            'target' => 'field_ding_event_tags',
            'term_search' => '0',
            'autocreate' => 1,
          ),
          5 => array(
            'source' => 'date_start',
            'target' => 'field_ding_event_date:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'date_end',
            'target' => 'field_ding_event_date:end',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'image_url',
            'target' => 'field_ding_event_title_image',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'image_url',
            'target' => 'field_ding_event_list_image',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'location_address_1',
            'target' => 'field_ding_event_location:thoroughfare',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'location_address_2',
            'target' => 'field_ding_event_location:premise',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'location_zip',
            'target' => 'field_ding_event_location:postal_code',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'location_city',
            'target' => 'field_ding_event_location:locality',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'rooms',
            'target' => 'field_ding_event_rooms',
            'term_search' => '0',
            'autocreate' => 1,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'ding_wysiwyg',
        'skip_hash_check' => 0,
        'bundle' => 'ding_event',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '0',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['billetexpressen_events'] = $feeds_importer;

  return $export;
}
