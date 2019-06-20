/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expert_system.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:43:56 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/20 14:34:36 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERT_SYSTEM_H
# define EXPERT_SYSTEM_H

enum line_type{
    L_RULE,
    L_FACT,
    L_QUERY
};

enum rule_tkn{
    T_AND,
    T_OR,
    T_XOR,
    T_VAL,
    T_NOT_VAL,
    T_BRACKET_O,
    T_BRACKET_C,
    T_IMPLIES,
    T_ENDL
};

typedef struct      s_tkn
{
    line_type       l_type;
    rule_tkn        r_type;
    char            val;
}                   t_tkn;

#endif