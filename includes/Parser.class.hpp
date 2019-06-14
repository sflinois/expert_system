/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:46:37 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/14 14:22:07 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

# include "expert_system.h"
# include "GlobalGraph.class.hpp"
# include <list>

class Parser
{
    public:
        Parser();
        Parser(Parser const &src);
        Parser(std::list<t_tkn*> tkn_lst);
        ~Parser();

        Parser&         operator=(Parser const &rhs);

        GlobalGraph     parsTokenList(std::list<t_tkn*> tkn);

    private:
        std::list<t_tkn*>      _tkn_lst;
};

#endif