ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft

cls

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteLista.make
popd

REM compila para producao com otimizacoes
del ..\objetos\TesteListaProd.obj
pushd .
nmake /F..\composicao\TesteListaProd.make  "PRD=" 

REM compila para debug - o arquivo .comp indica quem deve ser compilado com _DEBUG
del ..\objetos\TesteListaDebug.obj
pushd .
nmake /F..\composicao\TesteListaDebug.make 

del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteBaralho.make
popd

REM compila para producao com otimizacoes
del ..\objetos\TesteBaralhoProd.obj
pushd .
nmake /F..\composicao\TesteBaralhoProd.make  "PRD=" 

REM compila para debug - o arquivo .comp indica quem deve ser compilado com _DEBUG
del ..\objetos\TesteBaralhoDebug.obj
pushd .
nmake /F..\composicao\TesteBaralhoDebug.make 

del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

