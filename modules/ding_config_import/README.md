# Ding configuration import
This module can be used to import configuration changes into the site and enable/disable modules.

The configuration is described by using YAML files with arrays that are flattened to variable keys
if they are associative arrays. If "normal" arrays they are written as arrays to variables.

If an associative array contains the stop key `array: 1` the array it is placed in is not flattened
thereby allow for complex variable configuration.

The module comes with an example file to help users getting started with the configuration files.

## How to use
Simply download the example file that comes with the module add edit it to set the different
configuration variables.

Upload the file at `/admin/config/ding/config` and clear the cache.

## How it is parsed

The yaml file has two root elements `settings` and `modules`, so the basic file looks like this.
```yaml
---
settings:
  opensearch:
    url: "https://opensearch.addi.dk/b3.5_5.2/"
    auth:
      group: "xxxxx"
      name: "yyyy"
      pass: "zzzz"

modules:
  enable:
    - ding_user_form
  disable:
    - ding_adgangsplatformen
    - ding_registration
```
Note that it is not required that both root elements are present in a given file.

This yaml snippet will be transformed to the following variables as store in the database.
```yaml
---
opensearch:
  url: "https://opensearch.addi.dk/b3.5_5.2/"
  auth:
    group: "xxxxx"
    name: "yyyy"
    pass: "zzzz"
```

Translate into:
```txt
opensearch_url = "https://opensearch.addi.dk/b3.5_5.2/"
opensearch_auth_group = "xxxx"
opensearch_auth_name = "xxxx"
opensearch_auth_pass = "xxxx"
```

More advanced configuration using the `array: 1` "key-word" to prevent flatting.
```yaml
ding:
  ting_frontend_group_holdings_available: "open"
  adgangsplatformen:
    settings:
      array: 1
      clientId: ''
      clientSecret: ''
      auth_client:
        authClientId: ''
        authClientSecret: ''
```

Translate into:
```txt
ding_ting_frontend_group_holdings_available = "open"
ding_adgangsplatformen_settings = [
  clientId => ''
  clientSecret => ''
  auth_client => [
    authClientId => ''
    authClientSecret => ''
  ]
]
```

You can enable/disable modules using the `modules` section in the yaml file.
```yaml
modules:
  enable:
    - ding_user_form
  disable:
    - ding_adgangsplatformen
    - ding_registration
```
