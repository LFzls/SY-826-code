echo off & color 0A
set "str2=cov_style" 
::是否删除orig文件，如果要删除则下面语句去掉::
set "str1=del_orig" 

::指定起始文件夹
set DIR="%cd%"
echo DIR=%DIR%

::参数 /R 表示需要遍历子文件夹,去掉表示不遍历子文件夹,"%%f "是一个变量,类似于迭代器,但是这个变量只能由一个字母组成,前面带上 "%%"
:: 括号中是通配符,可以指定后缀名,*.*表示所有文件
for /R %DIR% %%f in (*.c) do ( 
if defined str2 (echo %%f
astyle --style=allman  --convert-tabs --align-pointer=middle --attach-closing-while  --break-blocks ^
--indent-cases --align-reference=middle --break-after-logical --break-one-line-headers  --add-braces -p %%f
)
)
::for /R %DIR% %%f in (*.h) do ( 
::if defined str2 ( echo %%f
::astyle --style=allman  --convert-tabs --align-pointer=middle --attach-closing-while  --break-blocks ^
::--indent-cases --align-reference=middle --break-after-logical --break-one-line-headers  --add-braces -p %%f
::) 
::)

for /R %DIR% %%f in (*.orig) do ( 
if defined str1 (echo %%f
del %%f)
)
::pause