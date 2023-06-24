#include <QCoreApplication>
//#include "fileIO.h"
//#include "streamIO.h"
#include "streamconvert.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    FileIO file;
//    file.MakeNewFileAndReadIt();
//    StreamIO stream;
//    stream.lineByLineReading();
    StreamConvert streamConv;
    streamConv.stream2Float();

    return a.exec();
}
