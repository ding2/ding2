<?php

/**
 * @file
 * Describe hooks provided by the BPI module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Return a list of BPI node types a module can handle.
 *
 * @return string[]
 *   An array of BPI type names.
 */
function hook_bpi_syndicate_get_bpi_types() {
    return array();
}

/**
 * Get form for mapping a BPI node to a Drupal content type.
 *
 * @param string $bpi_node_type
 *   The BPI node type.
 * @param string $content_type
 *   The Drupal content type.
 * @param array $field_mapping
 *   The field mapping (@see bpi_get_mappings() for details).
 *
 * @return array
 *   The mapping form.
 */
function hook_bpi_get_field_mapping_form($bpi_node_type, $content_type, array $field_mapping) {
    return array();
}

/**
 * Alter the form for defining a BPI node mapping.
 *
 * @param string $bpi_type
 *   The BPI node type.
 * @param array $form
 *   The form.
 */
function hook_bpi_mapping_form_alter($bpi_type, array &$form) {
}

/**
 * Get a url used for syndicating a BPI node.
 *
 * @param string $bpi_type
 *   The BPI node type.
 * @param string $bpi_id
 *   The BPI node id.
 * @param array $mapping
 *   The mapping for the node type.
 *
 * @return string|NULL
 *   The syndicate url.
 */
function hook_bpi_syndicate_action_url($bpi_type, $bpi_id, array $mapping) {
    return NULL;
}

/**
 * Alter data to be pushed to BPI.
 *
 * @param array $bpi_content
 *   The BPI content.
 * @param array $node
 *   The node..
 * @param array $mapping
 *   The BPI mapping of the node.
 */
function hook_bpi_convert_to_bpi_alter(array &$bpi_content, $node, array $mapping) {
}

/**
 * Get bpi image type for an image field.
 *
 * A "bpi image type" is basically a name describing how the image is used;
 * example image types: 'image', 'list_image', 'title_image'.
 *
 * @param string $image_field_name
 *   The image field name.
 * @param object $node
 *   The node.
 *
 * @return string|NULL
 *   The bpi image type.
 */
function hook_bpi_get_image_type($image_field_name, $node) {
    return NULL;
}

/**
 * @} End of "addtogroup hooks".
 */
