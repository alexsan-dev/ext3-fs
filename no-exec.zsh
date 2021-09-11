#!/bin/env zsh
source ./env.zsh
alias mkdisk="$EJECUTABLE mkdisk"
alias rmdisk="$EJECUTABLE rmdisk"
alias fdisk="$EJECUTABLE fdisk"
#Si no tienes Zsh instalado en tu sistema (Mac incluye zsh por default)
#deberás instalar Zsh manualmente en ese caso.
#Cada comando fdisk va acompañado de un comentario que indica como debe ir
#quedando el disco. P significa primaria, F Free, E extendida,
#L logica, G libre dentro de una extendida.
#Este archivo tiene algunos errores lógicos. Los errores están acompañados de un comentario que indica porqué debería
#ocurrir el error. En la calificación se validarán algunos escenarios extra. Este archivo debe correr y ejecutarse sin 
#ningún problema, ya que cada comando es atómico. Si ocurre un error, simplemente se detiene la ejecución y no produce
#nada el comando que lanzó el error, pero el resto de comandos deben ejecutarse sin problema. Este archivo NO se ejecuta
#con exec. El archivo de entrada para exec está separado.

OFICIAL="/tmp/discoscalificacion/discooficial.dk"
T1=/tmp/mia/d1.dk
T2=/tmp/mia/d2.dk
T3=/tmp/mia/d3.dk

mkdisk -path=$T1 -size=10 -u=m -f=WF 
mkdisk -path=$T3 -size=187 -u=m -f=FF 
mkdisk -f=FF -size=55 -u=k -path=$T2
mkdisk -size=10 -u=m -f=BF -path="$OFICIAL"
rmdisk -path=$T2
fdisk -path="$OFICIAL" -add=15 -u=K -name="ppp1" #Error, p1 no existe.
fdisk -path="$OFICIAL" -size=2550 -u=K -type=P -name="ppp1" #(2550 P; 7450 F)
fdisk -size=1550 -path="$OFICIAL" -u=K -name="ppp2" #(2550P; 1550P; 5900 F)
fdisk -size=3900 -path="$OFICIAL" -u=K -name="ppp3"
fdisk -size=1 -path="$OFICIAL" -type=E -u=M -name="pppe3" #(2550P; 1550P; 3900P; 2000F)
  
fdisk -path="$T1" -size=2550 -u=K -type=P -name="ppp1" #(2550P; 7450F)
fdisk -size=2000 -path="$T1" -u=K -name="ppp2" -type=P #(2550P; 2000P; 5450F)
fdisk -size=3900 -path="$T1" -u=K -name="ppp3" -type=P #(2550P; 2000P; 3900P; 1550F)

fdisk -delete=fast -path="$OFICIAL" -name="ppp2" #(2550P; 1550F; 3900P; 2000F)
fdisk -name="ppp2" -delete=full -path="$T1" #(2550P; 2000F; 3900P; 1550F)
fdisk -add=1000 -name="ppp1" -u=K -path="$T1" #(3550P; 1000F; 3900P; 1550F)
fdisk -path="$T1" -add=-800 -name="ppp3" -u=K #(3550P; 1000F; 3100P; 2350F)

fdisk -size=1400 -path="$OFICIAL" -u=K -name="EEE1" -f=WF -type=E #(2550P; 1400E; 150F; 3900P; 2000F)
fdisk -size=500 -path="$T1" -u=K -name="RRR1" -type=P #(3550P; 1000F; 3100P; 500P; 1850F)
fdisk -size=1800 -path="$T1" -u=K -name="EEE1" -type=E -f=BF #(3550P; 1000F; 3100P; 500P; 1800E; 50F)
fdisk -size=400 -path="$OFICIAL" -f=WF -u=K -name="EEE2" -type=E #Error, solo una extendida por disco

function fill_logicas(){
  I=50
  S=0
  while [[ $S -le $2 ]]; do
    S=$((I+S))
    fdisk -size="$I" -path="$1" -u=K -name="LLL$I" -type=L
    I=$((I+$3))
  done
}

fill_logicas "$OFICIAL" 1300 9 #(2550P; [50L; 59L; 68L; 77L; 86L; 95L; 104L; 113L; 122L; 131L; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)

fill_logicas "$T1" 1700 8 #(3550P; 1000F; 3100P; 500P; [50L; 58L; 66L; 74L; 82L; 90L; 98L; 106L; 114L; 122L; 130L; 138L; 146L; 154L; 162L; 170L; 40F]E; 50F)

fdisk -delete=fast -path="$OFICIAL" -name="LL95" #(2550P; [50L; 59L; 68L; 77L; 86L; 95G; 104L; 113L; 122L; 131L; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)
fdisk -delete=full -path="$OFICIAL" -name="LL131" #(2550P; [50L; 59L; 68L; 77L; 86L; 95G; 104L; 113L; 122L; 131G; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)
fdisk -delete=fast -path="$OFICIAL" -name="LL50" #(2550P; [50G; 59L; 68L; 77L; 86L; 95G; 104L; 113L; 122L; 131G; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)
fdisk -size=50 -path="$OFICIAL" -u=K -name="NN50" -type=L #(2550P; [50G; 59L; 68L; 77L; 86L; 95G; 104L; 113L; 122L; 50L; 81G; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)
fdisk -size=40 -path="$OFICIAL" -u=K -name="NN40" -type=L #(2550P; [50G; 59L; 68L; 77L; 86L; 40L; 55G; 104L; 113L; 122L; 50L; 81G; 140L; 149L; 158L; 48G]E; 150F; 3900P; 2000F)

fdisk -size=400 -path="$OFICIAL" -u=K -name="PP10" -type=P #(2550P; [50G; 59L; 68L; 77L; 86L; 40L; 55G; 104L; 113L; 122L; 50L; 81G; 140L; 149L; 158L; 48G]E; 150F; 3900P; 400P; 1600F)
fdisk -size=500 -path="$OFICIAL" -u=K -name="PP11" -type=P  #Error, maximo de 4 particiones primarias
