<?php

/**
 * @file
 * DataManager. Handles data from files.
 *
 * The data manager module is first cut on a data management support system
 * for the behat test suite. This will provide known data to support the test
 * scenarios. At this stage the data is placed in files of equivalent data for
 * particular purposes: Pid's which have reviews, creator-description, online
 * access, accessinfomedia - and pid's that doesn't have this particular
 * attribute.
 *
 * The file to be used is set through a gherkin command and to find a Pid a
 * random post is picked from that file. This broadens the test coverage to
 * vary on data.
 */

/**
 * Class DataManager
 */
// phpcs:disable PSR1.Classes.ClassDeclaration.MissingNamespace
class DataManager extends \Page\PageBase
{
    /**
     * Filename - holds the filename for the current chosen data file.
     *
     * @var string $filename
     */
    protected $filename = '';

    /**
     * Counter into file
     *
     * @var file $fileHolder
     *    Pointer to file.
     */
    protected $fileHolder;

    /**
     * Flag showing if we have reached the end of the file.
     *
     * @var bool $fileOEF
     *    Flag.
     */
    protected $fileEOF;

    /**
     * Flag for reservable only. If set only reservable pid's will be returned.
     *
     * @var bool $onlyReservable
     *    True if only finding reservable objects.
     */
    protected $onlyReservable = false;

    /**
     * Get Filename - returns the current filename in use.
     *
     * @return mixed
     *    The current filename.
     */
    public function getFilename()
    {
        return $this->filename;
    }

    /**
     * Open file and make it ready to read from.
     */
    public function setToFirstInFile()
    {
        if (!$this->fileHolder) {
            if (is_readable($this->filename)) {
                $this->fileHolder = fopen($this->filename, "r");
                $this->fileEOF = false;
            }
        }
    }


    /**
     * Reads next from file.
     *
     * Updates fileEOF marking and close the file if the end has been reached.
     *
     * @return string
     *    The next PID read from file.
     */
    public function readNextPidFromFile()
    {
        $this->fileEOF = !($fline = fgets($this->fileHolder));
        if ($this->fileEOF == true) {
            fclose($this->fileHolder);
            $this->fileHolder = null;
        }
        $columns = explode("\t", $fline);
        return $columns[0];
    }

    /**
     * Return state of file reading.
     *
     * @return bool
     *    True if the file has been read to an end.
     */
    public function EOF()
    {
        if ($this->fileEOF) {
            return true;
        };
        return false;
    }

    /**
     * Get a random PID from the set datafile.
     *
     * The reason for taking out random values is to create the opportunity of a broader test.
     * All data in the file must be equivalent in terms of their basic attributes, for instance
     * 'has review'.
     *
     * @return mixed|string
     *    Return the PID that was found.
     *
     * @throws Exception
     *    In case of error.
     */
    public function getRandomPID()
    {
        $marray = [];
        if (is_readable($this->filename)) {
            // Now open, and read in all lines until no more data is returned, or we found a match.
            // If we only want reservables, we only read in objects of type Bog*.
            $mfilehandle = fopen($this->filename, "r");
            while (($fline = fgets($mfilehandle)) !== false) {
                if ($fline != "") {
                    // If we are only looking for reservables, we should only add real books.
                    if ($this->onlyReservable) {
                        $columns = explode("\t", $fline);
                        if (count($columns) != 3) {
                            return "Error: File '" . $this->filename . "' is expected to have three columns.";
                        }
                        if (substr($columns[2], 0, 3) == "Bog") {
                            $marray[] = $fline;
                        }
                    } else {
                        $marray[] = $fline;
                    }
                }
            }
            fclose($mfilehandle);
            if (count($marray) < 1) {
                return "Error: file '" . $this->filename . "' was empty or did not contain any books.";
            }

            // Pick a random line of the ones read in, and dissolve it into fields, separated by tabs.
            $pointer = random_int(0, count($marray) - 1);
            $columns = explode("\t", $marray[$pointer]);

            // If the flag is set for only finding reservables, try up to 200 times to
            // find one that is reservable according to Connie conventions. Notice we
            // only try this for books, because other types are generally not reservable.
            $max = 200;
            while (--$max > 0 && $this->onlyReservable && !$this->isReservable($columns[0])) {
                // We found a random one to start with, now we spin forward until we
                // find a reservable one and loop around if we get to the end.
                $pointer++;
                if ($pointer == count($marray)) {
                    $pointer = 0;
                }
                $columns = explode("\t", $marray[$pointer]);
            }
            if ($max == 0) {
                return "Error: no reservable information found " . $columns[0] . " " . $columns[2];
            }
            // Return the PID.
            return $columns[0];
        } else {
            return "Error: file " . $this->filename . " does not exist or is not readable!";
        }
    }

    /**
     * Tells if material is reservable according to Connie rules.
     *
     * This works of course only on Connie, which must be enabled for checks about
     * reservation.
     *
     * @param string $mpid
     *    The pid of the object to be checked for whether it is reservable.
     *
     * @return bool
     *    If true the material is reservable
     */
    private function isReservable($mpid)
    {
        $xx = explode(":", $mpid);
        $provider = $xx[count($xx) - 1];
        if ($provider % 2 == 0) {
            if (($provider / 10) % 2 == 0) {
                return true;
            }
        }
        return false;
    }

    /**
     * Set Filename for the data file to be used for known data.
     *
     * @param string $setFilename
     *    Filename to use.
     */
    public function setFilename($setFilename)
    {
        $this->filename = $setFilename;
    }

    /**
     * Set flag for whether returned pid's from data files of known pids should only be reservable.
     *
     * @param bool $truefalse
     *    Set flag for whether material should be reservable or not.
     */
    public function setReservable($truefalse)
    {
        $this->onlyReservable = $truefalse;
    }
}
