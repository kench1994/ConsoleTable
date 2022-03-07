#include "ConsoleTable.h"

using namespace utils;
int main()
{
	model::TableDts table;
	table.set_header({ "4444", "55555", "666666" });
	table.set_header({ "表头字段1", "表头字段2", "表头字段3" });
	table.add_row({ "1", "2", "3" });
	table.add_row({ "4444", "55555", "666666" });
	table.add_row({ "单元格C1", "单元格C2", "单元格C3" });
	printf(utils::view::TableView(table).c_str());
    return 0;
}