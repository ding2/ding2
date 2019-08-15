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
 * Alter the form when syndicating content from BPI.
 *
 * @param array $form
 *   The form.
 * @param array $context
 *   The form context; keys:
 *   - form_state (array): The form state (by reference).
 *   - bpi_node (array): The BPI node content.
 *   - syndicated_images (array): Images downloaded from BPI.
 */
function hook_bpi_syndicate_node_form(array &$form, array &$context) {
}

/**
 * Alter data to be pushed to BPI.
 *
 * @param array $bpi_content
 *   The BPI content.
 * @param array $node
 *   The node.
 * @param array $context
 *   The context; keys:
 *   - with_refs (bool): Push with references to materials.
 *   - with_images (bool): Push with images.
 */
function hook_bpi_convert_to_bpi_alter(array &$bpi_content, array $node, array $context) {
}

/**
 * @} End of "addtogroup hooks".
 */
