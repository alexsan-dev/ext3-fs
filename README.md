# Calificación proyecto no. 1

Este proyecto contiene los archivos de entrada separados en carpetas. La carpeta ```test``` contiene  archivos de entrada
preliminares, para que puedan practicar antes de la calificación real. Cada día de calificación agregará una nueva
carpeta para los archivos de ese día. Las entradas preliminares solo validan mínimos. Por lo que la dificultad es un
tanto reducida en comparación con los reales. Sin embargo, son un buen punto de entrada para validar mínimos y
el correcto funcionamiento del proyecto. <br>
Para correr los archivos de entrada, seguir las intrucciones que se detallan en este documento.

## Requerimientos
El proyecto deberá ser presentado desde un entorno válido. Las opciones aceptadas son las siguientes.
- Instalación física Linux (la distribución queda a discreción del estudiante).
- Entorno Mac.
- Instalación *BSD física (la distribución queda a discreción del estudiante).
- WSL. En caso de utilizar esta opción, se les recuerda que deben preparar TODO su entorno de acuerdo al documento
  WSL.pdf adjunto en este repositorio a modo de recordatorio.

## Utilización
Una vez resuelto el problema del entorno, el proyecto deberá ser compilado y ejecutado desde consola. En ningún
momento se aceptará su ejecución desde un IDE o algún otro método auxiliar. El nombre del ejecutable queda a
discreción del estudiante. Una vez compilado seguir los siguientes pasos para su ejecución
- Instalar Zsh. Zsh es una shell, es incluída por defecto en algunas distribución Linux, así como en MacOS. Puedes
verificar si tienes instalado zsh con el comando ```zsh --version```. Si tu sistema no la incluye por defecto,
deberás instalarla. NO es necesario que cambies la shell por defecto de tu usuario, únicamente con instalar zsh como una shell secundaria es suficiente.
- Editar el archivo ```env.zsh```; Este archivo define algunas variables de entorno que necesitarán para correr el
archivo de entrada. Estas variables están acompañadas de un comentario para mejor comprensión
- ```zsh no-exec.zsh```
- ```$EJECUTABLE exec -path=exec.sh```
- Repetir el último comando según archivos *.sh existan. El orden será indicado por el auxiliar. No intentes ejecutar
archivos *.sh con exec antes de ejecutar los archivos no-exec!

## Consideraciones
- Los archivos *.sh (a ser ejecutados bajo el comando exec) NO contienen errores, a menos que se indique explícitamente lo contrario. Es decir, hay archivos *.sh diseñados especialmente para contener errores y evaluar el manejo de
los mismos y la robustez de su aplicación. Sin embargo, estos NUNCA se van a mezclar con archivos *.sh normales,
en el caso de los archivos de prueba donde solamente se evalúan requerimientos mínimos estos no contienen errores.
- El comando mount NO genera IDs de manera aleatoria. Los primeros dígitos son los últimos dígitos de su carnet.
Seguidos de un número, comenzando en 1 e incrementando de acuerdo al orden que se montan distintos discos. Seguido
de una letra en minuscula, comenzando en a e incrementando según el orden de particiones montadas en un mismo disco.
Esto significa que el nombre esperado de las particiones deberá ser predecible y coincidir con el esperado en los archivos de calificación (cada comando mount va acompañado de un comentario que indica el ID esperado).
- No deben preocuparse por crear discos o reportes en locaciones inválidas según un sistema Unix. La mayoría de operaciones se realizarán en el directorio /tmp. 

## Conceptos a evaluar
El proyecto puede ser dividido en 4 partes que serán evaluadas y constituyen el 100% del proyecto.
1. Implementacioń del esquema de partición MBR.
2. Implementación del sistema de archivos ext2/3.
3. Implementación de comandos de utilidad para el manejo del sistema de archivos (cp, mv, rm, touch, etc).
4. Implementación del esquema de grupos, permisos y journaling.
Los reportes no representan ninguna parte del proyecto ya que son obligatorios para demostrar la correcta implementación de estos conceptos y se utilizan en todas las partes. No todos los reportes son obligatorios ya que no todas
las partes son requerimientos mínimos. Sin embargo, para tener derecho a la ponderación de cada una de estas partes deberán ser presentados los reportes según aplique (i.e, para tener derecho a los puntos por implementar el sistema
de archivos ext2/3, deberá ser presentado el reporte tree).

## Requerimientos mínimos
Los requerimientos mínimos representan el 25% del proyecto. Estos incluyen únicamente el punto 1. Implementación del
esquema de partición MBR. A modo de recordatorio se listan los comandos y funcionalidades que pertenecen a esta área.
- Aplicación por argumentos de consola (no exec).
- Comando exec.
- mkdisk
- fdisk
- rmdisk
- mount
- umount 
- rep -name=mbr
- rep -name=disk
- Dentro del comando fdisk se implica la implementación de particiones Primarias, Extendidas y Lógicas.

## Notas
- Los argumentos de consola se utilizan únicamente para mkdisk, fdisk, rmdisk. mount, umount, rep, etc. Son utilizados únicamente desde archivos exec.
- En los requerimientos mínimos se lista como último punto la implementación de particiones Primarias, Extendidas
y Lógicas, a modo hacer explícito su requerimiento como parte del comando fdisk.
- Los archivos de calificación varían de acuerdo al día.
- La hoja de calificación será subida en este mismo repositorio.
- El ejecutable ```proyecto1``` que se encuentra en este repositorio no hace nada. Es solamente un placeholder.
- La carpeta ```data``` es una carpeta con información de prueba que será utilizada para llenar los sistemas de
archivos durante la calificación. Su contenido no tiene ninguna trascendencia o relevancia más de allá de este propósito.
- El alumno voluntario durante la explicación del entorno WSL puede hacer uso del mismo sin necesidad de configurar
todo su entorno según las instrucciones detalladas en WSL.pdf; Sin embargo, la instalación de zsh para la ejecución
de los archivos no-exec es necesaria.
