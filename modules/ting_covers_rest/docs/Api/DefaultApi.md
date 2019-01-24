# OpenAPI\Client\DefaultApi

All URIs are relative to *https://example.com/coverservice/2.0*

Method | HTTP request | Description
------------- | ------------- | -------------
[**coverTypeGet**](DefaultApi.md#coverTypeGet) | **GET** /cover/{type} | Search covers
[**coverTypeIdGet**](DefaultApi.md#coverTypeIdGet) | **GET** /cover/{type}/{id} | Get cover


# **coverTypeGet**
> \OpenAPI\Client\Model\Cover[] coverTypeGet($type, $id, $format, $generic, $size, $limit, $offset)

Search covers

# Search multiple covers Get covers by ID in specific image format(s), specific image size(s) and with or without generic covers. The results can be paginated by specifiying an offset and a page limit. The response will contain a \"Link\" HTTP header according to RFC5988 pointing to previous and/or next page of results.

### Example
```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');

$apiInstance = new OpenAPI\Client\Api\DefaultApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$type = new \OpenAPI\Client\Model\\OpenAPI\Client\Model\Type(); // \OpenAPI\Client\Model\Type | # ID type The type of the ID, i.e. \"isbn\", \"faust\", \"pid\", \"issn\", or \"issn-vol-nr\".
$id = ["870970-basis:26957087","870970-basis:53969127"]; // string[] | # ID A list of IDs.
$format = array('format_example'); // string[] | # Formats A list of image formats you want to receive the cover(s) in.
$generic = true; // bool | # Generic covers If we should include generic front page covers or not for ressources without a cover.
$size = array('size_example'); // string[] | # Image sizes A list of image sizes (Cloudinary transformations) for the cover(s) you want to receive.
$limit = 56; // int | # Pagination page limit Number of covers per page for paginated results.
$offset = 0; // int | # Pagination page offset Offset for paginated results.

try {
    $result = $apiInstance->coverTypeGet($type, $id, $format, $generic, $size, $limit, $offset);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling DefaultApi->coverTypeGet: ', $e->getMessage(), PHP_EOL;
}
?>
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **type** | [**\OpenAPI\Client\Model\Type**](../Model/.md)| # ID type The type of the ID, i.e. \&quot;isbn\&quot;, \&quot;faust\&quot;, \&quot;pid\&quot;, \&quot;issn\&quot;, or \&quot;issn-vol-nr\&quot;. |
 **id** | [**string[]**](../Model/string.md)| # ID A list of IDs. |
 **format** | [**string[]**](../Model/string.md)| # Formats A list of image formats you want to receive the cover(s) in. | [optional]
 **generic** | **bool**| # Generic covers If we should include generic front page covers or not for ressources without a cover. | [optional] [default to true]
 **size** | [**string[]**](../Model/string.md)| # Image sizes A list of image sizes (Cloudinary transformations) for the cover(s) you want to receive. | [optional]
 **limit** | **int**| # Pagination page limit Number of covers per page for paginated results. | [optional]
 **offset** | **int**| # Pagination page offset Offset for paginated results. | [optional] [default to 0]

### Return type

[**\OpenAPI\Client\Model\Cover[]**](../Model/Cover.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../../README.md#documentation-for-api-endpoints) [[Back to Model list]](../../README.md#documentation-for-models) [[Back to README]](../../README.md)

# **coverTypeIdGet**
> \OpenAPI\Client\Model\Cover coverTypeIdGet($type, $id, $format, $generic, $size)

Get cover

# Get one cover Get one cover by type and ID in specific image format(s), specific image size(s) and with or without generic covers.

### Example
```php
<?php
require_once(__DIR__ . '/vendor/autoload.php');

$apiInstance = new OpenAPI\Client\Api\DefaultApi(
    // If you want use custom http client, pass your client which implements `GuzzleHttp\ClientInterface`.
    // This is optional, `GuzzleHttp\Client` will be used as default.
    new GuzzleHttp\Client()
);
$type = new \OpenAPI\Client\Model\\OpenAPI\Client\Model\Type(); // \OpenAPI\Client\Model\Type | # ID type The type of the ID, i.e. \"isbn\", \"faust\", \"pid\", \"issn\", or \"issn-vol-nr\".
$id = 'id_example'; // string | # ID The ID of the cover.
$format = array('format_example'); // string[] | # Formats A list of image formats you want to receive the cover(s) in.
$generic = true; // bool | # Generic covers If we should include generic front page covers or not for ressources without a cover.
$size = array('size_example'); // string[] | # Image sizes A list if image sizes (Cloudinary transformations) for the cover(s) you want to receive.

try {
    $result = $apiInstance->coverTypeIdGet($type, $id, $format, $generic, $size);
    print_r($result);
} catch (Exception $e) {
    echo 'Exception when calling DefaultApi->coverTypeIdGet: ', $e->getMessage(), PHP_EOL;
}
?>
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **type** | [**\OpenAPI\Client\Model\Type**](../Model/.md)| # ID type The type of the ID, i.e. \&quot;isbn\&quot;, \&quot;faust\&quot;, \&quot;pid\&quot;, \&quot;issn\&quot;, or \&quot;issn-vol-nr\&quot;. |
 **id** | **string**| # ID The ID of the cover. |
 **format** | [**string[]**](../Model/string.md)| # Formats A list of image formats you want to receive the cover(s) in. | [optional]
 **generic** | **bool**| # Generic covers If we should include generic front page covers or not for ressources without a cover. | [optional] [default to true]
 **size** | [**string[]**](../Model/string.md)| # Image sizes A list if image sizes (Cloudinary transformations) for the cover(s) you want to receive. | [optional]

### Return type

[**\OpenAPI\Client\Model\Cover**](../Model/Cover.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../../README.md#documentation-for-api-endpoints) [[Back to Model list]](../../README.md#documentation-for-models) [[Back to README]](../../README.md)

