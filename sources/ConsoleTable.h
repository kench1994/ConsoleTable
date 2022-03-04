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

		//����������
		inline unsigned int col_width(const model::TableDts& table, unsigned int uColIndex, bool bWithPadding = true)
		{
			unsigned int uWidth = 0;
			for (const auto& spRow : table.vContents)
				uWidth = std::max(spRow->at(uColIndex).length(), uWidth);
			
			return uWidth;
		}

		//TODO:����tableһ��Ӧ��Ҫ�ж�����

		
	}

    namespace view
    {
		std::string TableView(const model::TableDts& d)
		{
			if (1 == d.vContents.size() && !d.vContents.front())
				return "";
			
			//col1 �п�� ���
			//col2 ...
			std::vector<unsigned int> vWidthWithPadding;
			unsigned int idx = 0;
			for (const auto& itHeaderCell : *d.vContents.front())
			{
				vWidthWithPadding.push_back(control::col_width(d, idx));
				idx++;
			}
			for (const auto& iter : vWidthWithPadding)
			{
				for(auto i = 0; i < iter; i++)
					printf("%c", '-');
			}
			printf("\n");

			//��ʼ����
			for (const auto& spRow : d.vContents)
			{
				for (const auto& itCell : *spRow)
				{
					printf("%s", itCell.c_str());

					//todo
					//��padding
				}
				printf("\n");
			}
		}
        // enum class colors : unsigned int{
        //     reset = 0x00,
        //     clear = 0x00
        // };

        // enum class position : unsigned int{
        //     middle,
        //     //�ǿ�
        //     angle-l,
        //     angle-r,
        //     //���
        //     edge
        // };

        // //��Ԫ�����
        // typedef struct tagTableCell{
        //     tagTableCell() : spWidth(nullptr){}
        //     std::string strVal;
        //     position enPosition;
        //     std::shared_ptr<unsigned int> spWidth;
        // }TableCell;

        // using Row_t = std::vector<shared_ptr<TableCell>>;
        // //��ͼʱ����ÿһ�л����Զ��������
        // class ConsoleTable{
        //     protected:


        
        //     public:
        //         ConsoleTable(){}
        //         ~ConsoleTable(){}

        //         void set_header(const std::vector<std::string>& vLineDts)
        //         {
                    
        //         }

        //         void add_row(const std::vector<std::string>& vLineDts)
        //         {
        //             std::size_t idx = 1;
        //             for(const auto& iter = vLineDts.begin(); iter != vLineDts.end(); ++iter, ++idx)
        //             {
        //                 auto spCell = std::make_shared<TableCell>();
        //                 spCell->strVal = iter;
        //                 if(1 == idx)
        //                     spCell->position = position::angle-l;
        //                 else if(idx == vLineDts.size())
        //                     spCell->position = position::angle-r;
        //                 else
        //                     spCell->position = position::middle;
                        
                        
        //             }
        //         }

        //     private:
        //         std::vector<shared_ptr<Row_t>> m_vContents;
        //}
    }
}
