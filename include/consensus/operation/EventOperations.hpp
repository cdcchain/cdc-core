// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include "consensus/Types.hpp"
#include "consensus/operation/Operations.hpp"

namespace cdcchain {
    namespace consensus {

        struct EventOperation{
            static const OperationTypeEnum type;

            EventOperation(){}

            EventOperation(const ContractIdType& id, const std::string& event_type, const std::string& event_param) : id(id)
            {
                if (event_type.length() > EVENT_TYPE_MAX_LEN)
                    this->event_type = event_type.substr(0, EVENT_TYPE_MAX_LEN);
                else
                    this->event_type = event_type;
                this->is_truncated = false;
                this->event_param = event_param;

                if (this->event_param.length() > EVENT_PARAM_MAX_LEN)
                {
                    this->is_truncated = true;
                    this->event_param = this->event_param.substr(0, EVENT_PARAM_MAX_LEN);
                }
            }

            ContractIdType id;
            std::string event_type;
            std::string event_param;
            bool is_truncated;

            void evaluate(TransactionEvaluationState& eval_state)const;
        };

    }
}


FC_REFLECT(cdcchain::consensus::EventOperation, (id)(event_type)(event_param)(is_truncated))
