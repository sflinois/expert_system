/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:11:13 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/08 14:02:56 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.class.hpp"

Lexer::Lexer()
{
    
}

Lexer::Lexer(Lexer const &src)
{
    
}

Lexer::~Lexer()
{

}

Lexer&              Lexer::operator=(Lexer const &rhs)
{
    
}

std::list<t_tkn>    Lexer::tokenize(char *file)
{
    std::ifstream		ifs;
	std::string			line;
    int                 ret = 0;

	ifs.open(file);
	if (ifs.is_open())
	{
		while (std::getline(ifs, line) && !ret)
			ret = this->tokenize_line(line);
	}
	ifs.close();
	return (this->_tkn_lst);
}

int                Lexer::tokenize_line(std::string line)
{
    typedef bool (Lexer::*char_to_tkn) (char c);
	static char_to_tkn fncTab[] = {&Lexer::add_rule_tkn,
								&Lexer::add_fact_tkn,
								&Lexer::add_query_tkn};
    bool        is_valid;
    line_type   l_type;

    l_type = L_RULE;
    if (line.front() == FACT_CHAR)
        l_type = L_FACT;
    else if (line.front() == QUERY_CHAR)
        l_type = L_QUERY;
    
    for(char& c : line) {
        if ()
        is_valid = (c);
    }
}

