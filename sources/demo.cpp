#include "ConsoleTable.h"

using namespace utils;
int main()
{
	model::TableDts table;
	table.set_header({ "4444", "55555", "666666" });
	table.set_header({ "��ͷ�ֶ�1", "��ͷ�ֶ�2", "��ͷ�ֶ�3" });
	table.add_row({ "1", "2", "3" });
	table.add_row({ "4444", "55555", "666666" });
	table.add_row({ "��Ԫ��C1", "��Ԫ��C2", "��Ԫ��C3" });
	printf(utils::view::TableView(table).c_str());
    return 0;
}