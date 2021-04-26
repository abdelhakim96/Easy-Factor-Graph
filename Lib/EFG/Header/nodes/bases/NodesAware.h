/**
 * Author:    Andrea Casalino
 * Created:   01.01.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#ifndef EFG_NODES_NODES_AWARE_H
#define EFG_NODES_NODES_AWARE_H

#include <nodes/Node.h>
#include <nodes/bases/Base.h>

namespace EFG::nodes {
    class NodesAware : virtual public Base {
    public:
        /**
         * @return all the variables (hidden or observed) in the model
         */
        std::set<categoric::VariablePtr> getVariables() const;

        categoric::VariablePtr findVariable(const std::string& name) const;

    protected:
        /**
         * @brief The set of variables part of the model, with the connectivity information
         */
        std::map<categoric::VariablePtr, Node> nodes;
    };
}

#endif