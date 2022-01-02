/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:22
 */
#include "web.h"

namespace trunk {
namespace typhoon {
namespace web {

RequestHandler::RequestHandler() = default;

void RequestHandler::Response(struct mg_connection *conn,
                              const nlohmann::json& data,
                              int32_t status_code) {
  std::string s = data.dump(0);
  if (status_code>=200 && status_code < 300) {
    mg_send_http_ok(conn,"application/json; charset=utf-8",s.size());
  } else if (status_code>=300 && status_code < 400) {
    mg_send_http_redirect(conn,"",status_code);
  } else if (status_code>=400 && status_code < 500) {
    mg_send_http_error(conn,status_code,"http error");
  } else {}
  mg_write(conn, s.c_str(), s.size());
}


}  // namespace web
}  // namespace typhoon
}  // namespace trunk