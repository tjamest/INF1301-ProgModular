rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\TesteLista        /s..\scripts\TesteLista             /l..\produto\TesteLista              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\TesteBaralho        /s..\scripts\TesteBaralho             /l..\produto\TesteBaralho              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\ferramnt\exbestat    	/e..\scripts\estatisticas

:sai