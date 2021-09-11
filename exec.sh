mount -path="/tmp/discos calificacion/disco oficial.dk"  -name=p1 #171a
mount -path="/tmp/discos calificacion/disco oficial.dk"  -name=p2 #171b
mount -path="/tmp/discos calificacion/disco oficial.dk"  -name=L77 #171c
mount -path=/tmp/mia/d1.dk  -name=p1 #172a
mount -path=/tmp/mia/d1.dk  -name=R1 #172b
mount -path=/tmp/mia/d1.dk  -name=L154 #172c
umount -id=171b
umount -id="172a"

rep -path=/tmp/mia/reportes/mbr-t1.png -name=mbr -id=172c
rep -path=/tmp/mia/reportes/disk-t1.png -name=disk -id=172b
rep -path=/tmp/mia/reportes/mbr-oficial.png -name=mbr -id=171a
rep -path=/tmp/mia/reportes/disk-oficial.png -name=disk -id=171c
