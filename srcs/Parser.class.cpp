/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:45:58 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/25 17:21:32 by sflinois         ###   ########.fr       */
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


std::list<t_tkn*>       &Parser::parsTokenList(std::list<t_tkn*> tkn)
{
    int                 err = 0;
    int                 line_flag = 0;
    int                 valid_flag = 0;

    this->_tkn_lst = tkn;
    while((err = this->checkTknLine(tkn, &line_flag, &valid_flag)) == 0)
    {
        err |= this->checkBracketsLine(tkn);
        err |= 1; // check if right is used in left
        while (tkn.front() && tkn.front()->r_type != T_ENDL)
            tkn.pop_front();
        tkn.pop_front();
    }
    if (line_flag != 7 || valid_flag != 7)
        err = 1;
    if (err != 2)
        this->_tkn_lst.clear();
    // std::cout << std::endl << err << std::endl;
    return (this->_tkn_lst);
}


int                     Parser::checkTknLine(std::list<t_tkn*> tkn, int *line_flag, int *valid_flag)
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
    std::list<char> value_left;
    std::list<char> value_right;
    t_tkn*      prev = NULL;
    int     err = 0;
    int     imply = 0;

    if (tkn.empty())
        return (2);
    if (tkn.front()->l_type == L_RULE)
    {
        *line_flag |= 1;
        for(t_tkn *tkn : tkn)
        {
            if (tkn->r_type == T_ENDL)
                break;
            if (tkn->r_type == T_IMPLIES && imply == 0)
                imply = 1;
            else if (tkn->r_type == T_IMPLIES && imply != 0)
                err |= 1;
            else if (imply > 0)
            {
                err |= this->checkImply(prev, tkn);
                if (tkn->r_type == T_VAL || tkn->r_type == T_NOT_VAL)
                    value_right.push_back(tkn->val);
            }
            else
            {
                err |= (this->*fncTab[tkn->r_type])(prev, tkn);
                if (tkn->r_type == T_VAL || tkn->r_type == T_NOT_VAL)
                    value_left.push_back(tkn->val);
            }
            prev = tkn;
        }

        if (!value_left.empty() && !value_right.empty())
        {
            for(char cl : value_left)
                for(char cr : value_right)
                    if (cl == cr)
                        err |= 1;
            if (err == 0)
                *valid_flag |= 3;
        }
        else if (imply || !value_left.empty())
        {
            err |= 1;
        }
    }
    else
    {
        if (tkn.front()->l_type == L_FACT)
            *line_flag |= 2;
        else if (tkn.front()->l_type == L_QUERY)
            *line_flag |= 4;
        for(t_tkn *tkn : tkn)
        {
            if (tkn->r_type == T_ENDL)
                break;
            if (tkn->l_type == L_QUERY)
                *valid_flag |= 4;
            err |= this->checkFactList(prev, tkn);
            prev = tkn;
        }
    }

    return (err);
}

int                     Parser::checkBracketsLine(std::list<t_tkn*> tkn)
{
    int     open_nb = 0;
    
    for(t_tkn *t : tkn)
    {
        if (t->r_type == T_ENDL || t->r_type == T_IMPLIES)
            break;
        if (t->r_type == T_BRACKET_O)
            open_nb += 1;
        if (t->r_type == T_BRACKET_C)
        {
            if (open_nb > 0)
                open_nb -= 1;
            else
                return (1);
        }
    }
    if (open_nb > 0)
        return (1);
    return (0);   
}

int                     Parser::checkValue(t_tkn* prev, t_tkn* tkn)
{
    if (tkn->r_type == T_NOT_VAL && prev && prev->r_type == T_NOT_VAL)
        return (1);
    if (prevTkn(prev) && prev->r_type == T_VAL)
        return (1);
    if (prevTkn(prev) && prev->r_type == T_BRACKET_C)
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
    if (tkn && (tkn->r_type == T_VAL))
    {
        if (!prevTkn(prev))
            return (1);
        if (prevTkn(prev) && prev->r_type != T_IMPLIES
                            && prev->r_type != T_AND)
            return(1);
        return (0);
    }
    else if (tkn->r_type == T_AND)
    {
        if (!prevTkn(prev))
            return (1);
        if (prevTkn(prev) && prev->r_type == T_VAL)
            return(0);
    }
    return (1);
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