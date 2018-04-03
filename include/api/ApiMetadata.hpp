// Copyright (c) 2017-2018 The CDC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#pragma once

#include <fc/io/json.hpp>
#include <functional>

namespace cdcchain {
    namespace api {

        enum MethodPrerequisites
        {
            no_prerequisites = 0,
            json_authenticated = 1,
            wallet_open = 2,
            wallet_unlocked = 4,
            connected_to_network = 8,
            simulator_open = 16
        };

        enum ParameterClassification
        {
            required_positional,
            required_positional_hidden, /* Hide in help e.g. interactive password entry */
            optional_positional,
            optional_named
        };

        struct ParameterData
        {
            std::string name;
            std::string type;
            ParameterClassification classification;
            fc::ovariant default_value;
            ParameterData(){}
            ParameterData(const ParameterData& rhs) :
                name(rhs.name),
                type(rhs.type),
                classification(rhs.classification),
                default_value(rhs.default_value)
            {}
            ParameterData(const ParameterData&& rhs) :
                name(std::move(rhs.name)),
                type(std::move(rhs.type)),
                classification(std::move(rhs.classification)),
                default_value(std::move(rhs.default_value))
            {}
            ParameterData(std::string name,
                std::string type,
                ParameterClassification classification,
                fc::ovariant default_value) :
                name(name),
                type(type),
                classification(classification),
                default_value(default_value)
            {}
            ParameterData& operator=(const ParameterData& rhs)
            {
                name = rhs.name;
                type = rhs.type;
                classification = rhs.classification;
                default_value = rhs.default_value;
                return *this;
            }
        };

        typedef std::function<fc::variant(const fc::variants& params)> JsonApiMethodType;

        struct MethodData
        {
            std::string                 name;
            JsonApiMethodType           method;
            std::string                 description;
            std::string                 return_type;
            std::vector<ParameterData>  parameters;
            uint32_t                    prerequisites;
            std::string                 detailed_description;
            std::vector<std::string>    aliases;
            bool                        cached;
        };

    }
} // end namespace cdcchain::api

FC_REFLECT_ENUM(cdcchain::api::MethodPrerequisites, (no_prerequisites)(json_authenticated)(wallet_open)(wallet_unlocked)(connected_to_network)(simulator_open))
FC_REFLECT_ENUM(cdcchain::api::ParameterClassification, (required_positional)(required_positional_hidden)(optional_positional)(optional_named))
FC_REFLECT(cdcchain::api::ParameterData, (name)(type)(classification)(default_value))
FC_REFLECT(cdcchain::api::MethodData, (name)(description)(return_type)(parameters)(prerequisites)(detailed_description)(aliases)(cached))
