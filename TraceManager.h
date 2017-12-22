#include <iostream>
#include <fstream>
#include <cstring>

struct MEMREF {

    /* the target address */
    unsigned long long address;

    /* access type (R/W) */
    unsigned type;

    /* the accessing thread */
    unsigned thread;

    /* instruction counter */
    unsigned long long time;

    void print(std::ostream &out) {
        out << std::hex << "0x" << address << std::dec << " ";
        out << type    << " ";
        out << thread  << " ";
        out << time    << " ";
        out << "\n";
    }

};

class TraceReader {

    std::ifstream inFile;
    char *content;
    size_t bsize;
    size_t curpos;
public:

    bool open(const char* filename) {
        inFile.open(filename, std::ios_base::in | std::ios_base::binary);
        if ( !inFile ) {
          //std::cerr << "[ERROR] Unable to open file " << filename << " for reading trace" << std::endl;
          return false;
        }
        return true;
    }
    void close() {
        if (inFile.is_open()) {
          inFile.close();
        }
    }

    TraceReader(){
        bsize = sizeof(MEMREF)*(1<<20);
        content = new char[bsize]; //buffer size, 256M
        curpos = bsize;
    }
    template<typename T>
    bool next(T &ref) {
        auto left = bsize-curpos;
        if(left < sizeof(T)){
            if(!inFile) return false;

            //move left data to front
            if(curpos != bsize)
                memcpy(content, content+curpos, left);
            inFile.read(content+left, curpos);
            bsize = left+inFile.gcount();
            curpos = 0;
            return next(ref);
        }else{
            ref = *(T*)(content+curpos);
            curpos += sizeof(T);
        }
        return true;
        /*
        if ( !inFile.eof() ) {
            inFile.read((char*)&ref, sizeof(T));

            // check for incomplete read
            if (!inFile) return false;

            return true;
        }
        return false;
        */
    }

    template<typename T>
    std::size_t getLength() {
        if (inFile.is_open()) {
            auto cur = inFile.tellg();
            inFile.seekg(0, std::ios::beg);
            auto beg = inFile.tellg();
            inFile.seekg(0, std::ios::end);
            auto end = inFile.tellg();
            inFile.seekg(cur, std::ios::beg);
            return (end - beg) / sizeof(T);
        }
        return 0;
    }

    void reset() {
        if (inFile.is_open()) {
          inFile.seekg(0, std::ios::beg);
        }
    }
};
