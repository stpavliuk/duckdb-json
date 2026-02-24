#define DUCKDB_EXTENSION_MAIN

#include "duckdb_json_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

// OpenSSL linked through vcpkg
#include <openssl/opensslv.h>

namespace duckdb {

inline void DuckdbJsonScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "SSS " + name.GetString() + " 🐥");
	});
}

inline void DuckdbJsonOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "DuckdbJson " + name.GetString() + ", my linked OpenSSL version is " +
		                                           OPENSSL_VERSION_TEXT);
	});
}

static void LoadInternal(ExtensionLoader &loader) {
	// Register a scalar function
	auto duckdb_json_scalar_function =
	    ScalarFunction("duckdb_json", {LogicalType::VARCHAR}, LogicalType::VARCHAR, DuckdbJsonScalarFun);
	loader.RegisterFunction(duckdb_json_scalar_function);

	// Register another scalar function
	auto duckdb_json_openssl_version_scalar_function = ScalarFunction(
	    "duckdb_json_openssl_version", {LogicalType::VARCHAR}, LogicalType::VARCHAR, DuckdbJsonOpenSSLVersionScalarFun);
	loader.RegisterFunction(duckdb_json_openssl_version_scalar_function);
}

void DuckdbJsonExtension::Load(ExtensionLoader &loader) {
	LoadInternal(loader);
}
std::string DuckdbJsonExtension::Name() {
	return "duckdb_json";
}

std::string DuckdbJsonExtension::Version() const {
#ifdef EXT_VERSION_DUCKDB_JSON
	return EXT_VERSION_DUCKDB_JSON;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_CPP_EXTENSION_ENTRY(duckdb_json, loader) {
	duckdb::LoadInternal(loader);
}
}
