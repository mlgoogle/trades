// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_interface.h
// Created on: 2016年8月10日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_INTERFACE_H_
#define PLUGINS_USER_USER_INTERFACE_H_

#include "basic/basictypes.h"
#include "config/config.h"
#include "net/proto_buf.h"
#include "share/data_share_mgr.h"
#include "net/comm_head.h"

#include "user/user_mysql.h"
namespace user {
class UserInterface {
 private:
  UserInterface();
  ~UserInterface();

 public:
  static UserInterface* GetInstance();
  static void FreeInstance();
  void test();
 public:
  void InitConfig(config::FileConfig* config);

  int32 OnHeartbeat(const int32 socket, PacketHead* packet);

  int32 OnUserInfo(const int32 socket, PacketHead* packet);
  
  int32 OnAccountInfo(const int32 socket, PacketHead* packet);

  int32 OnOrderList(const int32 socket, PacketHead* packet);

  int32 OnOrderDetail(const int32 socket, PacketHead* packet);

  int32 OnBankcardList(const int32 socket, PacketHead* packet);

  int32 OnBindBankcard(const int32 socket, PacketHead* packet);

  int32 OnUnbindBankcard(const int32 socket, PacketHead* packet);

  int32 OnChangeDefaultBankcard(const int32 socket, PacketHead* packet);
  
  int32 OnBankAccountInfo(const int32 socket, PacketHead* packet);

  int32 OnCreditList(const int32 socket, PacketHead* packet);

  int32 OnCreditDetail(const int32 socket, PacketHead* packet);

  int32 OnUserWithdraw(const int32 socket, PacketHead* packet);

  int32 OnUserWithdrawList(const int32 socket, PacketHead* packet);

  int32 OnUserWithdrawDetail(const int32 socket, PacketHead* packet);

  int32 OnObtainVerifyCode(const int32 socket, PacketHead* packet);

  int32 OnChangeUserInfo(const int32 socket, PacketHead* packet);
  
  int32 OnWXPlaceOrder(const int32 socket, PacketHead* packet);

  int32 OnWXPayClientResponse(const int32 socket, PacketHead* packet);

  int32 OnWXPayServerResponse(const int32 socket, PacketHead* packet);

  int32 OnUnionpayPlaceOrder(const int32 socket, PacketHead* packet);

  int32 OnUnionpayPayClientResponse(const int32 socket, PacketHead* packet);

  int32 OnUnionpayPayServerResponse(const int32 socket, PacketHead* packet);

  int32 OnDeviceToken(const int32 socket, PacketHead* packet);

  int32 OnAlipayServer(const int32 socket, PacketHead* packet);

  int32 OnAlipayClient(const int32 socket, PacketHead* packet);
  
  int32 OnCheckSMSCode(const int32 socket, PacketHead* packet);

  int32 CheckHeartLoss();
//更新共享数据，旅游分享和技能分享
  int32 InitShareGuide();
  //定时监测订单状态
  int32 NopayOrderStatusCheck();
  int32 CloseSocket(const int fd);

  void SendPacket(const int socket, PacketHead* packet);

  void SendError(const int socket, PacketHead* packet, int32 Onerr, int16 opcode);

  void SendMsg(const int socket, PacketHead* packet, DicValue* dic,
               int16 opcode);

  void InitShareDataMgr(share::DataShareMgr* data);
 private:
  int32 InitShareType();
  int32 InitShareDetails();
  int32 InitShareSkills();
  int32 SplitString(const std::string &in, const char ch, std::vector<std::string> &out);

  static UserInterface* instance_;
  UserMysql* user_mysql_;
  share::DataShareMgr* data_share_mgr_;
};

}  // namespace user



#endif  // PLUGINS_USER_USER_INTERFACE_H_
