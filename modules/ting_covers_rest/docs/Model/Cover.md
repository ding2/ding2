# Cover

## Properties
Name | Type | Description | Notes
------------ | ------------- | ------------- | -------------
**type** | [**\OpenAPI\Client\Model\Type**](Type.md) |  | 
**id** | **string** | An identifier URI consisting of identifier type as scheme (\&quot;isbn\&quot;, \&quot;faust\&quot;, \&quot;pid\&quot;, \&quot;issn\&quot;,  or \&quot;issn-vol-nr\&quot;) and the identifier itself. **Notice:** A cover can be known under more than one type/ID. | 
**quality** | **string** | The quality of the cover; digital or scanned. Only used on PUT and POST. | 
**copyright** | **string** | Copyright information for the cover. Only used on PUT and POST. | [optional] 
**source** | **string** | Information about the origin of the image. Only used on PUT and POST. | [optional] 
**image_data** | **string** | Base64 encoded cover image. Only used on PUT and POST. | 
**image_urls** | [**\OpenAPI\Client\Model\CoverImageUrls[]**](CoverImageUrls.md) | A list of the all images (the formats and sizes matching the request) for the cover. Only used on GET. | 

[[Back to Model list]](../README.md#documentation-for-models) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to README]](../README.md)


