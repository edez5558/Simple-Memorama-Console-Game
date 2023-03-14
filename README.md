# Juego de memorama utilizando Checkpointing technique

Edmundo Gomez Alvarez

## Introduccion

Checkpointing es una técnica que permite guardar el estado actual de un programa en un punto determinado de su ejecución. De esta manera, si ocurre una falla del sistema, se puede reiniciar el programa desde el último punto de control o checkpoint en lugar de comenzar desde el principio, lo que ahorra tiempo y recursos valiosos.

En la computación tolerante a fallos, el checkpointing se utiliza para minimizar el impacto de fallas de hardware o software. Si un sistema falla, los checkpoints permiten que el sistema se recupere y continúe su funcionamiento desde un punto anterior, sin perder datos importantes o tiempo de procesamiento. Además, el uso de múltiples checkpoints también puede aumentar la redundancia del sistema, lo que mejora su confiabilidad y resistencia a fallos.

## Desarrollo

Cuando el programa se abre, lo primero que hace es verificar si existe un archivo llamado "checkpoint.data". Si este archivo no existe, el programa crea uno nuevo. Si el archivo ya existe, el programa carga el estado del juego que se encuentra en el archivo.
![Crear](https://user-images.githubusercontent.com/122659695/224899421-e4f4fbbe-cf13-4231-90c1-5654e423f648.png)

Estos son los dos mensajes que se muestran cuando se seleccionan dos posiciones.

Este mensaje es cuando no son pares.

![Noigual](https://user-images.githubusercontent.com/122659695/224899416-749c8fb1-a002-493e-b23d-9d77daa0e302.png)

Este mensaje es cuando son pares.

![Encontrado](https://user-images.githubusercontent.com/122659695/224899423-8c2de326-0795-4d20-9936-69b357d569ec.png)

Para mostrar el funcionamiento del programa cuando se cierra el programa de manera inesperada utilizare Ctrl + C para terminar la ejecucion del programa

![Fallo](https://user-images.githubusercontent.com/122659695/224899408-37ec1644-8bb8-4424-9393-2feb88e3c62b.png)

Ahora volvemos a abrir el programa y podemos observar que sigue con el estado del programa anteriormente.

![Recuperacion](https://user-images.githubusercontent.com/122659695/224899418-f50e4f9b-011c-4690-be1c-360d6632dd49.png)

Tambien el programa se puede cerrar cuando solo hayas seleccionado una posicion.

![Fallo2](https://user-images.githubusercontent.com/122659695/224899413-3a757408-1456-482b-b61c-7699f5e9088e.png)

y podemos ver que aun mantiene su estado.

![Recuperacion2](https://user-images.githubusercontent.com/122659695/224899420-cbb6c1c7-f176-45dd-864d-171a815fd3f8.png)

## Conclusion

Aunque la mayoría del programa consistió simplemente en guardar un array en un archivo, el uso de un puntero en una parte del programa presentó un desafío adicional. Para solucionar este problema, se utilizó un offset para almacenar el puntero de manera que se pudiera recuperar sin problemas con las direcciones.

Este enfoque demuestra la importancia de tener una comprensión sólida de los conceptos de programación para abordar problemas más complejos como el checkpointing. Al implementar esta técnica, el programa pudo recuperarse de fallos del sistema y proporcionar una mejor experiencia de usuario.
