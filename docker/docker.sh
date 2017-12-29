echo ========= Build docker image
docker build -t otus.lessons.08.01 .
echo ========= Check allocator version
docker run --rm -i otus.lessons.08.01 allocator -v
echo ========= Allocate, result will go to ../bin/out.txt
docker run --rm -i otus.lessons.08.01 otus.lessons.08.01
echo ========= Remove docker image
docker rmi otus.lessons.08.01
