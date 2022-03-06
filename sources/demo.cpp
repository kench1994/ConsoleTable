#include "ConsoleTable.h"

using namespace utils;
int main()
{
	model::TableDts table;
	table.set_header({ "4444", "55555", "666666" });
	table.set_header({ "1", "2", "3" });
	table.add_row({ "4444", "55555", "666666" });
	table.add_row({ "3", "2", "1" });

	printf(utils::view::TableView(table).c_str());
    return 0;
}