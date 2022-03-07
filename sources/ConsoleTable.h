#pragma once
#include <algorithm>
#include <assert.h>
#include <string>
#include <vector>
#include <atomic>
#include <memory>
#include <sstream>
namespace utils
{
    namespace model
    {
        using CellDts_t = std::string;
        using RowDts_t = std::vector<CellDts_t>;

        typedef struct tagTableDts{
            tagTableDts()
                : vContents({nullptr})
            {}

			//TODO:support anykind cell
            void set_header(const RowDts_t& vLineDts)
            {
                auto &&spHeaderDts = vContents[0];
                if(!spHeaderDts)
                    spHeaderDts = std::make_shared<RowDts_t>(vLineDts);
                else
                    *spHeaderDts = vLineDts;
            }

            void add_row(const RowDts_t& vLineDts)
            {
				vContents.emplace_back(std::make_shared<RowDts_t>(vLineDts));
            }




            //规定0行一定为header
            std::vector<std::shared_ptr<RowDts_t>> vContents;
        }TableDts;
    }

	namespace view
	{
		
		enum class forground_colors : unsigned int {
			default = 30,
			Black = 30,
			Red = 31,
			Green = 32,
			Yellow = 33,
			Blue = 34,
			Magenta = 35,
			Cyan = 36,
			White = 37,
			BrightBlack = 90,
			BrightRed = 91,
			BrightGreen = 92,
			BrightYellow = 93,
			BrightBlue = 94,
			BrightMagenta = 95,
			BrightCyan = 96,
			BrightWhite = 97
		};
	}
	namespace control
	{
		//颜色显示规则
		//输入cell -- 现在只是文本
		inline view::forground_colors color(const model::CellDts_t& d)
		{
			return view::forground_colors::default;
		}

		//通过row_id控制color
		inline view::forground_colors color_by_row(unsigned int uRowID)
		{

			return view::forground_colors::default;
		}

		//cell规则

		//输入表和列号,计算出相应列中值最大的长度
		inline unsigned int col_width(const model::TableDts& table, unsigned int uColIndex)
		{
			unsigned int uWidth = 0;
			for (const auto& spRow : table.vContents)
				uWidth = (std::max)(spRow->at(uColIndex).length(), uWidth);
			return uWidth;
		}

		//TODO:计算table一共应该要有多少列

		
	}

    namespace view
    {
		constexpr const char* NEW_LINE = "\n", *FIELD_SEP = "|";
        constexpr unsigned int uCellValPaddingBefore = 1, uCellValPaddingAfter = 2;
		//TODO:add 行列序号选项
		std::string TableView(const model::TableDts& d)
		{
			if (1 == d.vContents.size() && !d.vContents.front())
				return "";
            //计算显示需要预留的空间
			size_t szTableDraSpace = 0;
			std::vector<unsigned int> vWidthPerCol;
			unsigned int uColIdx = 0;
            const auto& spHeaderRow = d.vContents.front();
			for (const auto& itHeaderCell : *spHeaderRow)
			{
                auto uColWidth = control::col_width(d, uColIdx);
				vWidthPerCol.push_back(uColWidth);
				uColIdx++;
                //前后padding + val_len + 切割符或\n
                szTableDraSpace += (\
                  uColWidth + \
                  uCellValPaddingBefore + uCellValPaddingAfter +\
                  strlen(FIELD_SEP));
			}
            //乘以行数
            szTableDraSpace *= d.vContents.size();
			//表头N个字段 再加n ge颜色补偿
			szTableDraSpace += spHeaderRow->size() * 9;

			auto pszTableDrawSpace = new char[szTableDraSpace];
            memset(pszTableDrawSpace, ' ', szTableDraSpace);	
            auto pszRealDraw = pszTableDrawSpace;
			//开始画表
			unsigned int uRowId = 0;
			for (const auto& spRow : d.vContents)
			{
                uColIdx = 0;
				for (const auto& itCell : *spRow)
				{
					if(0 == uRowId)
					{
						pszRealDraw += sprintf(pszRealDraw, " \x1B[94m%s\033[0m  ", itCell.c_str());
					}
					else
					{
						strncpy(pszRealDraw + uCellValPaddingBefore, itCell.c_str(), itCell.size());
						pszRealDraw += (vWidthPerCol[uColIdx] + uCellValPaddingBefore + uCellValPaddingAfter);
					}
					
					if(++uColIdx == spRow->size())
					{
						strncpy(pszRealDraw, NEW_LINE, strlen(NEW_LINE));
						pszRealDraw +=  strlen(NEW_LINE);
					}
					else
					{
						strncpy(pszRealDraw, FIELD_SEP, strlen(FIELD_SEP));
						pszRealDraw +=  strlen(FIELD_SEP);
					}
				}
				++uRowId;
			}
            std::string strResult(pszTableDrawSpace, szTableDraSpace);
            delete []pszTableDrawSpace;
            return strResult;
		}
    }
}
