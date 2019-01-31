# Ting Covers Rest

## Requirements

* Docker

## Generate OpenAPI client from specs

Only used when updating the API client / working on the API; not needed for installation.

We use `--skip-validate-spec` because `openapi-generator-cli` finds some non-existent errors.

```sh

docker run --rm -v ${PWD}:/local openapitools/openapi-generator-cli generate \
    --skip-validate-spec \
    -i https://raw.githubusercontent.com/reload/ddb-coverservice-api/master/coverservice-2.0.0.yaml \
    -g php \
    -o /local

```
