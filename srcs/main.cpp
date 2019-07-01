/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/07/01 11:56:49 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Init Unit Test */
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "expert_system.h"
#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "GlobalGraph.class.hpp"
#include "Execution.hpp"
#include <list>
#include <sstream>
// #include "main.unitTest.cpp"

int     work(int argc, char **argv) {
    Lexer               lex;
    Parser              pars;
    GlobalGraph         graph;
    std::list<t_tkn*>   tkn;

    if (argc != 2)
    {
        std::cerr << "expert_system take 1 argument" << std::endl;
        return (1);
    }
    tkn = lex.tokenize(argv[1]);

    if (tkn.empty()) {
        std::cerr << "error in file <" << argv[1] << ">" << std::endl;
        return (1);
    }
    tkn = pars.parsTokenList(tkn);
    if (tkn.empty())
    {
        std::cout << "Error occured during parsing" << std::endl;
        return (1);
    }
    graph.init(tkn);
    // graph.display_graph();

    std::list<GGraphNode*> queriesNode = graph.get_query_list();


    Execution       exec(queriesNode);

    exec.resolveQueries();

    return 0;

}

int		main(int argc, char **argv)
{
    bool    test = false;
    int     result;
    
    if (argc == 3 && std::strncmp(argv[1], "-t", 2) == 0){
        test = true;
        argc = 2;
        argv[1] = argv[2];
    }
    if ((result = work(argc, argv)) == 1)
        return 1;

    /* Init Unit Test */
    if (test)
        result = Catch::Session().run();
    return result;
}

TEST_CASE( "MAINTEST", "[mainTest]" ) {

    std::ostringstream oss;
    std::ostringstream oss_err;
    // Save the CERR at instante T
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::streambuf* p_cerr_streambuf = std::cerr.rdbuf();
    // Assign OSS to the CERR for save CERR in OSS
    std::cout.rdbuf(oss.rdbuf());
    std::cerr.rdbuf(oss_err.rdbuf());

    SECTION( "Empty Params" ) {
        char av1[] = "./expert_system";
        char* av[] = {av1};

        int i = work(1, av);

        CHECK(i == 1);

        CHECK(oss.str() == "");
        CHECK(oss_err.str() == "expert_system take 1 argument\n");
    }

    SECTION( "Too Many Params" ) {
        char av1[] = "./expert_system";
        char* av[] = {av1};

        int i = work(3, av);

        CHECK(i == 1);

        CHECK(oss.str() == "");
        CHECK(oss_err.str() == "expert_system take 1 argument\n");
    }

    SECTION( "and_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/and_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\nF is True\nK is True\nP is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "and_basic2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/and_basic2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\nF is True\nK is False\nP is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "neg_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/neg_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "neg_basic2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/neg_basic2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "neg_basic3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/neg_basic3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "neg_basic4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/neg_basic4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "or_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/or_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "or_basic2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/or_basic2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "or_basic3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/or_basic3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "or_basic4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/or_basic4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses5" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses5";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses6" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses6";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses7" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses7";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses8" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses8";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses9" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses9";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses10" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses10";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "parentheses11" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/parentheses11";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "E is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "same_conclusion1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/same_conclusion1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "same_conclusion2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/same_conclusion2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "same_conclusion3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/same_conclusion3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "same_conclusion4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/same_conclusion4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "xor_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/xor_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "xor_basic2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/xor_basic2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "xor_basic3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/xor_basic3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is True\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "xor_basic4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/xor_basic4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    SECTION( "error_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/error_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 1);

        CHECK(oss.str() == "");
        CHECK(oss_err.str() == "Syntax error at line 1: \n   plop\nerror in file <tests/error_basic1>\n");
    }

    SECTION( "error_basic2" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/error_basic2";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 1);

        CHECK(oss.str() == "Error occured during parsing\n");
        CHECK(oss_err.str() == "You need rules, facts statement and query lines\n");
    }

    SECTION( "error_basic3" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/error_basic3";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 1);

        CHECK(oss.str() == "");
        CHECK(oss_err.str() == "Syntax error at line 3: \n   =5\nerror in file <tests/error_basic3>\n");
    }

    SECTION( "error_basic4" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/error_basic4";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 1);

        CHECK(oss.str() == "");
        CHECK(oss_err.str() == "Syntax error at line 1: \n   a => b\nerror in file <tests/error_basic4>\n");
    }

    SECTION( "loop_basic1" ) {
        char av1[] = "./expert_system";
        char av2[] = "tests/loop_basic1";
        char* av[] = {av1, av2};

        int i = work(2, av);

        CHECK(i == 0);

        CHECK(oss.str() == "A is False\n");
        CHECK(oss_err.str() == "");
    }

    // Restore CERR at instante T (before test)
    std::cout.rdbuf(p_cout_streambuf);
    std::cerr.rdbuf(p_cerr_streambuf);

}