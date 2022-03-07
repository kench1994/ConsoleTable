#include "ConsoleTable.h"

using namespace utils;
int main()
{
	// printf("%d", strlen("x1B[31m\033[0m"));
	// printf("\n");
    // printf("\x1B[31mTexting\033[0m\t\t");
    // printf("\x1B[32mTexting\033[0m\t\t");
    // printf("\x1B[33mTexting\033[0m\t\t");
    // printf("\x1B[34mTexting\033[0m\t\t");
    // printf("\x1B[35mTexting\033[0m\n");
    
    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[36mTexting\033[0m\t\t");
    // printf("\x1B[37mTexting\033[0m\t\t");
    // printf("\x1B[93mTexting\033[0m\n");
    
    // printf("\033[3;42;30mTexting\033[0m\t\t");
    // printf("\033[3;43;30mTexting\033[0m\t\t");
    // printf("\033[3;44;30mTexting\033[0m\t\t");
    // printf("\033[3;104;30mTexting\033[0m\t\t");
    // printf("\033[3;100;30mTexting\033[0m\n");

    // printf("\033[3;47;35mTexting\033[0m\t\t");
    // printf("\033[2;47;35mTexting\033[0m\t\t");
    // printf("\033[1;47;35mTexting\033[0m\t\t");
    // printf("\t\t");
    // printf("\n");

	model::TableDts table;
	table.set_header({ "4444", "55555", "666666" });
	table.set_header({ "表头字段1", "表头字段2", "表头字段3" });
	table.add_row({ "1", "2", "3" });
	table.add_row({ "4444", "55555", "666666" });
	table.add_row({ "单元格C1", "单元格C2", "单元格C3" });
	printf(utils::view::TableView(table).c_str());
    return 0;
}