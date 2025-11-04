#include "../../include/so_long.h"


void validation_map()
{
    if (!is_retangular())
        ft_show_error("Map Bad formated!");
    if (!has_allow_char())
        ft_show_error("Invalid Character!");
    if (!validade_quant_EPC())
        ft_show_error("Find Multiples values or Invalid colletions!");
    if (!is_sorrounded_walls())
        ft_show_error("Incorrect Walls!");
}