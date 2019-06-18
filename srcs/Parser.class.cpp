/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:45:58 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/18 15:51:58 by sflinois         ###   ########.fr       */
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
    // GGraphNode          *tmp = NULL;
    int                 err;

    this->_tkn_lst = tkn;
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

    if (this->_tkn_lst.empty())
        return (2);
    if (this->_tkn_lst.front()->l_type == L_RULE)
    {
        for(t_tkn *tkn : this->_tkn_lst)
        {
            // std::cout << "DEBUG " << tkn->r_type << std::endl;
            if (tkn->r_type == T_ENDL)
                break;
            if (tkn->r_type == T_IMPLIES)
                imply = 1;
            else if (imply)
                err |= this->checkImply(prev, tkn);
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
    while (this->_tkn_lst.front() && this->_tkn_lst.front()->r_type != T_ENDL)
        this->_tkn_lst.pop_front();
    this->_tkn_lst.pop_front();
    return (err);
}

int                     Parser::checkValue(t_tkn* prev, t_tkn* tkn)
{
    if (tkn->r_type == T_NOT_VAL && prev && prev->r_type == T_NOT_VAL)
        return (1);
    if (prevTkn(prev) && prev->r_type == T_VAL)
        return (1);
    if (prevTkn(prev) && prev->r_type == T_BRACKET_C)
        return (1);
    if (prevTkn(prev) && prev->r_type == T_BRACKET_O)
        return (1);
    return (0);
}

int                     Parser::checkOperators(t_tkn* prev, t_tkn* tkn)
{
    if (!tkn)
        return (1);
    if (!prevTkn(prev))
        return (1);
    if (prevTkn(prev) && prev->r_type != T_VAL && prev->r_type != T_BRACKET_C)
        return (1);
    return (0);
}

int                     Parser::checkBrackets(t_tkn* prev, t_tkn* tkn)
{
    if (!tkn)
        return (1);
    if (tkn->r_type == T_BRACKET_O)
    {
        if (prevTkn(prev) && prev->r_type != T_OR
                && prev->r_type != T_XOR
                && prev->r_type != T_AND)
            return (1);
    }
    else if (tkn->r_type == T_BRACKET_C)
    {
        if (!prevTkn(prev))
            return (1);
        if (prevTkn(prev) && prev->r_type != T_VAL)
            return (1);
    }
    return (0);
}

int                     Parser::checkImply(t_tkn* prev, t_tkn* tkn)
{
    if (!tkn)
        return (1);
    if (tkn && (tkn->r_type == T_VAL || tkn->r_type == T_NOT_VAL))
    {
        if (!prevTkn(prev))
            return (1);
        if (prevTkn(prev) && prev->r_type != T_VAL
                            && prev->r_type != T_IMPLIES
                            && prev->r_type != T_AND)
            return(1);
    }
    else if (tkn->r_type == T_AND)
    {
        if (!prevTkn(prev))
            return (1);
        if (prevTkn(prev) && prev->r_type != T_VAL)
            return(1);
    }
    return (0);
}

int                     Parser::checkFactList(t_tkn* prev, t_tkn* tkn)
{
    if (!tkn || tkn->r_type != T_VAL)
        return (1);
    if (prevTkn(prev) && prev->r_type != T_VAL)
            return (1);
    return (0);
}

bool                    Parser::prevTkn(t_tkn* prev){
    if (!prev)
        return (false);
    if (prev->r_type == T_ENDL)
        return (false);
    return (true);
}