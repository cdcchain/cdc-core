// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <consensus/operation/Operations.hpp>

namespace cdcchain {
    namespace consensus {

        struct DefineSlateOperation
        {
            static const OperationTypeEnum type;

            vector<signed_int> slate;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

    }
} // cdcchain::consensus

FC_REFLECT(cdcchain::consensus::DefineSlateOperation, (slate))
