//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "bank/bank_logic.h"
#include "bank/bank_proto_buf.h"
#include "bank/operator_code.h"
#include "bank/errno.h"
#include "bank/schduler_engine.h"
#include "logic/swp_infos.h"
#include "comm/comm_head.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/bank/bank_config.xml"

#define TIME_DISTRIBUTION_TASK 10001

namespace bank_logic {

Banklogic *Banklogic::instance_ = NULL;

Banklogic::Banklogic() {
  if (!Init())
    assert(0);
}

Banklogic::~Banklogic() {
  if (bank_db_) {
    delete bank_db_;
    bank_db_ = NULL;
  }
  //history_logic::HistoryEngine::FreeSchdulerManager();
  //history_logic::HistoryEngine::FreeHistoryEngine();
}

bool Banklogic::Init() {
  bool r = false;
  manager_schduler::SchdulerEngine* (*schduler_engine)(void);
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  bank_db_ = new bank_logic::BankDB(config);

  std::string schduler_library = "./data_share.so";
  std::string schduler_func = "GetManagerSchdulerEngine";
  schduler_engine = (manager_schduler::SchdulerEngine* (*)(void))
  logic::SomeUtils::GetLibraryFunction(
  schduler_library, schduler_func);schduler_engine_
  = (*schduler_engine)();
  if (schduler_engine_ == NULL)
    assert(0);

  //history_logic::HistoryEngine::GetSchdulerManager()->InitSchdulerEngine(
    //  schduler_engine_);
  return true;
}

Banklogic *Banklogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Banklogic();
  return instance_;
}

void Banklogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Banklogic::OnBankConnect(struct server *srv, const int socket) {
  std::string ip;
  int port;
  logic::SomeUtils::GetIPAddress(socket, ip, port);
  LOG_MSG2("ip {%s} prot {%d}", ip.c_str(), port);
  return true;
}

bool Banklogic::OnBankMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket %d", socket);
    send_error(socket, ERROR_TYPE, ERROR_TYPE, FORMAT_ERRNO);
    return false;
  }

  switch (packet->operate_code) {
    default:
      break;
  }
  return true;
}

bool Banklogic::OnBankClose(struct server *srv, const int socket) {
  return true;
}

bool Banklogic::OnBroadcastConnect(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  return true;
}

bool Banklogic::OnBroadcastMessage(struct server *srv, const int socket,
                                      const void *msg, const int len) {

  return true;
}

bool Banklogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Banklogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
    if (srv->add_time_task != NULL) {
      //srv->add_time_task(srv, "history", TIME_DISTRIBUTION_TASK, 3, -1);
    }
  }
  return true;
}

bool Banklogic::OnTimeout(struct server *srv, char *id, int opcode,
                             int time) {
  switch (opcode) {
    default:
      break;
  }
  return true;
}


}  // namespace trades_logic
