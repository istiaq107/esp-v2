#include <string>

#include "http_filter.h"

#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Http {

HttpSampleDecoderFilterConfig::HttpSampleDecoderFilterConfig(
    const sample::Decoder& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

HttpSampleDecoderFilter::HttpSampleDecoderFilter(
    HttpSampleDecoderFilterConfigSharedPtr config)
    : config_(config) {}

HttpSampleDecoderFilter::~HttpSampleDecoderFilter() {}

void HttpSampleDecoderFilter::onDestroy() {}

const LowerCaseString HttpSampleDecoderFilter::headerKey() const {
  std::cout << "config_ key is: " << config_->key() << "=============\n";
  return LowerCaseString(config_->key());
}

const std::string HttpSampleDecoderFilter::headerValue() const {
  return config_->val();
}

FilterHeadersStatus HttpSampleDecoderFilter::decodeHeaders(HeaderMap& headers,
                                                           bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterDataStatus HttpSampleDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus HttpSampleDecoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void HttpSampleDecoderFilter::setDecoderFilterCallbacks(
    StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

}  // namespace Http
}  // namespace Envoy