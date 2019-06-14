/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:45:58 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 14:22:40 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

Parser::Parser()
{
    this->_tkn_lst.clear;
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


GlobalGraph             Parser::parsTokenList(std::list<t_tkn*> tkn)
{

}

