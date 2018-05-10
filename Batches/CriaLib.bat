ECHO Cria a biblioteca a ser utilizada no exemplo \truco
ECHO assume o arcabouco todo construído e correto

pushd  .

cd     ..\ferramnt\arcaboucoteste_2_02\arcabouc\objetos
del    *.obj
del    *.lib
nmake /F..\composicao\crialib.make  "PRD="
copy   arcaboucoteste.lib ..\..\..\..\objetos

popd
