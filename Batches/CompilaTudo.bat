ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft

cls

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteLista.make
popd

del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteBaralhoDebug.make
popd

del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\TesteMesaDebug.make
popd

del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\JogoDeTruco.make
popd

del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

