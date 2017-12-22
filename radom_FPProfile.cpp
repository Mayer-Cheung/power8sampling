#include <string>
#include <vector>
#include <map>
#include <random>
#include "footprint.h"
#include "footprintManager.h"
#include "TraceManager.h"

using namespace std;

int main(int argc, char** argv){
    TraceReader tr;
    FPBuilder fpb;
    string trace = argv[1];
    string fname = trace;
    if(argc > 2) fname = argv[2];
    
    unordered_map<int, int> ht;

    std::ofstream out("distribute.txt");

    if (tr.open(trace.c_str())) {
        MEMREF mf;
        while (tr.next(mf)) {
            fpb.OnReference((mf.address  >> 7) << 7);
            ht[(mf.address  >> 7) << 7]++;
        }
        FPDist* fpd = fpb.Finalize();

        //serialization
        FPUtil::serialize(fpd, fname+".fp");
        ofstream fout(fname+".rt");
        fpb.rthist.serialize(fout);

        for (auto it : ht) {
        	out << it.second << "\n";
        }
        cout << ht.size() << endl;
    }
    
    return 0;
}
