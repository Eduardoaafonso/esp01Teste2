Programa feito para ESP32s
Obs: Possíveis conflitos entre as bibliotecas do ESP8266 e ESP32s (DNS e WebServer)
Funcionalidade:

1) Conecta no WIFI pelo modo AP(nome e senha "fikiria")
2) Monta parte da tabela do Firebase
	2.1) Após receber Status "ativo", termina de montar os outros elementos da tabela

Bugs:

1) Lento para entrar no modo AP
2) Tratamento de erros e condições
	2.1) Tratar erro de SSID ou senha da rede errada
	2.2) Tratar os casos de mais de 1 dispositivo funcionando com o mesmo cliente
	2.3) Tratar possíveis faltas de elementos na tabela do FireBase.

Passo a Passo para Teste de funcionamento

1) Modificar o FIREBASE_HOST e FIREBASE_AUTH para a conta do projeto
2) Conectar no modo AP com a senha "fikiria"
3) Acessar o site "fikiria.com" ou "192.168.4.1" (às vezes entra como "192.168.1.1")
4) Colocar email, SSID e senha da rede Wifi
5) Aparecerá uma página confirmando seu email com uma instrução
6) Clique em "Enviar"
7) Verifique no FireBase se foram criadas as tabelas "Dispositivo" e "Planos"
8) Modifique o Status para "ativo" manualmente
9) Será criado a tabela "Leituras"