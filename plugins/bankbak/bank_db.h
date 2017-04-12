//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef SWP_BANK_DB_H_
#define SWP_BANK_DB_H_

#include <string>
#include <list>
#include "bank/bank_info.h"
#include "storage/data_engine.h"
#include "logic/swp_infos.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"

namespace bank_logic {

class BankDB {
 public:
  BankDB(config::FileConfig* config);
  ~BankDB();

 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace bank_logic

#endif /* SWP_HISTORY_DB_H_ */
