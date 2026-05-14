#include "FileIO.hpp"
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

#include "App.hpp"
#include "MainWindow.hpp"
#include "MemMappedFile.hpp"
#include "AutoFdClose.hpp"

class Pclose{
public:
    void operator()(FILE *f){
        pclose(f);
    }
};

class Fclose{
public:
    void operator()(FILE *f){
        fclose(f);
    }
};

class Fd
{
public:
    int id = 0;

    Fd() = default;
    Fd(int fd): id(fd) {}
    Fd(std::nullptr_t) {}
    explicit operator bool() const { return id != 0; }
    friend bool operator==(Fd l, Fd r) { return l.id == r.id; }
    friend bool operator!=(Fd l, Fd r) { return !(l == r); }
    // or only a defaulted operator== (since C++20)
};

struct FdClose{
    using pointer = Fd;
    void operator()(Fd fd){
        close(fd.id);
    }
};

//using Auto_FdClose = std::unique_ptr<int,FdClose>;
using Auto_FdClose = std::unique_ptr<Fd,FdClose>;

using Auto_fclose = std::unique_ptr<FILE,Fclose>;
static_assert(sizeof(Auto_fclose) == sizeof(FILE*));

using Auto_pclose = std::unique_ptr<FILE,Pclose>;
static_assert(sizeof(Auto_pclose) == sizeof(FILE*));
//----------------------------------------------------------------
int main(int argc,char *argv[]){
    App app(argc, argv);

    MainWindow window;
    window.resize(650, 400);
    window.show();
#if 0
    FileIO fio(fopen("", "w"), &fclose);
    //fprintf(fio.get(), "%d", 17);
    fprintf(fio, "%d", 17);
    FileIO fio2(popen("", "w"), &pclose);

    Auto_fclose fc(fopen("","w"));
    Auto_pclose pc(popen(" ","w"));
    return app.exec();
#endif

    const char *filepath = "./src/map.txt";

    AutoFdClose fdClose(open(filepath,O_RDONLY));
    MemMappedFile mR(fdClose.get());
    char* p = mR.get();
    printf("%s",p);

    return app.exec();
};
