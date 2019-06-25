#include "catch.hpp"
#include "Execution.hpp"
#include <sstream>

GGraphNode *    creatNode(node_type type, char name, bool is_not, char value) {
    GGraphNode *node = new GGraphNode();
    node->type = type;
    node->name = name;
    node->value = value;
    (void)is_not;
    return node;
}

TEST_CASE( "EXECUTION", "[execution]" ) {

    SECTION( "Init" ) {

        GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

        GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
        nodeA->in_list.push_back({nodeB, false});

        GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

        GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);
        nodeC->in_list.push_back({nodeD, false});

        std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA, false}};

        CHECK_NOTHROW(Execution(queriesNode));

    }

    SECTION( "Get Node" ) {
        GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

        GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
        nodeA->in_list.push_back({nodeB, false});

        GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

        GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);
        nodeC->in_list.push_back({nodeD, false});

        std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA, false}};

        Execution   *exec = new Execution(queriesNode);

        std::list<std::pair<GGraphNode*, bool>> queries = exec->getQueriesNode();

        CHECK(queries == queriesNode);

        GGraphNode* node = queries.begin()->first;

        CHECK(node == nodeA);
        CHECK(node->type == FACT_NODE);
        CHECK(node->name == 'A');
        CHECK(node->value == 0);

        std::list<std::pair<GGraphNode*, bool>>::iterator it = queries.begin();
        it++;
        CHECK(it == queries.end());

        delete exec;
    }

    SECTION( "Search Value" ) {

        SECTION( "Simple value False" ) {
            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});

            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);
            nodeC->in_list.push_back({nodeD, false});

            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

            Execution   *exec = new Execution(queriesNode);

            // Send Node A directly but can search first query in QueriesNode
            CHECK(exec->searchValue({nodeA, false}) == -1);

            delete exec;
        }

        SECTION( "Multi value False" ) {
            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);

            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});
            nodeA->in_list.push_back({nodeC, false});
            nodeA->in_list.push_back({nodeD, false});

            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA, false}};

            Execution   *exec = new Execution(queriesNode);

            // Send Node A directly but can search first query in QueriesNode
            CHECK(exec->searchValue({nodeA, false}) == -1);

            delete exec;
        }

        SECTION( "Multi value True" ) {
            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});
            nodeA->in_list.push_back({nodeC, false});
            nodeA->in_list.push_back({nodeD, false});

            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

            Execution   *exec = new Execution(queriesNode);

            CHECK(nodeA->value == 0);
            CHECK(nodeB->value == 0);
            CHECK(nodeC->value == 1);
            CHECK(nodeD->value == 0);

            // Send Node A directly but can search first query in QueriesNode
            CHECK(exec->searchValue({nodeA,false}) == 1);

            CHECK(nodeA->value == 1);
            CHECK(nodeB->value == -1);
            CHECK(nodeC->value == 1);
            CHECK(nodeD->value == 0);

            delete exec;
        }

        SECTION( "Multi value chaine True" ) {
            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);
            nodeC->in_list.push_back({nodeD, false});

            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);
            nodeB->in_list.push_back({nodeC, false});

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});
            
            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

            Execution   *exec = new Execution(queriesNode);

            CHECK(nodeA->value == 0);
            CHECK(nodeB->value == 0);
            CHECK(nodeC->value == 1);
            CHECK(nodeD->value == 0);

            // Send Node A directly but can search first query in QueriesNode
            CHECK(exec->searchValue({nodeA,false}) == 1);

            CHECK(nodeA->value == 1);
            CHECK(nodeB->value == 1);
            CHECK(nodeC->value == 1);
            CHECK(nodeD->value == 0);

            delete exec;
        }

        SECTION( "AND" ) {
            SECTION( "And False" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

                GGraphNode  *nodep = creatNode(AND_NODE, '+', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 0);
                CHECK(nodeC->value == 1);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == -1);

                CHECK(nodeA->value == -1);
                CHECK(nodep->value == -1);
                CHECK(nodeB->value == -1);
                CHECK(nodeC->value == 1);

                delete exec;
            }

            SECTION( "And True" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 1);

                GGraphNode  *nodep = creatNode(AND_NODE, '+', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == 1);

                CHECK(nodeA->value == 1);
                CHECK(nodep->value == 1);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                delete exec;
            }
        }

        SECTION( "OR" ) {
            SECTION( "OR False" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

                GGraphNode  *nodep = creatNode(OR_NODE, '|', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 0);
                CHECK(nodeC->value == 0);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == -1);

                CHECK(nodeA->value == -1);
                CHECK(nodep->value == -1);
                CHECK(nodeB->value == -1);
                CHECK(nodeC->value == -1);

                delete exec;
            }

            SECTION( "OR True by one" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

                GGraphNode  *nodep = creatNode(OR_NODE, '|', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 0);
                CHECK(nodeC->value == 1);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == 1);

                CHECK(nodeA->value == 1);
                CHECK(nodep->value == 1);
                CHECK(nodeB->value == -1);
                CHECK(nodeC->value == 1);

                delete exec;
            }

            SECTION( "OR True by two" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 1);

                GGraphNode  *nodep = creatNode(OR_NODE, '|', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == 1);

                CHECK(nodeA->value == 1);
                CHECK(nodep->value == 1);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                delete exec;
            }
        }

        SECTION( "XOR" ) {
            SECTION( "XOR False by two true" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 1);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 1);

                GGraphNode  *nodep = creatNode(XOR_NODE, '|', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == -1);

                CHECK(nodeA->value == -1);
                CHECK(nodep->value == -1);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 1);

                delete exec;
            }

            SECTION( "XOR False by two false" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

                GGraphNode  *nodep = creatNode(XOR_NODE, '|', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 0);
                CHECK(nodeC->value == 0);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == -1);

                CHECK(nodeA->value == -1);
                CHECK(nodep->value == -1);
                CHECK(nodeB->value == -1);
                CHECK(nodeC->value == -1);

                delete exec;
            }

            SECTION( "XOR True by one" ) {
                GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);

                GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 1);

                GGraphNode  *nodep = creatNode(XOR_NODE, '^', false, 0);

                GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
                nodeA->in_list.push_back({nodep, false});
                nodep->in_list.push_back({nodeB, false});
                nodep->in_list.push_back({nodeC, false});

                std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}};

                Execution   *exec = new Execution(queriesNode);

                CHECK(nodeA->value == 0);
                CHECK(nodep->value == 0);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == 0);

                // Send Node A directly but can search first query in QueriesNode
                CHECK(exec->searchValue({nodeA,false}) == 1);

                CHECK(nodeA->value == 1);
                CHECK(nodep->value == 1);
                CHECK(nodeB->value == 1);
                CHECK(nodeC->value == -1);

                delete exec;
            }
        }
    }

    SECTION( "Resolve Queries" ) {
            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 0);

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});

            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);
            nodeC->in_list.push_back({nodeD, false});

            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}, {nodeC,false}};

            Execution   *exec = new Execution(queriesNode);

            // Send Node A directly but can search first query in QueriesNode
            std::ostringstream oss;
            // Save the CERR at instante T
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            // Assign OSS to the CERR for save CERR in OSS
            std::cout.rdbuf(oss.rdbuf());

            // Execute function to test on CERR
            exec->resolveQueries();

            // Restore CERR at instante T (before test)
            std::cout.rdbuf(p_cout_streambuf);

            // test your oss content...
            CHECK(oss.str() == "A is False\nC is False\n");

            delete exec;
        }

        SECTION( "Resolve Queries" ) {
            GGraphNode  *nodeB = creatNode(FACT_NODE, 'B', false, 1);

            GGraphNode  *nodeA = creatNode(FACT_NODE, 'A', false, 0);
            nodeA->in_list.push_back({nodeB, false});

            GGraphNode  *nodeD = creatNode(FACT_NODE, 'D', false, 0);

            GGraphNode  *nodeC = creatNode(FACT_NODE, 'C', false, 0);
            nodeC->in_list.push_back({nodeD, false});

            std::list<std::pair<GGraphNode*, bool>> queriesNode = {{nodeA,false}, {nodeC,false}};

            Execution   *exec = new Execution(queriesNode);

            // Send Node A directly but can search first query in QueriesNode
            std::ostringstream oss;
            // Save the CERR at instante T
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            // Assign OSS to the CERR for save CERR in OSS
            std::cout.rdbuf(oss.rdbuf());

            // Execute function to test on CERR
            exec->resolveQueries();

            // Restore CERR at instante T (before test)
            std::cout.rdbuf(p_cout_streambuf);

            // test your oss content...
            CHECK(oss.str() == "A is True\nC is False\n");

            delete exec;
        }

}