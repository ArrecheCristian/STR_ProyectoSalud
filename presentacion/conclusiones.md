* Para mapas pequeños con poca cantidad de agentes, no pueden sacarse muchas conclusiones ya que las variaciones no son muy
significativas al haber pocos datos para procesar

* La division de procesos de 3x2 la dejamos de utilizar para las pruebas ya que utiliza todos los cores del cpu y baja el
rendimiento significativamente, ya que tiene que compartir los cores con todos los procesos del sistema.

* La división vertical/horizontal tambien medio se descarta porque se ve que es bastante chota, mejora bastante el rendimiento
cuando las divisiones son más equitativas.

* Cuanto más grande es el mapa, para la misma division de procesos, los agentes están cada vez más alejados de la zona de buffer.

* Ya tratandose de mapas más grandes y mayor cantidad de agentes, la escalabilidad es bastante constante