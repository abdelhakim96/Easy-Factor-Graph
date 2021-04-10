/**
 * Author:    Andrea Casalino
 * Created:   03.01.2020
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <nodes/Inserter.h>
#include <nodes/EvidenceSetter.h>
#include <nodes/EvidenceChanger.h>
#include <nodes/GibbsSampler.h>
#include <distribution/factor/modifiable/Factor.h>
#include <iostream>
using namespace std;

class TestModel 
    : public EFG::nodes::Inserter
    , public EFG::nodes::EvidencesSetter
    , public EFG::nodes::EvidencesChanger
    , public EFG::nodes::GibbsSampler {
public:
    TestModel() = default;

    void print() {
        std::cout << "---------------------------------------------------------" << std::endl;
        for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it) {
            std::cout << std::endl;
            std::cout << it->first->name() << std::endl;

            std::cout << "active connections: ";
            for (auto c = it->second.activeConnections.begin(); c != it->second.activeConnections.end(); ++c) {
                std::cout << " " << c->first->variable->name();
            }
            std::cout << std::endl;

            std::cout << "inactive connections: ";
            for (auto c = it->second.disabledConnections.begin(); c != it->second.disabledConnections.end(); ++c) {
                std::cout << " " << c->first->variable->name();
            }
            std::cout << std::endl;
        }
    };
};

EFG::distribution::DistributionPtr makeSimpleFactor(EFG::categoric::VariablePtr a, EFG::categoric::VariablePtr b, bool corrAnti) {
    return std::make_shared<EFG::distribution::factor::cnst::Factor>(EFG::categoric::Group(a, b), corrAnti);
};

//int main() {
//    EFG::categoric::VariablePtr varA = EFG::categoric::makeVariable(3, "A");
//    EFG::categoric::VariablePtr varB = EFG::categoric::makeVariable(3, "B");
//    EFG::categoric::VariablePtr varC = EFG::categoric::makeVariable(3, "C");
//    EFG::categoric::VariablePtr varD = EFG::categoric::makeVariable(3, "D");
//
//    TestModel model;
//
//    {
//        auto potA = std::make_shared<EFG::distribution::factor::modif::Factor>(EFG::categoric::Group(varA));
//        potA->add(EFG::Combination({ 0 }), 1.f);
//        potA->add(EFG::Combination({ 1 }), 2.f);
//        model.Insert(potA);
//    }
//
//    model.Insert(makeSimpleFactor(varA, varB, true));
//    model.Insert(makeSimpleFactor(varA, varC, true));
//    model.Insert(makeSimpleFactor(varB, varC, true));
//    model.Insert(makeSimpleFactor(varC, varD, true));
//
//    model.print();
//
//    std::map<std::string, const std::size_t> evidences;
//    evidences.emplace("C", 0);
//    model.resetEvidences(evidences);
//
//    model.addEvidence("D", 0);
//
//    model.print();
//
//    model.Insert(makeSimpleFactor(varB, varD, true));
//    model.print();
//
//    model.setEvidences(std::vector<std::size_t>{1,1});
//
//    return EXIT_SUCCESS;
//}

int main() {
    EFG::categoric::VariablePtr varA = EFG::categoric::makeVariable(3, "A");
    EFG::categoric::VariablePtr varB = EFG::categoric::makeVariable(3, "B");
    EFG::categoric::VariablePtr varC = EFG::categoric::makeVariable(3, "C");

    TestModel model;

    //{
    //    auto potA = std::make_shared<EFG::distribution::factor::modif::Factor>(EFG::categoric::Group(varA));
    //    potA->add(EFG::Combination({ 0 }), 1.f);
    //    potA->add(EFG::Combination({ 1 }), 2.f);
    //    model.Insert(potA);
    //}

    model.Insert(makeSimpleFactor(varA, varB, false));
    model.Insert(makeSimpleFactor(varA, varC, false));
    model.Insert(makeSimpleFactor(varB, varC, false));

   auto samples =  model.getHiddenSetSamples(10);

   return EXIT_SUCCESS;
}







//// Refer also to Section 'Sample 02: Belief propagation, part A' of the documentation
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//#include <model/Graph.h>
//#include "../Utilities.h"
//using namespace EFG;
//
//
//void part_01();
//void part_02();
//void part_03();
//
//int main() {
//
//	///////////////////////////////////////////
//	// part 01 graph with a single potential //	
//	///////////////////////////////////////////
//	cout << "-----------------------\n";
//	cout << "part 01 \n\n\n";
//	cout << "-----------------------\n";
//	part_01();
//
//	///////////////////////////////////////////////////////
//	// part 02 graph with two potentials and 3 variables //	
//	///////////////////////////////////////////////////////
//	cout << "-----------------------\n";
//	cout << "part 02 \n\n\n";
//	cout << "-----------------------\n";
//	part_02();
//
//	////////////////////////////////////////////////////
//	// part 03 belief degradation with the chain size //	
//	////////////////////////////////////////////////////
//	cout << "-----------------------\n";
//	cout << "part 03 \n\n\n";
//	cout << "-----------------------\n";
//	part_03();
//	
//	return 0;
//}
//
//void part_01() {
//
//	//create a simple graph with two nodes
//	CategoricVariable A(2, "A");
//	CategoricVariable B(2, "B");
//
//	float teta = 2.f;
//	float Z = 1.f + expf(teta);
//
//	pot::Factor shape_temp({ &A, &B });
//	shape_temp.AddValue(vector<size_t>{ 1,1 }, 1.f);
//	shape_temp.AddValue(vector<size_t>{ 0,0 }, 1.f);
//	pot::ExpFactor Psi1(shape_temp, teta);
//
//	model::Graph graph_1;
//	graph_1.Insert(Psi1); //the potential passed as input will be internally copied, assuming the same set of variables, which are in turn copied assuming the same names and sizes
//	vector<float> marginals;
//
//	//make a new belief propagation setting B=0 as observation
//	graph_1.SetEvidences(vector<pair<string, size_t>>{ {"B" , 0}});
//
//	//compute the marginal probability of A s.t. the evidence of B: values are compared with the theoretical result (see 'Sample 02: Belief propagation, part A / part 01')
//	marginals = graph_1.GetMarginalDistribution("A");
//	cout << "P(A|B=0)" << endl;
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ expf(teta) / Z, 1.f / Z }));
//	print_distribution(marginals);
//	cout << endl << endl;
//
//	//make a new belief propagation setting B1=1 as observation
//	graph_1.SetEvidences( vector<size_t>{ 1 });
//
//	//compute the new marginals
//	marginals = graph_1.GetMarginalDistribution("A");
//	cout << "P(A|B=1)" << endl;
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ 1.f / Z, expf(teta) / Z }));
//	print_distribution(marginals);
//	cout << endl << endl;
//
//}
//
//void part_02() {
//
//	//build the graph described in 'Sample 02: Belief propagation, part A / part 02'
//	CategoricVariable A(2, "A");
//	CategoricVariable B(2, "B");
//	CategoricVariable C(2, "C");
//
//	float alfa = 0.5f, beta = 1.f;
//
//	pot::ExpFactor Psi_BC = pot::ExpFactor::makeFactor(alfa, vector<CategoricVariable*>{ &B, &C }, true);
//
//	pot::ExpFactor Psi_AB = pot::ExpFactor::makeFactor(beta, vector<CategoricVariable*>{ &A, &B }, true);
//
//	model::Graph graph_2;
//	graph_2.Insert(Psi_AB);
//	graph_2.Insert(Psi_BC);
//
//	//make a new belief propagation setting C=1 as observation
//	graph_2.SetEvidences(vector<pair<string, size_t>>{ {"C" , 1} });
//
//	float Z = 1.f + expf(alfa) + expf(beta) + expf(alfa)*expf(beta);
//
//	//compute the marginals of A,B and then compare results with the theoretial ones 
//	//(see also Sample 2/ part 2 of the documentation)
//	vector<float> marginals = graph_2.GetMarginalDistribution( "B");
//	cout << "P(B|C=1)\n";
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ (1.f + expf(beta)) / Z, expf(alfa)*(1.f + expf(beta)) / Z }));
//	print_distribution(marginals);
//
//	marginals = graph_2.GetMarginalDistribution("A");
//	cout << "P(A|C=1)\n";
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ (expf(alfa) + expf(beta)) / Z, (1.f + expf(alfa) * expf(beta)) / Z }));
//	print_distribution(marginals);
//
//
//	//make a new belief propagation setting B=1 as observation
//	graph_2.SetEvidences(vector<pair<string, size_t>>{ {"B", 1} });
//
//	Z = 1.f + expf(beta);
//
//	marginals = graph_2.GetMarginalDistribution("A");
//	cout << "P(A|B=1)\n";
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ 1.f / Z, expf(beta) / Z }));
//	print_distribution(marginals);
//
//	Z = 1.f + expf(alfa);
//
//	marginals =  graph_2.GetMarginalDistribution("C");
//	cout << "P(C|B=1)\n";
//	cout << "theoretical " << endl;
//	print_distribution(list<float>({ 1.f / Z, expf(alfa) / Z }));
//	print_distribution(marginals);
//
//}
//
//void process_chain(const std::size_t& chain_size, const std::size_t& var_size, const float& w) {
//
//	if (chain_size < 2) throw 0; //invalid chain size
//
//	//build the set of variables in the chain
//	vector<CategoricVariable> Y;
//	Y.reserve(chain_size);
//	for (size_t k = 0; k < chain_size; k++)
//		Y.emplace_back(var_size, "Y_" + to_string(k));
//
//	model::Graph graph;
//
//	//build the correlating potentials and add it to the chain
//	for (size_t k = 1; k < chain_size; k++) {
//		graph.InsertMove(pot::ExpFactor::makeFactor(w, vector<CategoricVariable*>{ &Y[k - 1], & Y[k] }, true)); //the rvalue built is moved inside the graph
//	}
//
//	//set Y_0 as an observations and compute the marginals of the last variable in the chain
//	graph.SetEvidences(vector<pair<string, size_t>>{ {Y.front().GetName(), 0} });
//	vector<float> prob = graph.GetMarginalDistribution(Y.back().GetName());
//
//	print_distribution(prob);
//	cout << endl;
//
//}
//void part_03() {
//
//	//build chain graphs described in 'Sample 02: Belief propagation, part A / part 03'
//
//	size_t Dom_size = 5;
//
//	for (int k = 2; k <= 10; k++) {
//		cout << "chain size equal to " << k << ", marginals of Y_n:   ";
//		process_chain(k, Dom_size, 3.5f);
//	}
//
//}
