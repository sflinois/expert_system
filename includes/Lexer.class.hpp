/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:48:07 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 13:15:38 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_CLASS_HPP
# define LEXER_CLASS_HPP

# include "expert_system.h"
# include <list>
# include <fstream>
# include <iostream>

#define     COMMENT_CHARS "#"
#define     IGNORED_CHARS " \t\v\f\r"
#define     FACT_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     OPE_AND '+'
#define     OPE_OR '|'
#define     OPE_XOR '^'
#define     OPE_NOT '!'
#define     OPE_IMPLY '>'

#define     FACT_CHAR '='
#define     QUERY_CHAR '?'

class           Lexer
{
    public:
        Lexer();
		Lexer(Lexer const &src);
		~Lexer();

		Lexer&		        operator=(Lexer const &rhs);

        std::list<t_tkn*>    tokenize(char *file);

    private:
        int                 tokenize_line(std::string line);

        int                 add_rule_tkn(std::string line);
        int                 add_fact_tkn(std::string line);
        int                 add_query_tkn(std::string line);
        void                init_tkn(t_tkn **tkn, char c ,line_type l_type, rule_tkn r_type);

        void                print_tkn_list();

        std::list<t_tkn*>      _tkn_lst;
};

#endif