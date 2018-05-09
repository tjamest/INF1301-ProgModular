REM   Limpa tudo que sera' regerado

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del TesteLista.list
del TesteLista.make
del TesteListaProd.list
del TesteListaProd.make
del TesteListaDebug.list
del TesteListaDebug.make

cd ..\Fontes
del *.bak
del *.err

cd ..\Objetos
del *.bak
del TesteLista.obj
del TesteLista.lib
del TesteLista.build
del TesteListaProd.obj
del TesteListaProd.lib
del TesteListaProd.build
del TesteListaDebug.obj
del TesteListaDebug.lib
del TesteListaDebug.build

cd ..\Produto
del *.bak
del TesteLista.log
del TesteLista.exe
del TesteListaProd.log
del TesteListaProd.exe
del TesteListaDebug.log
del TesteListaDebug.exe
del *.err

cd ..\Tabelas
del *.bak

cd ..\Scripts
del *.bak
del *.estat

cd ..\Docs
del *.bak

cd ..\Ferramnt
del *.bak


popd
