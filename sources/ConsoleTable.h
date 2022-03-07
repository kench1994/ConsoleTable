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

            //�涨0��һ��Ϊheader
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
		//��ɫ��ʾ����
		//����cell -- ����ֻ���ı�
		inline view::colors color(const model::CellDts_t& d)
		{
			return view::colors::default;
		}

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
        constexpr unsigned int uCellValPaddingBefore = 1, uCellValPaddingAfter = 2;
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
                  1);
			}
            //��������
            szTableDraSpace *= d.vContents.size();
			auto pszTableDrawSpace = new char[szTableDraSpace];
            memset(pszTableDrawSpace, ' ', szTableDraSpace);

            auto pszRealDraw = pszTableDrawSpace;
			//��ʼ����
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
