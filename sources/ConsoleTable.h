#pragma once
#include <algorithm>
#include <assert.h>
#include <string>
#include <vector>
#include <atomic>
#include <memory>
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
		enum class colors : unsigned int {
			default = 0x00
		};
	}
	namespace control
	{
		//颜色显示规则
		//输入cell -- 现在只是文本
		inline view::colors color(const model::CellDts_t& d)
		{
			return view::colors::default;
		}

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
        constexpr unsigned int uCellValPaddingBefore = 1, uCellValPaddingAfter = 2;
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
                  1);
			}
            //乘以行数
            szTableDraSpace *= d.vContents.size();
			auto pszTableDrawSpace = new char[szTableDraSpace];
            memset(pszTableDrawSpace, ' ', szTableDraSpace);

            auto pszRealDraw = pszTableDrawSpace;
			//开始画表
			for (const auto& spRow : d.vContents)
			{
                uColIdx = 0;
				for (const auto& itCell : *spRow)
				{
					strncpy(pszRealDraw + uCellValPaddingBefore, itCell.c_str(), itCell.size());
					pszRealDraw += (vWidthPerCol[uColIdx] + uCellValPaddingBefore + uCellValPaddingAfter);
					strncpy(pszRealDraw, ++uColIdx != spRow->size() ? "|" : "\n", 1);
					pszRealDraw += 1;
				}
			}
            std::string strResult(pszTableDrawSpace, szTableDraSpace);
            delete []pszTableDrawSpace;
            return strResult;
		}
    }
}
