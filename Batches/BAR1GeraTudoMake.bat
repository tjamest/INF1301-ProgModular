@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\ferramnt

gmake /b..\composicao /cTesteBaralho
gmake /b..\composicao /cTesteBaralhoProd
gmake /b..\composicao /cTesteBaralhoDebug

popd
