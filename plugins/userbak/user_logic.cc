// Copyright (c) 2016 The user Authors. All rights reserved.
// user_logic.cc
// Created on: 2016年8月8日
// Author: Paco

#include "user/user_logic.h"

#include <assert.h>
#include <typeinfo>
#include <stdio.h>
#include <string.h>

#include "core/common.h"
#include "basic/basictypes.h"
#include "config/config.h"
#include "basic/native_library.h"
#include "logic/base_values.h"

#include "user/user_interface.h"
#include "user/user_opcode.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "logic/logic_unit.h"
#include "comm/comm_head.h"

#define DEFAULT_CONFIG_PATH "./plugins/user/user_config.xml"
static char *host ="http://sdk.open.api.getui.net/apiex.htm";
static char *appKey = "yEIPB4YFxw64Ag9yJpaXT9";
static char *masterSecret = "bMsRgf7RrA6jBG4sNbv0F6";

namespace user {
Userlogic* Userlogic::instance_ = NULL;
int Userlogic::server_fd_ = -1;	

Userlogic::Userlogic() {
  server_fd_ = -1;
  if (!Init())
    assert(0);
}

Userlogic::~Userlogic() {
}

bool Userlogic::Init() {
  bool r = false;
  /*Result res = pushInit(host, appKey, masterSecret, "编码");
   if(res!=SUCCESS){
     LOG_ERROR("DataShareMgr pushInit err");
   }*/
  user_manager_ = UserManager::GetInstance();
  config::FileConfig* config = config::FileConfig::GetFileConfig();
  std::string path = DEFAULT_CONFIG_PATH;
  if (config == NULL) {
    LOG_ERROR("Userlogic config init error");
    return false;
  }
  r = config->LoadConfig(path);
  if (!r) {
    LOG_ERROR("user config load error");
    return false;
  }
  UserInterface::GetInstance()->InitConfig(config);
  InitShareData();
  
  return true;
}
	
bool Userlogic::InitShareData() {
  basic::libhandle  handle = NULL;
  handle = basic::load_native_library("./data.so");
  if (handle==NULL){
    LOG_ERROR("Can't load path data.so\n");
  }
  LOG_MSG("load data.so success");
  share::DataShareMgr* (*pengine) (void);
  pengine = (share::DataShareMgr *(*)(void))basic::get_function_pointer(handle, "GetDataShareMgr");
  if(pengine==NULL){
    LOG_ERROR("Can't find GetDataShareMgr\n");
    return false;
  }
  share::DataShareMgr* data_engine_ = (*pengine)();
  UserInterface::GetInstance()->InitShareDataMgr(data_engine_);
  return false;
}

Userlogic* Userlogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Userlogic();
  return instance_;
}

void Userlogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Userlogic::OnUserConnect(struct server *srv, const int socket) {
  LOG_MSG2("socket has be connected:", socket);
  return true;
}

bool Userlogic::OnUserMessage(struct server *srv, const int socket,
                              const void *msg, const int len) {
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  PacketHead *packet = NULL;
  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket:%d", socket);
    send_error(socket, ERROR_TYPE,ERROR_TYPE, JSON_FORMAT_ERR);
    return false;
  }
  
  if (packet->type == USER_TYPE)
    user_manager_->AssignPacket(socket, packet);
  
  return true;
}

bool Userlogic::OnUserClose(struct server *srv, const int socket) {
  LOG_MSG2("socket has be closed:", socket);
  user_manager_->OnSockClose(socket);
  LOG_MSG2("OnSockClose:", socket);
  return true;
}

bool Userlogic::OnBroadcastConnect(struct server *srv, const int socket,
                                   const void *msg, const int len) {
  server_fd_ = socket;
  return true;
}

bool Userlogic::OnBroadcastMessage(struct server *srv, const int socket,
                                   const void *msg, const int len
                                   ) {
  /*  bool r = false;
  int32 err = 0;
  char* msg_c = new char[len + 1];
  memcpy(msg_c, msg, len);
  msg_c[len] = '\0';
  LOG_MSG("OnBroadcastMessage:len-" << len);
  PacketHead packet_head(msg_c);
  delete[] msg_c;
  msg_c = NULL;
  user_manager_->AssignPacket(socket, &packet_head);*/
  return true;
}

bool Userlogic::OnBroadcastClose(struct server *srv, const int socket) {
  server_fd_ = -1;
  
  pthread_t tid;
  if (pthread_create(&tid, 0, Userlogic::AutoReconnectToServer, (void*)srv) == 0)
	pthread_detach(tid);
  else
	LOG_ERROR("can not create thread AutoReconnectToserver");
  
  return true;
}

void* Userlogic::AutoReconnectToServer(void* arg) {
  struct server* srv = (struct server*)arg;
  int ret = 0;
  
  do {
	ret = srv->create_reconnects(srv);
	sleep(1);
  } while (ret < 0);
  LOG_MSG2("try reconnect remote server:", ret);
}
	
bool Userlogic::OnInitTimer(struct server *srv) {
  //srv->add_time_task(srv, "user", CONNECT_CKECK, 15, -1);
  srv->add_time_task(srv, "user", SHARE_DATA_INIT, 3, 1);
  srv->add_time_task(srv, "user", SHARE_DATA_INIT_TEN, 10*60, -1);
  srv->add_time_task(srv, "user", ORDER_STATUS_CHECK, 2*60, -1);
  return true;
}



bool Userlogic::OnTimeout(struct server *srv, char *id, int opcode, int time) {
  switch (opcode) {
    case CONNECT_CKECK: {
      user_manager_->CheckHeartLoss();
      break;
    }
    case SHARE_DATA_INIT: {
      user_manager_->InitShareGuideData();
      break;
    }
    case SHARE_DATA_INIT_TEN: {
      user_manager_->InitShareGuideData();
      break;
    }
    case ORDER_STATUS_CHECK: {
      user_manager_->OrderStatusCheck();
      break;
    }
  }
  return true;
}

}  // namespace user

