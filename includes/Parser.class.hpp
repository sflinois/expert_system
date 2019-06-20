/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:46:37 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/20 14:53:39 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include "expert_system.h"
# include "GlobalGraph.class.hpp"
# include <list>
# include <iostream>

class Parser
{
    public:
        Parser();
        Parser(Parser const &src);
        Parser(std::list<t_tkn*> tkn_lst);
        ~Parser();

        Parser&             operator=(Parser const &rhs);

        std::list<t_tkn*>   &parsTokenList(std::list<t_tkn*> tkn);

    private:

        int     checkTknLine(std::list<t_tkn*> tkn, int *line_flag, int *valid_flag);
        int     checkBracketsLine(std::list<t_tkn*> tkn);
        int     checkValue(t_tkn* prev, t_tkn* tkn);
        int     checkOperators(t_tkn* prev, t_tkn* tkn);
        int     checkImply(t_tkn* prev, t_tkn* tkn);
        int     checkBrackets(t_tkn* prev, t_tkn* tkn);
        int     checkFactList(t_tkn* prev, t_tkn* tkn);
        bool    prevTkn(t_tkn* prev);

        std::list<t_tkn*>      _tkn_lst;
};

#endif