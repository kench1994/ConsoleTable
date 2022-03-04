#pragma once
#include <string>
#include <atomic>
#include <memory>
namespace utils
{
    namespace visual
    {
        enum class colors : unsigned int{
            reset = 0x00,
            clear = 0x00
        };

        enum class position : unsigned int{
            middle,
            //角块
            angle-l,
            angle-r,
            //棱块
            edge
        };

        //单元格抽象
        typedef struct tagTableCell{
            tagTableCell() : spWidth(nullptr){}
            std::string strVal;
            position enPosition;
            std::shared_ptr<unsigned int> spWidth;
        }TableCell;
        using Row_t = std::vector<shared_ptr<TableCell>>;
        //绘图时对于每一行会先自动填充上棱
        class ConsoleTable{
            protected:


        
            public:
                ConsoleTable(){}
                ~ConsoleTable(){}

                void set_header(const std::vector<std::string>& vLineDts)
                {
                    
                }

                void add_row(const std::vector<std::string>& vLineDts)
                {
                    std::size_t idx = 1;
                    for(const auto& iter = vLineDts.begin(); iter != vLineDts.end(); ++iter, ++idx)
                    {
                        auto spCell = std::make_shared<TableCell>();
                        spCell->strVal = iter;
                        if(1 == idx)
                            spCell->position = position::angle-l;
                        else if(idx == vLineDts.size())
                            spCell->position = position::angle-r;
                        else
                            spCell->position = position::middle;
                        
                        
                    }
                }

            private:
                std::vector<shared_ptr<Row_t>> m_vContents;
        };
    }
}