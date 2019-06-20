/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:11:13 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/20 14:34:36 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.class.hpp"

Lexer::Lexer()
{
    
}

Lexer::Lexer(Lexer const &src)
{
    *this = src;
}

Lexer::~Lexer()
{

}

Lexer&              Lexer::operator=(Lexer const &rhs)
{
    this->_tkn_lst = rhs._tkn_lst;
    return (*this);
}

std::list<t_tkn*>    Lexer::tokenize(char *file)
{
    std::ifstream		ifs;
	std::string			line;
    int                 nb_line = 1;
    int                 ret = 0;

	ifs.open(file);
	if (ifs.is_open())
	{
		while (std::getline(ifs, line) && !ret)
        {
			ret = this->tokenize_line(line);
            if (ret)
            {
                std::cerr << "Syntax error at line " << nb_line << ": " << std::endl;
                std::cerr << "   " << line << std::endl;
                this->_tkn_lst.clear();
            }
            nb_line++;
        }
	}
	ifs.close();
    this->print_tkn_list();
	return (this->_tkn_lst);
}

int                Lexer::tokenize_line(std::string line)
{
    typedef int (Lexer::*char_to_tkn) (std::string line);
	static char_to_tkn fncTab[] = {&Lexer::add_rule_tkn,
								&Lexer::add_fact_tkn,
								&Lexer::add_query_tkn};
    int         error;
    line_type   l_type;

    l_type = L_RULE;
    if (line.front() == FACT_CHAR)
    {
        line.erase(0, 1);
        l_type = L_FACT;
    }
    else if (line.front() == QUERY_CHAR)
    {
        line.erase(0, 1);
        l_type = L_QUERY;
    }
    error = (this->*fncTab[l_type])(line);
    return error;
}

int             Lexer::add_rule_tkn(std::string line)
{
    std::string str_comment(COMMENT_CHARS);
    std::string str_ignored(IGNORED_CHARS);
    std::string str_fact(FACT_CHARS);
    int         is_special_char = 0;
    t_tkn       *tkn;

    for(char& c : line)
    {
        tkn = NULL;
        if (is_special_char == 1)
        {
            if (str_fact.find(c, 0) != std::string::npos)
                this->init_tkn(&tkn, c, L_RULE, T_NOT_VAL);
            else
                return (1);
            is_special_char = 0;
        } 
        else if (is_special_char == 2)
        {
            if (c == OPE_IMPLY)
                this->init_tkn(&tkn, c, L_RULE, T_IMPLIES);
            else
                return (1);
            is_special_char = 0;
        }
        else if (str_comment.find(c, 0) != std::string::npos)
        {
            this->init_tkn(&tkn, '\n', L_RULE, T_ENDL);
            this->_tkn_lst.push_back(tkn);
            return (0);
        }
        else if (str_ignored.find(c, 0) != std::string::npos)
            ;
        else if (str_fact.find(c, 0) != std::string::npos)
            this->init_tkn(&tkn, c, L_RULE, T_VAL);
        else if (c == OPE_AND)
            this->init_tkn(&tkn, c, L_RULE, T_AND);
        else if (c == OPE_OR)
            this->init_tkn(&tkn, c, L_RULE, T_OR);
        else if (c == OPE_XOR)
            this->init_tkn(&tkn, c, L_RULE, T_XOR);
        else if (c == OPE_BRACKET_O)
            this->init_tkn(&tkn, c, L_RULE, T_BRACKET_O);
        else if (c == OPE_BRACKET_C)
            this->init_tkn(&tkn, c, L_RULE, T_BRACKET_C);
        else if (c == OPE_NOT)
            is_special_char = 1;
        else if (c == FACT_CHAR)
            is_special_char = 2;
        else
            return (1);
        if (tkn)
        {
            // std::cout << tkn->val;
            this->_tkn_lst.push_back(tkn);
        }
    }
    this->init_tkn(&tkn, '\n', L_RULE, T_ENDL);
    this->_tkn_lst.push_back(tkn);
    return (0);
}

int             Lexer::add_fact_tkn(std::string line)
{
    std::string str_comment(COMMENT_CHARS);
    std::string str_ignored(IGNORED_CHARS);
    std::string str_fact(FACT_CHARS);
    t_tkn       *tkn;
    
    for(char& c : line)
    {
        tkn = NULL;
        if (str_fact.find(c, 0) != std::string::npos)
            this->init_tkn(&tkn, c, L_FACT, T_VAL);
        else if (str_ignored.find(c, 0) != std::string::npos)
            ;
        else if (str_comment.find(c, 0) != std::string::npos)
        {
            this->init_tkn(&tkn, '\n', L_FACT, T_ENDL);
            this->_tkn_lst.push_back(tkn);
            return (0);
        }
        else
            return (1);
        if (tkn)
            this->_tkn_lst.push_back(tkn);
    }
    this->init_tkn(&tkn, '\n', L_FACT, T_ENDL);
    this->_tkn_lst.push_back(tkn);
    return (0);
}

int             Lexer::add_query_tkn(std::string line)
{
    std::string str_comment(COMMENT_CHARS);
    std::string str_ignored(IGNORED_CHARS);
    std::string str_fact(FACT_CHARS);
    t_tkn       *tkn;
    
    for(char& c : line)
    {
        tkn = NULL;
        if (str_fact.find(c, 0) != std::string::npos)
            this->init_tkn(&tkn, c, L_QUERY, T_VAL);
        else if (str_ignored.find(c, 0) != std::string::npos)
            ;
        else if (str_comment.find(c, 0) != std::string::npos)
        {
            this->init_tkn(&tkn, '\n', L_QUERY, T_ENDL);
            this->_tkn_lst.push_back(tkn);
            return (0);
        }
        else
            return (1);
        if (tkn)
            this->_tkn_lst.push_back(tkn);
    }
    this->init_tkn(&tkn, '\n', L_QUERY, T_ENDL);
    this->_tkn_lst.push_back(tkn);
    return (0);
}

void            Lexer::init_tkn(t_tkn **tkn, char c ,line_type l_type, rule_tkn r_type)
{
    *tkn = new t_tkn();
    (*tkn)->l_type = l_type;
    (*tkn)->r_type = r_type; 
    (*tkn)->val = c;
}

void            Lexer::print_tkn_list()
{
    for(t_tkn *tkn: this->_tkn_lst)
    {
        std::cout << tkn->val ;//<< ":" << tkn->r_type << ":" << tkn->l_type << " ";
    }
}