ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft

cls

REM Compila o Teste Lista
pushd .
nmake /F..\composicao\TesteLista.make
popd

del ..\objetos\*.obj

REM Compila o Teste Baralho com Debug
pushd .
nmake /F..\composicao\TesteBaralhoDebug.make
popd

del ..\objetos\*.obj

REM Compila o Teste Mesa com Debug
pushd .
nmake /F..\composicao\TesteMesaDebug.make
popd

del ..\objetos\*.obj

REM Compila o Jogo de Truco com Debug
pushd .
nmake /F..\composicao\JogoDeTrucoDebug.make
popd

del ..\objetos\*.obj

REM Compila o Jogo de Truco
pushd .
nmake /F..\composicao\JogoDeTruco.make
popd

del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

