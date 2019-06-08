/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:48:07 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/08 14:02:48 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_CLASS_HPP
# define LEXER_CLASS_HPP

# include "expert_system.h"
# include <list>
# include <fstream>

#define     COMMENT_CHARS "#"
#define     IGNORED_CHARS " \t\v\f\r"
#define     FACT_CHARS "ABCDEFGHIJKLMNOPQRSTWXYZ"
#define     OPE_CHARS "()!+|^"
#define     IMPLY_RULE "=>"

#define     FACT_CHAR '='
#define     QUERY_CHAR '?'

class           Lexer
{
    public:
        Lexer();
		Lexer(Lexer const &src);
		~Lexer();

		Lexer&		        operator=(Lexer const &rhs);

        std::list<t_tkn>    tokenize(char *file);

    private:
        int                 tokenize_line(std::string line);

        bool                add_rule_tkn(char c);
        bool                add_fact_tkn(char c);
        bool                add_query_tkn(char c);


        std::list<t_tkn>      _tkn_lst;
};

std::string     syntax_array[5] = {COMMENT_CHARS, IGNORED_CHARS,
                                FACT_CHARS, OPE_CHARS, IMPLY_RULE};

#endif