#pragma once

#include "duckdb.hpp"

namespace duckdb {

class DuckdbJsonExtension : public Extension {
public:
	void Load(ExtensionLoader &db) override;
	std::string Name() override;
	std::string Version() const override;
};

} // namespace duckdb
