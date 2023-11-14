### Exercise 2

**a) Na primeira chamada do syscall, o programa chama a função "int openat(int dirfd, const char *pathname, int flags);", utilizando
o registo RAX com o valor 257, uma vez que este é código da função.Esta retorna o pointeiro para o ficheiro que é aberto. É passado
como parametros o valor -100 para "dirfd" que simobliza AT_FDCWD para especificar a diretoria corrente (diretoria em que o programa
está a correr), o ponteiro para a string "/etc/os-release", em "pathname", escrito em bytes e o valor 0 nas "flags", ou seja não
especificando nenhuma flag adicional na abertura do ficheiro.
    Na segunda vez é chamada a função "off_t lseek(int fd, off_t offset, int whence);", com o código 8, que tem como retorno o
offset em que se encontra o ponteiro do ficheiro. É passado como primeiro parametro o file descriptor do ficheiro aberto na função
anterior. O segundo contém o valor a 0, sem offset e por fim, é colocado o valor 2 ('SEEK_END') no último parametro, ou seja o
ponteiro do ficheiro ficará no fim do ficheiro.
    Na próxima chamada é utilizada a função "void *mmap(void addr[.length], size_t length, int prot, int flags, int fd, off_t
offset);", com o código 9. Esta tem como retorno o ponteiro para a area mapeada. o argumento "addr" é passado a null, ou seja o 
kernel escolhe a pagina alinhada para criar o mapeamento. Em "length" é usado o que offset que foi retornado na função anterior.
Para as permissões de proteção do mapeamento é usado o valor 1(PROT_EXEC), que indica a permissão de executar o código armazenado.
No argumento flags é passado o valor 2(MAP_PRIVATE) que cria um armazenamento de memória privado. No descritor do ficheiro é usado o
retorno da primeira função e com um "offset" de 0.
    Na última chamada é feito uma escrita com "size_t write(int fd, const void buf[.count], size_t count)" que escreve no 
standard output (fd = 1) tudo o que está no buffer, neste caso contém o ficheiro. E escreve o número de bytes que está sinalizado em
"count" (386).
	E por fim, é chamada a função exit_group(), que termina o processo corrente.
