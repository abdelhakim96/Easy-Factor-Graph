/**
 * Author:    Andrea Casalino
 * Created:   01.01.2021
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#pragma once

#include <EasyFactorGraph/categoric/Variable.h>
#include <EasyFactorGraph/misc/SmartSet.h>

#include <vector>

namespace EFG::categoric {
using VariablesSoup = std::vector<VariablePtr>;

using VariablesSet = SmartSet<Variable>;

VariablesSet to_vars_set(const VariablesSoup &soup);

/**
 * @brief An ensemble of categoric variables. Each variable in the ensemble
 * should have its own unique name.
 */
class Group {
public:
  /**
   * @param the initial variables of the group
   */
  explicit Group(const VariablesSoup &group);

  /**
   * @param the initial variable to put in the group
   */
  explicit Group(const VariablePtr &var);

  /**
   * @param the first initial variable to put in the group
   * @param the second initial variable to put in the group
   * @param all the other initial variables
   */
  template <typename... Vars>
  Group(const VariablePtr &varA, const VariablePtr &varB, const Vars &...vars) {
    this->add(varA, varB, vars...);
  }

  /**
   * @throw In case of size mismatch with the previous variables set:
   * the sizes of the 2 groups should be the same and the elements in
   * the same positions must have the same domain size.
   */
  /**
   * @brief replaces the group of variables.
   * @throw In case of size mismatch with the previous variables set:
   * the sizes of the 2 groups should be the same and the elements in
   * the same positions must have the same domain size
   */
  void replaceVariables(const VariablesSoup &new_variables);

  inline bool operator==(const Group &o) const {
    return (this->group_sorted == o.group_sorted);
  };

  /**
   * @param the variable to add in the group
   * @throw in case a variable with the same name is already part of the group
   */
  void add(const VariablePtr &var);

  template <typename... Vars>
  void add(const VariablePtr &var, const Vars &...vars) {
    this->add(var);
    this->add(vars...);
  }

  /** @return the size of the joint domain of the group.
   * For example the group <A,B,C> with sizes <2,4,3> will have a joint domain
   * of size 2x4x3 = 24
   */
  std::size_t size() const;

  inline const VariablesSoup &getVariables() const { return this->group; }
  inline const VariablesSet &getVariablesSet() const {
    return this->group_sorted;
  }

protected:
  Group() = default;

  VariablesSoup group;
  VariablesSet group_sorted;
};

VariablesSet &operator-=(VariablesSet &subject, const VariablesSet &to_remove);

VariablesSet get_complementary(const VariablesSet &entire_set,
                               const VariablesSet &subset);
} // namespace EFG::categoric
