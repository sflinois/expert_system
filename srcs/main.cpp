/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/18 16:15:55 by sflinois         ###   ########.fr       */
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
    std::list<t_tkn*>   tkn;

    if (argc != 2)
    {
        std::cerr << "expert_system take 1 argument" << std::endl;
        return (1);
    }
    tkn = lex.tokenize(argv[1]);
    pars.parsTokenList(tkn);
}