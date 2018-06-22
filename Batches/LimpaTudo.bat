REM   Limpa tudo que sera regerado

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del *.list
del *.make

cd ..\Docs
del *.bak

cd ..\Ferramnt
del *.bak

cd ..\Fontes
del *.bak
del *.err

cd ..\Objetos
del *.bak
del baralho.obj
del lista.obj
del mesa.obj
del interface.obj
del *.build

cd ..\Produto
del *.bak
del *.log
del *.exe
del *.err

cd ..\Scripts
del *.bak
del *.estat

cd ..\Tabelas
del *.bak

popd