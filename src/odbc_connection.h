#pragma once

#include "nanodbc.h"
#include "sql_types.h"
#include "time_zone.h"
#include <Rcpp.h>

namespace odbc {

enum bigint_map_t {
  i64_to_integer64,
  i64_to_integer,
  i64_to_double
};

class odbc_result;

class odbc_connection {
public:
  odbc_connection(
      std::string connection_string,
      std::string timezone = "UTC",
      std::string encoding = "");

  std::shared_ptr<nanodbc::connection> connection() const;

  void begin();
  void commit();
  void rollback() const;
  bool has_active_result() const;
  bool is_current_result(odbc_result* result) const;
  bool supports_transactions() const;

  void set_current_result(odbc_result* r);

  cctz::time_zone timezone() const;
  std::string encoding() const;

  int get_bigint_map() const;
  void set_bigint_map(int map_to);

private:
  std::shared_ptr<nanodbc::connection> c_;
  std::unique_ptr<nanodbc::transaction> t_;
  odbc_result* current_result_;
  cctz::time_zone timezone_;
  std::string encoding_;
  int bigint_map_;
};
} // namespace odbc
