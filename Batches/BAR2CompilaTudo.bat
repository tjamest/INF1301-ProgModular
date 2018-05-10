ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft

cls

REM compila para producao sem otimizacoes
pushd .
/NODEFAULTLIB:LIBCMTD.lib
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

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

