# Ting Covers Rest

## Requirements

* Docker

## Generate OpenAPI client from specs

```sh

docker run --rm -v ${PWD}:/local openapitools/openapi-generator-cli generate \
    --skip-validate-spec \
    -i https://raw.githubusercontent.com/reload/ddb-coverservice-api/master/coverservice-2.0.0.yaml \
    -g php \
    -o /local/openapi

```
