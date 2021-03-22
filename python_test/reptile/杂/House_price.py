from Get_data import getdata
from Get_Html import getHTML
from IOcsv import writer
import time
from xlsx import write_excel_xlsx,read_excel_xlsx
book_name_xlsx = './data/杭州房价.xlsx'
sheet_name_xlsx = '杭州房价数据表'
# fileHeader = []
# fileHeader.append('年份/月份')
# for i in range(1, 13):
#     fileHeader.append(i)
# writer('test.csv', fileHeader)

d =[]
for year in range(2010,2021):

    print(year)
    url ="https://www.anjuke.com/fangjia/hangzhou"+str(year)
    # url ="https://www.anjuke.com/fangjia/hangzhou2010/"
    html = getHTML(url)
    # writer('test.csv',getdata(html,year))
    d.append(getdata(html,year))
    time.sleep(25)

write_excel_xlsx(book_name_xlsx, sheet_name_xlsx, d)

# print(span)
# for i in range(len(b)):
#     print(b[i],span[i],em[i])
