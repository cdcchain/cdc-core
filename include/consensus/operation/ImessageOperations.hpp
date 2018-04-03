// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once


#include <consensus/operation/Operations.hpp>
#include <consensus/Types.hpp>

namespace cdcchain {
    namespace consensus {
        struct ImessageMemoOperation
        {
            static const OperationTypeEnum type;
            string imessage;
            ImessageMemoOperation(){}
            ImessageMemoOperation(std::string imess) :imessage(imess){}
            void evaluate(TransactionEvaluationState& eval_state)const;
        };
    }
}
FC_REFLECT(cdcchain::consensus::ImessageMemoOperation, (imessage))
