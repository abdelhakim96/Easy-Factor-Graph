/**
 * Author:    Andrea Casalino
 * Created:   01.01.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#ifndef EFG_CATEGORIC_GROUP_H
#define EFG_CATEGORIC_GROUP_H

#include <categoric/Variable.h>
#include <set>

namespace EFG::categoric {
    class Group {
    public:
        Group(VariablePtr varA, VariablePtr varB);

        Group(const Group& ) = default;
        inline Group& operator=(const Group& o) {
            this->replace(o);
            return *this;
        }

        template<typename ... Vars>
        Group(VariablePtr varA, VariablePtr varB, Vars ... vars) {
            this->add(varA);
            this->add(varB, vars...);
        }

        // throw in case a variable with same name is already part of group
        void add(VariablePtr var);

        // throw in case of size mismatch
        template<typename ... Vars>
        void replace(VariablePtr varA, VariablePtr varB, Vars ... vars) {
            this->replace(Group(varA, varB, vars...));
        };

        /** \brief Returns the size of the joint domain
        */
        std::size_t size() const;

        inline const std::set<VariablePtr>& getGroup() const { return this->group; }
        
    protected:
        template<typename ... Vars>
        void add(VariablePtr var, Vars ... vars) {
            this->add(var);
            this->add(vars...);
        }

        void replace(const Group& g);

    // data
        std::set<VariablePtr> group;
    };
}

#endif
