#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "http-header.h"

struct http_request {
	const char *method;

	const char *target;

	unsigned char version_major;
	unsigned char version_minor;

	time_t date;
	const struct http_header *header;
	struct istream *payload;

	ARRAY_TYPE(const_string) connection_options;

	unsigned int connection_close:1;
};

static inline bool
http_request_method_is(const struct http_request *req, const char *method)
{
	if (req->method == NULL)
		return FALSE;

	return (strcmp(req->method, method) == 0);
}

static inline const struct http_header_field *
http_request_header_find(const struct http_request *req, const char *name)
{
	return http_header_field_find(req->header, name);
}

static inline const char *
http_request_header_get(const struct http_request *req, const char *name)
{
	return http_header_field_get(req->header, name);
}

static inline const ARRAY_TYPE(http_header_field) *
http_request_header_get_fields(const struct http_request *req)
{
	return http_header_get_fields(req->header);
}

bool http_request_has_connection_option(const struct http_request *req,
	const char *option);
int http_request_get_payload_size(const struct http_request *req,
	uoff_t *size_r);

#endif