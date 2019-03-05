# Provider integrations

Ding2 supports integration with other business systems for handling different aspects of a library website such as searching the library catalogue, determining the status of titles and authenticating patrons. Within Ding2 a system handling one or more of these aspects is called a *provider system*.

Provider systems are integrated with Drupal by implementing one or more Drupal modules which use the `ding_provider` module. Such a module is called a *provider module*.

Drupal modules requiring data or functionality from a business system must declare this requirement by implementing a `ding_provider_user` hook. This requirement must be met by other Drupal modules which integrate with business system and expose their data and functionality. This is declared by implementing a `ding_provider` hook.

## Example of a provider integration

The `ding_reservation` module is responsible for allowing users to manage their reservations of titles on the library website. The module exposed a user interface but does not store any reservations on its own. It requires a business system to handle that.

Consequently the module declares this requirement by implementing a hook:

```php
/**
 * Implements hook_ding_provider_user().
 */
function ding_reservation_ding_provider_user() {
  return array(
    'reservation' => array(
      'required' => TRUE,
      'install time setup' => TRUE,
    ),
  );
}
```

The `fbs` module is a provider module which integrates Ding2 with the *provider system, FBS (Fælles BiblioteksSystem - translated: Common library system), a library system for Danish municipalities. FBS supports reservations among other things and the `fbs` module declares this by implementing a hook:

```php
/**
 * Implements hook_ding_provider().
 */
function fbs_ding_provider() {
  return array(
    'title' => 'FBS provider',
    'settings' => 'fbs_settings_form',
    'provides' => array(
      'reservation' => array(
        'prefix' => 'reservation',
        'file' => 'includes/fbs.reservation.inc',
      ),
      // Other exposed provider functionality left out for clarity
    ),
  );
}
```

By combining these two modules end users are provides with a user interface for handling reservations while the reservation data is stored in a separate system.

[`ding_provider.api.php`](../modules/ding_provider/ding_provider.api.php) containers more in-depth documentation about provider hooks, their parameters etc.

## Types of providers

The different aspects of managing a library website are mirrored in the different *provider types* used by Ding2. A provider system may support one or more of these types. Not all types are required to run a Ding2 website.

The different types of providers in alphabetical order:

* **Availability**: Provides information about the availability of a title within the library organisation e.g: Is the title available to be loaned, can it be reserved, where are copies of the title located within the organisation.
* **Debt**: Provides information about a patrons debts towards the library organisation. Debts could be the result of late fees or lost copies.
* **Historical loans**: Provides information about all the loans of a patron over the lifetime of the patronship.
* **Loan**: Provides information about the current loans of a patron and the ability to renew these loans.
* **List**: Provides management of user lists. Lists can be both user-managed e.g. "My favourite books" as well as automatically created e.g. "My loan history". Lists can include a number of different entities e.g. titles, editorial content, other users, searches etc. These lists are mainly used for personalisation features.
* **Payment**: Provides the ability for patrons to settle their debts - usually using online payment by integrating with a payment gateway.
* **Reservation**: Provides management of reservations for patrons ie. reserving titles, listing current reservations, extending and deleting reservations.
* **Search**: Provides the ability to search the library and display titles with their metadata such as title, creator, subjects and publication year. It supports advanced searching functionality such as faceted search and autocompletion.
* **User**: Provides authentication of patrons, updating credentials and potentially creation of new patrons. Patrons are integrated with the Drupal user system.
* **User consent**: Provides management of user consent data. If certain functionality requires explicit consent from a patron this allows the consent to be stored in a business system.
* **Wayf**: Provides integration with single sign-on services for authentication based on the architecture of WAYF, a service fully provided by Danish e-Infrastructure Cooperation, under the Danish government's Agency for Science, Technology and Innovation.

## Provider requirements

While it is possible to mix and match provider systems and provider types as needed by the individual library organisation using Ding2 there are some general requirements and patterns regarding how systems are integrated.

### General requirements

* A provider system must expose an API for the required functionality and data. Examples of protocols used for current integrations:
  * HTTP + JSON/XML
  * SOAP
* It must be possible to consume the API using PHP since that is the programming language used by Ding2.
* The API should use some form of access-control which allows it to be accessed by the Ding2 website and prevents access from outsiders. Examples of currently used authentication methods:
  * Authentication (preferred) e.g. based on username/password or tokens.
  * Restriction by IP.
* The API should be well-documented in regards to functionality and data exposed. Examples of documentation used by current provider systems:
  * OpenAPI
  * SOAP
* The API should provide detailed error information which allows the website to provide sufficient feedback to the user.
* The API should respond fast enough to be called synchronously by the website.

### Library system requirements

Here we refer to a system responsible for managing patrons, bibliographic records (titles), individual items (copies) and the relationships between these as a library system. When used as a provider system it usually provides the following types:

* User
* Availability
* Loan
* Reservation
* Debt
* Historical loans (optional)
* User consent (optional)

#### User

It must be possible to authenticate a patron through a given username and a password. The username can also be in the form of a patron number, national identification number or other forms of textual identification. The password can also be a PIN code.

The authentication API should offer a method for Identifying the patron for subsequent requests. It is preferable not to store the authentication credentials for each user within the Ding2 system after the login procedures have been completed.

The authentication API must provide information about whether a patron is blocked i.e. prevented from accessing the library based on debts, bad behaviour or the like if such functionality is supported by the library system.

It must be possible to change the password of a patron using the API.

#### Availability

It must be possible to determine the availability of a record (not item) given a record ID. Information on availability includes:

* Whether the record is available for loan by a patron.
* Whether the record can be reserved by a patron.
* The total number of items managed by the library organisation.
* The distribution of items within the library organisation. This should include the name of the library branch, the location within each branch and shelf information.

#### Reservation

It must be possible to retrieve the current reservations of records for a patron. For each reservation it must be possible to determine:

* An ID of the reservation.
* The ID of the reserved record as used by the search provider system.
* The date the reservation was initiated by the patron.
* The date the reservation expires and is no longer relevant for the patron if not fulfilled by the library before that date.
* The ID of the branch where the patron would like to pick up the reserved record.
* Text messages for the reservation (if used by the library system).
* The state of the reservation, whether it is ready for pickup or not or if it is an interlibrary reservation.
* If the reservation is not ready for pickup:
  * The situation of the current reservation in the queue of all reservations of the record.
* If the reservation is ready for pickup:
  * The ID of the item ready for pickup.
  * The deadline for the patron to pick up the reserved item.
* If the reservation is an interlibrary loan and cannot be expected to be available in the local library system:
  * Metadata for the record. As minimum the title should be made available.

With an ID of a record and identification information for a patron it must be possible to create a reservation of the record for the patron. The reservation may include information such as an expiry period and a requested pickup branch for the reservation. If the reservation is successful, the provider must provide information about pickup branch and queue position for the reservation. If the reservation cannot be fulfilled the provider should provide information to be able to determine if the reason for the failure is caused by library policies.

With the ID of a reservation, it must be possible to update it. This may include changing the expiry period or the pickup branch for the reservation.

With an ID of a reservation, it must be possible to delete it without being fulfilled.

With the ID of a branch within the library organisation, it must be possible to determine the name of the branch in question.

With the ID of a patron, it should be possible to update default reservation preferences for the patron. Preferences may include a preferred branch for picking up reservations or a default expiry period.

#### Loan

It must be possible to retrieve information on the current loans of a patron. For each loan it must be possible to determine:

* An ID for the loan.
* The ID of the item borrowed by the patron.
* The ID of the lent record as used by the search provider system.
* The date the item was borrowed by the patron.
* The date the loan expires.
* Whether the loan can be renewed by the patron

With one or more loan IDs it must be possible to renew each of these loans and thus extend its expiry date. For each renewal request, the library system must indicate whether the renewal was successful or not.

The library system may provide additional information about why a renewal request was not successful. Potential causes are library policies or reservations by another patron.

#### Debt

It must be possible to retrieve a list of debts (or fees) for a patron. For each debt it must be possible to determine:

* An ID for the debt.
* A date when the debt was originated.
* A text message for the debt which should describe the reason for the debt, if it is a fee for overdue return or reimbursement for a lost item.
* The total amount of money owed for the debt.
* The amount of money left to be paid by the patron, in case the debt has been partially paid.
* The type of record for which the debt is created.

With one or more debt IDS and the identification information for the patron, it must be possible to register each one of these debts as settled. This can be used if the library accepts online payment.

#### Search

##### Search functionality

It must be possible to do a free text search for records in the catalog based on a query string.

It must be possible to search for records in the catalog matching one or more values (OR or AND correlation) for a specific field. This can also be implemented as facets or indices. At least the following fields must be supported:

* Acquisition date
* Creator
* Category
* Language
* Publication date
* Subject
* Title
* Type

It must be possible to search for records in the catalog based on a query containing multiple joined subqueries. Results must satisfy all subqueries (AND correlation).

It must be possible to divide a search result into subsets such as by specifying an offset and a number of records requested. Example: Return 10 records starting from number 30.

Records in the search result must be in an order which is meaningful to the query. It should be possible to specify one or more sorting methods when executing a search. Example: Sort results by publication year with the newest records first.

It must be possible to retrieve a record based on the ID of the record. It should be possible to retrieve multiple records in a single request by providing multiple IDs.

It must be possible to exclude records from a search result based on their ID.

It should be possible to retrieve facets and terms for a search result. Each term must include a count of how many records it refers to within the result.

It should be possible to provide suggestions for queries based on a partial query. An example of a use case for this is autocompletion.

It may be possible to group records within search results into collections e.g. different editions or volumes of a record are shown as a single search result.

It may be possible to perform a fuzzy search which includes records which do not match the query fully but are still deemed relevant.

It may be possible to retrieve records which are deemed relevant to a specific record e.g. through collaborative filtering.

##### Record properties

It must be possible to retrieve data about individual records within the library catalog. In this regard a record is considered a certain title - a book, cd or other type of object - although not the individual copies (items) of the record.

It must be possible to retrieve the following properties:

* ID. The ID for a record must be unique and should not change over time.
* Title of the record. A short version of the title may be supported.
* Names of one or more creators of the record.
* Record tyoe e.g. *Book* or *Audio CD*.
* Record source.
* ID of the record based on the source. If a record in the search system originates from the library system, this should be the library system ID.

It should be possible to retrieve the following properties:

* An abstract providing a summary.
* One or more subject headings.
* Language of the recored.
* Url to the record if it has a digital representation.
* Series name and number of the record.
* Year the record was produced.

It may be possible to retrieve the following properties, if applicable:

* Age for the target audience for the record.
* Target audience for the record.
* A description of physical appearance of the record.
* Size or duration of the record.
* File format, physical medium, or dimensions of the record.
* Genre of the record.
* ISBN of the record. Preferably ISBN-13.
* Name(s) of musicians listed as contributors.
* Pan European Game Information (PEGI) rating for the record.
* Name of the publisher of the record.
* IDs of records which references this record.
* Version/revision of the record.
* IDs of newer records which replace this record.
* IDs of older records which are replaced by this record.
* Information about rights held in and of the record.
* Spatial characteristics of the record.
* Spoken language within the record.
* Record subtitle languages.
* Titles of tracks in this record.
* Record revision name.
* Record which contains this record e.g. a periodical issue containing an article.
* Classification of the record.
* Names of one or more contributors of the record.
* IDs of records which are related.
* Full text version of the record.

It must be possible to retrieve a cover image of a record - either directly from the search system  or indirectly through information provided through the search result.

It must be possible to retrieve a list of all record types and sources used in the system.
