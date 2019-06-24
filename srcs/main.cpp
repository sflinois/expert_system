/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/24 15:34:28 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expert_system.h"
#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "GlobalGraph.class.hpp"
#include <list>

int		main(int argc, char **argv)
{
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
    if (tkn.empty())
        return (1);
    tkn = pars.parsTokenList(tkn);
    if (tkn.empty())
        std::cout << "Error occured during parsing" << std::endl;
    graph.init(tkn);
    graph.display_graph();
    
    return (0);
}