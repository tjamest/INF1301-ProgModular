@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\ferramnt

gmake /b..\composicao /cTesteLista

gmake /b..\composicao /cTesteBaralhoDebug

gmake /b..\composicao /cTesteMesaDebug

gmake /b..\composicao /cJogoDeTrucoDebug

gmake /b..\composicao /cJogoDeTruco

popd
