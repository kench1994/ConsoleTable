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




            //�涨0��һ��Ϊheader
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
		//��ɫ��ʾ����
		//����cell -- ����ֻ���ı�
		inline view::forground_colors color(const model::CellDts_t& d)
		{
			return view::forground_colors::default;
		}

		//ͨ��row_id����color
		inline view::forground_colors color_by_row(unsigned int uRowID)
		{

			return view::forground_colors::default;
		}

		//cell����

		//�������к�,�������Ӧ����ֵ���ĳ���
		inline unsigned int col_width(const model::TableDts& table, unsigned int uColIndex)
		{
			unsigned int uWidth = 0;
			for (const auto& spRow : table.vContents)
				uWidth = (std::max)(spRow->at(uColIndex).length(), uWidth);
			return uWidth;
		}

		//TODO:����tableһ��Ӧ��Ҫ�ж�����

		
	}

    namespace view
    {
		constexpr const char* NEW_LINE = "\n", *FIELD_SEP = "|";
        constexpr unsigned int uCellValPaddingBefore = 1, uCellValPaddingAfter = 2;
		//TODO:add �������ѡ��
		std::string TableView(const model::TableDts& d)
		{
			if (1 == d.vContents.size() && !d.vContents.front())
				return "";
            //������ʾ��ҪԤ���Ŀռ�
			size_t szTableDraSpace = 0;
			std::vector<unsigned int> vWidthPerCol;
			unsigned int uColIdx = 0;
            const auto& spHeaderRow = d.vContents.front();
			for (const auto& itHeaderCell : *spHeaderRow)
			{
                auto uColWidth = control::col_width(d, uColIdx);
				vWidthPerCol.push_back(uColWidth);
				uColIdx++;
                //ǰ��padding + val_len + �и����\n
                szTableDraSpace += (\
                  uColWidth + \
                  uCellValPaddingBefore + uCellValPaddingAfter +\
                  strlen(FIELD_SEP));
			}
            //��������
            szTableDraSpace *= d.vContents.size();
			//��ͷN���ֶ� �ټ�n ge��ɫ����
			szTableDraSpace += spHeaderRow->size() * 9;

			auto pszTableDrawSpace = new char[szTableDraSpace];
            memset(pszTableDrawSpace, ' ', szTableDraSpace);	
            auto pszRealDraw = pszTableDrawSpace;
			//��ʼ����
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
