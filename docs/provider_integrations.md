# Provider integrations

Ding2 supports integration with other business systems for handling different aspects of a library website such as searching the library catalogue, determining the status of materials and authenticating patrons. Within Ding2 a system handling one or more of these aspects is called a *provider system*.

Provider systems are integrated with Drupal by implementing one or more Drupal modules which use the `ding_provider` module. Such a module is called a *provider module*.

Drupal modules requiring data or functionality from a business system must declare this requirement by implementing a `ding_provider_user` hook. This requirement must be met by other Drupal modules which integrate with business system and expose their data and functionality. This is declared by implementing a `ding_provider` hook.

## Example of a provider integration

The `ding_reservation` module is responsible for allowing users to manage their reservations of materials on the library website. The module exposed a user interface but does not store any reservations on its own. It requires a business system to handle that.

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

## Types of providers

The different aspects of managing a library website are mirrored in the different *provider types* used by Ding2. A provider system may support one or more of these types. Not all types are required to run a Ding2 website.

The different types of providers in alphabetical order:

* **Availability**: Provides information about the availability of a material within the library organisation e.g: Is the material available to be loaned, can it be reserved, where are instances of the material located within the organisation.
* **Debt**: Provides information about a patrons debts towards the library organisation. Debts could be the result of late fees or lost materials.
* **Historical loans**: Provides information about all the loans of a patron over the lifetime of the patronship.
* **Loan**: Provides information about the current loans of a patron and the ability to renew these loans.
* **List**: Provides management of user lists. Lists can be both user-managed e.g. "My favourite books" as well as automatically created e.g. "My loan history". Lists can include a number of different entities e.g. materials, editorial content, other users, searches etc. These lists are mainly used for personalisation features. 
* **Payment**: Provides the ability for patrons to settle their debts - usually using online payment by integrating with a payment gateway.
* **Reservation**: Provides management of reservations for patrons ie. reserving materials, listing current reservations, extending and deleting reservations. 
* **Search**: Provides the ability to search the library and display materials with their metadata such as title, creator, subjects and publication year. It supports advanced searching functionality such as faceted search and autocompletion.
* **User**: Provides authentication of patrons, updating credentials and potentially creation of new patrons. Patrons are integrated with the Drupal user system.
* **User consent**: Provides management of user consent data. If certain functionality requires explicit consent from a patron this allows the consent to be stored in a business system.
* **Wayf**: Provides integration with single sign-on services for authentication based on the architecture of WAYF, a service fully provided by Danish e-Infrastructure Cooperation, under the Danish government's Agency for Science, Technology and Innovation. 

## Provider requirements

While it is possible to mix and match provider systems and provider types as needed by the individual library organisation using Ding2 there are some general requirements and patterns regarding how systems are integrated.

### General requirements

* A provider system must expose an API for the required functionality and data. Examples of protocols used for current integrations:
  * HTTP + JSON/XML
  * SOAP
* It must be possible to consume the API using PHP as that is the programming language used by Ding2.  
* The API should use some form of access control which allows it to be accessed by the Ding2 website and prevents access from outsiders. Examples of currently used authentication methods:
  * Authentication (preferred) e.g. based on username/password or tokens. 
  * Restriction by IP.
* The API should be well-documented in regards to functionality and data exposed. Examples of documentation used by current provider systems:
  * OpenAPI
  * SOAP 
* The API should provide detailed error information which allows the website to provide sufficient feedback to the user.
* The API should respond fast enough to be called synchronously by the website.

### Library system requirements

We refer to a system responsible for managing patrons, materials and material instances and the relationships between these as a library system. When used as a provider system it usually provides the following types:

* User
* Availability
* Loan
* Reservation
* Debt
* Historical loans (optional)
* User consent (optional)

#### User

It must be possible to authenticate a patron given a username and a password. The username can also be in the form of a patron number, social security number or other forms of textual identification. The password can also be a PIN code.

The authentication API should return some form of method for identifying the patron for subsequent requests. It is preferable not to store authentication credentials for each user within the Ding2 system after login procedure has completed.

The authentication API may provide information about whether a patron is blocked i.e. prevented from accessing the library based on debts, bad behaviour or the like.

Given a new password it must be possible to change the password of a patron using the API.

#### Availability

It must be possible to determine the availability of a material given an id of the material (not a material instance). Availability information includes:

* Whether the material is available for loan by a patron
* Whether the material can be reserved by a patron
* The total number of material instances managed by the library organisation
* The distribution of material instances within the library organisation. This should include branch names, locations within each branch and shelf information.

#### Reservation

It must be possible to retrieve the current material reservations of a patron. For each reservation it must be possible to determine:

* An id of the reservation
* The id of the reserved material as used by the search provider system
* The date the reservation was performed by the patron
* The date the reservation expires and is no longer relevant for the patron if not fulfilled by the library
* The id of the branch where the patron would like to pick up the reserved material when ready
* Textual notes for the reservation (if used by the library system)
* The state of the reservation: Whether is ready for pickup or not or if it is an interlibrary reservation
* If the reservation is not ready for pickup:
  * The position of the current reservation in the queue of all reservations of the material.
* If the reservation is ready for pickup:
  * An id of the material instance ready for pickup 
  * The deadline for the patron to pick up an instance of the reserved material (if the reservation is ready for pickup)
* If the reservation is an interlibrary loan and cannot be expected to be available in the local library system:
  * Metadata for the material. As minimum a title of the material.
  
Given an id of a material and identification information for a patron and it must be possible to create a reservation of the material for the patron. The reservation may include information such as an expiry period and a requested pickup branch for the reservation. If the reservation is successful the provider must provide information about pickup branch and queue position for the reservation. If the reservation fails the provider should provide information to be able to determine if the cause of the failure is caused by library policies.

Given an id of a reservation, it must be possible to update it. This may include changing the expiry period or pickup branch for the reservation.

Given an id of a reservation, it must be possible to delete a reservation.

Given an id of a branch in the library organisation, it must be possible to determine the name of this branch.

Given a user it should be possible to update default options for this user. The options may include a preferred pickup branch for reservations and a default expiry period.

#### Loan

It must be possible to retrieve the current loans of a patron. For each loan it must be possible to determine:

* An id for the loan
* The id of the loaned material as used by the search provider system
* The date the loan was performed by the patron
* The date the loan expires
* Whether the loan can be renewed by the patron
* The id of the material instance loaned by the patron

Given one or more loan ids it must be possible to renew these loans and thus extend the expiry date. For each renewal request, the library system must return whether the renewal was successful or not.

The library system may provide additional information about why a renewal request was not successful i.e. because the patron cannot renew the loan again because of library policies or because the material has been reserved by another patron.

#### Debt

It must be possible to retrieve a list of debts (fees) for a patron. For each debt it must be possible to determine:

* An id for the debt
* A date where the debt originates
* A text message for the debt. This should describe the reason for the debt e.g. a late fee or reimbursement for a lost material.
* The amount of money owed in total for the debt
* The amount of money remaining which is left to be paid by the patron in case is has been paid partially
* The type of material for which the debt is created

Given one or more debt ids and identification information for a patron, it must be possible to register these debts as paid.

