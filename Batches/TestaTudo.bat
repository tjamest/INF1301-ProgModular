rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteLista		/s..\scripts\TesteLista			/l..\produto\TesteLista		/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteBaralhoDebug	/s..\scripts\TesteBaralhoComContador	/l..\produto\TesteBaralhoDebug	/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteMesaDebug	/s..\scripts\TesteMesaComContador	/l..\produto\TesteMesaDebug	/a..\scripts\estatisticas
if errorlevel 4 goto sai

..\ferramnt\exbestat		/e..\scripts\estatisticas

:sai