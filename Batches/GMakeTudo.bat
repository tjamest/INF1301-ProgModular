@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\ferramnt

gmake /b..\composicao /cTesteLista
gmake /b..\composicao /cTesteListaProd
gmake /b..\composicao /cTesteListaDebug

gmake /b..\composicao /cTesteBaralho
gmake /b..\composicao /cTesteBaralhoProd
gmake /b..\composicao /cTesteBaralhoDebug

popd
