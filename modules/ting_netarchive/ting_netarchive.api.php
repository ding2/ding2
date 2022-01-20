<?php

/**
 * @file
 * Hooks provided by the ting_netarchive module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allows modules to provide archived PDF for ting entities hasOnlineRelations.
 *
 * This is called sequentially in implementing modules, sorting out found PDFs
 * between calls to different modules. This means that the first PDF found
 * will be used.
 *
 * Modules implementing this hook should return an array of found PDFs, where
 * the key is the id and the value the local path or URL of the PDF. Ting
 * PDF will download URLs and move local files into its own storage. Local
 * files should be unmanaged, and if you want to keep the file, make a copy and
 * return its path.
 *
 * A module can stop looking further for a PDF by returning FALSE instead of a
 * path/URL.
 *
 * @param array $request
 *   Array of $id => $entity.
 *
 * @return array
 *   Array of $id => $path to image.
 */
function hook_ting_netarchive($request) {

}


/**
 * @} End of "addtogroup hooks".
 */
