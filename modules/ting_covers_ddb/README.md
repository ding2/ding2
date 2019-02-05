# Ting Covers DDB

## Requirements

* Docker

## Generate OpenAPI client from specs

Only used when updating the API client / working on the API; not needed for installation.

```sh

docker run --rm -v ${PWD}:/local openapitools/openapi-generator-cli generate \
    --skip-validate-spec \
    -i https://raw.githubusercontent.com/reload/ddb-coverservice-api/master/coverservice-2.0.0.yaml \
    -g php \
    -o /local

```

We use `--skip-validate-spec` because `openapi-generator-cli` doesn't comply completely to the OpenAPI 3.0 specification.

In this case it throws errors because of some valid default values.
We handle this in the custom code (default values for format and size).

```sh

-attribute paths.'/cover/{type}'(get).parameters.[size].schemas.default is not of type `string`
-attribute paths.'/cover/{type}/{id}'(get).responses.200.headers is not of type `object`
-attribute paths.'/cover/{type}/{id}'(get).parameters.[size].schemas.default is not of type `string`
-attribute paths.'/cover/{type}'(get).parameters.[format].schemas.default is not of type `string`
-attribute paths.'/cover/{type}/{id}'(get).parameters.[format].schemas.default is not of type `string`

```
