//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef SWP_PAY_DB_H_
#define SWP_PAY_DB_H_

#include <string>
#include <list>
#include "storage/data_engine.h"
#include "logic/swp_infos.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
//#include "thread/base_thread_lock.h"

namespace pay_logic {

class PayDB {
 public:
  PayDB(config::FileConfig* config);
  ~PayDB();

 public:
  bool OnCreateRechargeOrder(const int64 uid, const int64 rid, const double price,
                             const int32 rtype);

  bool OnCreateWithdrawOrder(const int64 uid, const int64 rid,
                                  const double price, const int64 bid,
				  const int64 status = 0); 
  bool OnUpdateRechargeOrder(const int64 uid, const int64 rid, const int32 status,
                             const int32 rtype);

  bool OnUpdateCallBackRechargeOrder(const int64 rid,const double price,
                                     const std::string& transaction_id,
                                     const int32 astatus,int64& uid,
                                     double& balance);
  bool OnUpdateCallBackWithdrawOrder(const std::string& rid, const double price,
                                          const std::string& transaction_id,
                                          const int32 astatus, int64& uid,
                                          double& balance); 
 public:
  static void CallCreateRechargeOrder(void* param, base_logic::Value* value);
  static void CallUpdateCallBackRechargeOrder(void* param, base_logic::Value* value);
 private:
  base_logic::DataEngine* mysql_engine_;
//  threadrw_t*                                   pay_callback_; 
};

}  // namespace history_logic

#endif /* SWP_HISTORY_DB_H_ */
