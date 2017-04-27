<?php

/**
 * @file
 * Hooks provided by the ting_covers module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allows modules to provide covers for ting entities.
 *
 * This is called sequentially in implementing modules, sorting out found covers
 * between calls to different modules. This means that the first cover found
 * will be used.
 *
 * Modules implementing this hook should return an array of found covers, where
 * the key is the id and the value the local path or URL of the cover. Ting
 * cover will download URLs and move local files into its own storage. Local
 * files should be unmanaged, and if you want to keep the file, make a copy and
 * return its path.
 *
 * A module can stop looking further for a cover by returning FALSE instead of a
 * path/URL.
 *
 * @param array $request
 *   Array of $id => $entity.
 *
 * @return array
 *   Array of $id => $path to image.
 */
function hook_covers_ting_covers($request) {

}


/**
 * @} End of "addtogroup hooks".
 */
