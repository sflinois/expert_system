/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:45:58 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/15 15:52:05 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

Parser::Parser()
{
    this->_tkn_lst.clear();
}

Parser::Parser(Parser const &src)
{
    *this = src;
}

Parser::Parser(std::list<t_tkn*> tkn_lst)
{
    this->_tkn_lst = tkn_lst;
}

Parser::~Parser()
{

}

Parser&                 Parser::operator=(Parser const &rhs)
{
     this->_tkn_lst = rhs._tkn_lst;
    return (*this);
}


GlobalGraph*            Parser::parsTokenList(std::list<t_tkn*> tkn)
{
    GlobalGraph         *gg = new GlobalGraph();
    GGraphNode          *tmp = NULL;
    int                 err;

    while((err = this->checkTknLine()) == 0)
    {
        
    }
    return (gg);
}


int                     Parser::checkTknLine()
{
    typedef int (Parser::*checkParams) (t_tkn* prev, t_tkn* tkn);
	static checkParams fncTab[] = {&Parser::checkOperators,
								&Parser::checkOperators,
								&Parser::checkOperators,
								&Parser::checkValue,
								&Parser::checkValue,
								&Parser::checkBrackets,
								&Parser::checkBrackets,
    };
    t_tkn*      prev = NULL;
    int     err = 0;
    int     imply = 0;

    if (this->_tkn_lst.front()->l_type == L_RULE)
    {
        for(t_tkn *tkn : this->_tkn_lst)
        {
            if (tkn->r_type == T_ENDL)
                break;
            if (tkn->r_type == T_IMPLIES)
                imply = 1;
            else if (imply)
                err |= this->checkInply(prev, tkn);
            else
                err |= (this->*fncTab[tkn->r_type])(prev, tkn);
            prev = tkn;
        }
    }
    else
    {
        for(t_tkn *tkn : this->_tkn_lst)
        {
            if (tkn->r_type == T_ENDL)
                break;
            err |= this->checkFactList(prev, tkn);
            prev = tkn;
        }
    }
    return (err);
}

int                     Parser::checkValue(t_tkn* prev, t_tkn* tkn)
{
    if (prev && prev->r_type == T_VAL)
    

    return 0;
}

int                     Parser::checkOperators(t_tkn* prev, t_tkn* tkn)
{
    t_tkn*      tmp;
    
    for(t_tkn *tkn : this->_tkn_lst)
    {
        if (tkn->r_type == T_ENDL || tkn->r_type == T_IMPLIES)
            break;
        if (tkn->r_type == T_AND || tkn->r_type == T_OR || tkn->r_type == T_XOR)
        {
            if (tmp != NULL)
                return (1);
        }
        tmp = tkn;
    }
    return 0;
}

int                     Parser::checkBrackets(t_tkn* prev, t_tkn* tkn)
{
    for(t_tkn *tkn : this->_tkn_lst)
    {
        if (tkn->r_type == rule_tkn::T_ENDL)
            break;
        
        
    }
}

int                     Parser::checkInply(t_tkn* prev, t_tkn* tkn)
{
    for(t_tkn *tkn : this->_tkn_lst)
    {
        if (tkn->r_type == rule_tkn::T_ENDL)
            break;
        
        
    }
}

int                     Parser::checkFactList(t_tkn* prev, t_tkn* tkn)
{
    for(t_tkn *tkn : this->_tkn_lst)
    {
        if (tkn->r_type == rule_tkn::T_ENDL)
            break;
        
        
    }
}