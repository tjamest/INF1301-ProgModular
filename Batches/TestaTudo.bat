REM Testa todos scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteLista		/s..\scripts\TesteLista		/l..\produto\TesteLista		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteBaralhoDebug	/s..\scripts\TesteBaralho	/l..\produto\TesteBaralhoDebug	/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteMesaDebug	/s..\scripts\TesteMesa		/l..\produto\TesteMesaDebug	/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\ferramnt\exbestat		/e..\scripts\estatisticas

:sai