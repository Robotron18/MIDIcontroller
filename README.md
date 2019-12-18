<h1>requerimientos para cargar programa a arduino:</h1>

bajar carpeta arduinomidiboardv9filtered
El entorno arduino necesita las siguientes librerias:
-midi
-SSD1306Ascii
Ambas de descargan a traves del gestor de librerias de Arduino

<h2>configuracion del programa</h2> 

Los unicos parametros que se deben cambiar en el programa son:
-Determinar si el multiplexor sera para potes o botones
-Determinar si la salida sera midi o como mensaje serie (util para debug)

esto se configura desde las lineas 19 a 21

<h2>Salida midi USB</h1>
que el dispositivo este configurado como salida midi solo habilita a tener salida DIN. 
Para que el dispositivo sea reconocido como controlador midi hay que reprogramar otro integrado de la placa

instrucciones aqui>> https://youtu.be/tmFtMAZOGZo

No cualquier placa arduino es compatible con este procedimiento, las versiones de gama baja traen un adaptador usb CH340 que no permite esta operacion
Las unicas placas que permiten hacer la conversion a dispositivo midi son las que traen un atmel 16u2 o 8u2 como interfaz midi. Consulten con su proveedor antes de comprar
